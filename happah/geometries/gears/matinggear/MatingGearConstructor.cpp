#include "happah/geometries/gears/matinggear/MatingGearConstructor.h"
#include "happah/geometries/gears/matinggear/MatingGearConstructionInformation.h"

#include <cmath>

#include "glm/glm.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "happah/math/Ray.h"


MatingGearConstructor::MatingGearConstructor(
	const ToothProfile& originalGearToothProfile,
	hpreal originalGearRadius,
	hpuint matingGearNTeeth,
	hpreal maxAngle,
	hpuint samplingRate
) : m_allMatingPoints(new std::list<MatingPoint>()),
	m_matingNTeeth(matingGearNTeeth),
	m_maxDiffAngle(maxAngle * M_PI / 180.0f),
	m_matingProfile(new ToothProfile()),
	m_originalToothProfile(new ToothProfile(originalGearToothProfile)),
	m_originalRadius(originalGearRadius),
	m_samplingRate(samplingRate) {

	m_module = 2.0f * m_originalRadius / m_originalToothProfile->getNumberOfTeeth();

	m_matingRadius = m_module * m_matingNTeeth / 2.0f;
	m_distanceOfCenters = m_originalRadius + m_matingRadius;
	m_matingProfile = new ToothProfile();

	m_originalGearCurve = new BSplineCurve<hpvec2>;
	m_originalToothProfile->extendToGearCurve(*m_originalGearCurve);
	m_originalToothCurve = new BSplineCurve<hpvec2>;
	m_originalToothProfile->getCurve(*m_originalToothCurve);

	m_originalToothCurve->getParameterRange(m_startKnots, m_stopKnots);
	m_stepSize = (m_stopKnots - m_startKnots) / (m_samplingRate - 1);

	constructListsOfPossibleMatingPoints();

}

MatingGearConstructor::~MatingGearConstructor() {
	delete m_allMatingPoints;
	delete m_matingProfile;
	delete m_originalToothProfile;
	delete m_originalGearCurve;
	delete m_originalToothCurve;
}

MatingGearConstructionInformation* MatingGearConstructor::getInformation() {
	return new MatingGearConstructionInformation(this);
}

std::list< MatingPoint >* MatingGearConstructor::getMatingPointList() {
	return new std::list<MatingPoint>(*m_allMatingPoints);
}

hpreal MatingGearConstructor::getMatingGearReferenceRadius() {
	return m_matingRadius;
}

hpreal MatingGearConstructor::getOriginalGearReferenceRadius() {
	return m_originalRadius;
}

hpreal MatingGearConstructor::getMinRadiusForOriginGear(const ToothProfile& toothProfile, hpuint matingNTeeth) {
	hpreal min = toothProfile.getTipRadius() / (1.0f + matingNTeeth / toothProfile.getNumberOfTeeth());
	if(min < toothProfile.getRootRadius())
		return min;
	else
		return toothProfile.getRootRadius();
}

hpuint MatingGearConstructor::getMinNumberOfTeethForMatingGear(const ToothProfile& toothProfile, hpreal originRadius) {
	hpreal minReal = toothProfile.getNumberOfTeeth() * ((toothProfile.getTipRadius() / originRadius) - 1.0f);
	hpuint min = static_cast<hpuint>(minReal);
	if(min < 1)
		min = 1; //at least one tooth is necessary
	//return the next higher integer value, if minReal is not already exactly an integer value
	if(static_cast<hpreal>(min) >= minReal)
		return min;
	else
		return min + 1;
}


// std::list< MatingGearInformationPart* >* MatingGearConstructor::getInformationSplines() {
// 	std::list< MatingGearInformationPart* >* informationList = new std::list< MatingGearInformationPart* >();
// 	informationList->push_back(new MatingGearInformationPart(circle(m_originalRadius, hpvec2(0.0f, 0.0f)), MatingGearPart::ORIGIN_REFERENCE_CIRCLE, "Original gear ref circle")); //Reference circle of original gear
// 	informationList->push_back(new MatingGearInformationPart(circle(m_matingRadius, hpvec2(m_distanceOfCenters, 0.0f)),  MatingGearPart::MATING_REFERENCE_CIRCLE,"Mating gear ref circle")); //Reference circle of mating gear
// 	BSplineCurve<hpvec2>* originalUsedPoints = new BSplineCurve<hpvec2>();
// 	BSplineCurve<hpvec2>* matingPoints = new BSplineCurve<hpvec2>();
// 	for(std::list<MatingPoint>::iterator it = m_allMatingPoints->begin(), end = m_allMatingPoints->end(); it != end; ++it){
// 		if(it->error == ErrorCode::NO_ERROR) {
// 			originalUsedPoints->addControlPoint(it->originPoint);
// 			matingPoints->addControlPoint(it->point + hpvec2(m_distanceOfCenters, 0.0f));
// 			informationList->push_back(new MatingGearInformationPart(normalLine(it->originPoint, it->originNormal), MatingGearPart::ORIGIN_NORMAL, "Normal of original gear"));
// 			informationList->push_back(new MatingGearInformationPart(normalLine(it->point + hpvec2(m_distanceOfCenters, 0.0f), it->normal), MatingGearPart::MATING_NORMAL, "Normal of mating gear"));
// 			cerr << "ErrorCode: " << static_cast<int>(it->error) << endl;
// 		} else {
// 			informationList->push_back(new MatingGearInformationPart(normalLine(it->originPoint, it->originNormal), MatingGearPart::ORIGIN_NORMAL, "Normal of original gear", it->error));
// 		}
// 	}
// 	informationList->push_back(new MatingGearInformationPart(originalUsedPoints, MatingGearPart::ORIGIN_TOOTH_PROFILE, "Original used points"));
// 	informationList->push_back(new MatingGearInformationPart(matingPoints, MatingGearPart::MATING_TOOTH_PROFILE, "Constructed mating gear points"));
// 	return informationList;
// }

void MatingGearConstructor::constructListsOfPossibleMatingPoints() {

	m_allMatingPoints = new std::list<MatingPoint>();

	hpvec2 nextPoint = getValueAt(m_startKnots);
	hpvec2 nextNormal = getNormalAt(m_startKnots);

	hpreal radToDegree = 180.0f / M_PI;

	for(hpuint sampleStep = 1; sampleStep < m_samplingRate; ++sampleStep) {

		hpvec2 point = nextPoint;
		hpvec2 normal = nextNormal;
		nextPoint = getValueAt(m_startKnots + sampleStep * m_stepSize);
		nextNormal = getNormalAt(m_startKnots + sampleStep * m_stepSize);

		MatingPoint matingPoint = getMatingPointOf(point, normal);
		m_allMatingPoints->push_back(matingPoint);
		cerr << "normal mating point created" << endl;

		hpreal normalAngleDiff = asin(normal.x * nextNormal.y - normal.y * nextNormal.x);
		if(normalAngleDiff > m_maxDiffAngle) {
			cerr << "              angle>maxAngle" << endl;
			hpuint nPartitions = static_cast<hpuint>(std::abs(normalAngleDiff) / m_maxDiffAngle);
			hpvec2 pointDiff = nextPoint - point;
			hpreal direction = (normalAngleDiff > 0) ? 1.0f : -1.0f;
			for(hpuint partition = 1; partition <= nPartitions; ++partition) {
				hpvec2 partitionPoint = point + pointDiff * static_cast<hpreal> (partition / nPartitions);
				hpvec2 partitionNormal = glm::rotate(normal, m_maxDiffAngle * direction * partition * radToDegree);
				MatingPoint matingPoint = getMatingPointOf(partitionPoint, partitionNormal);
				cerr << "angle> mating point created" << endl;
				m_allMatingPoints->push_back(matingPoint);
			}
		}
	}
	//Go again through all collected points and look at the the intersection point on the reference radius.
	//If two following points differ too much, insert again mating points to get around this inaccuracy.
	//Remark: As the relation of the angle in the reference circle and the angle of the normal difference isn't
	//used here, no guarantee exists, that consecutive mating points have at least an angle of m_maxDiffAngle
	//viewed in the reference circle.
	// for(std::list<MatingPoint>::iterator it = m_allMatingPoints->begin(), nextIt = ++(m_allMatingPoints->begin()); nextIt != m_allMatingPoints->end(); ++it, ++nextIt) {
	// 	if(it->error == ErrorCode::NO_ERROR) {
	// 		hpvec2 point = it->point;
	// 		hpvec2 normal = it->normal;
	// 		hpvec2 nextPoint = nextIt->point;
	// 		hpvec2 nextNormal = nextIt->normal;

	// 		hpreal angleDiff = nextIt->intersectionRefRadiusAngle - it->intersectionRefRadiusAngle;
	// 		if(angleDiff > m_maxDiffAngle) {
	// 			cerr << "              refA.>maxAngle" << endl;
	// 			hpuint nPartitions = static_cast<hpuint>(std::abs(angleDiff) / m_maxDiffAngle);
	// 			hpvec2 pointDiff = nextPoint - point;

	// 			hpreal areaBetween = normal.x * nextNormal.y - normal.y * nextNormal.x;
	// 			hpreal angleBetweenNormals = asin(areaBetween); //angleA is negative or positive, depending on the normals
	// 			hpreal turnAnglePerStep = angleBetweenNormals / nPartitions;

	// 			for(hpuint partition = 1; partition <= nPartitions; ++partition) {
	// 				hpvec2 partitionPoint = point + pointDiff * static_cast<hpreal>(partition / nPartitions);
	// 				hpvec2 partitionNormal = glm::rotate(normal, turnAnglePerStep * partition * radToDegree);
	// 				MatingPoint matingPoint = getMatingPointOf(partitionPoint, partitionNormal);
	// 				m_allMatingPoints->insert(nextIt, matingPoint);
	// 				cerr << "refA.> mating point created" << endl;
	// 				++it;
	// 			}
	// 		}
	// 	}
	// }
}

MatingPoint MatingGearConstructor::getMatingPointOf(const hpvec2& point, const hpvec2& normal) {
	MatingPoint matingPoint;
	matingPoint.originPoint = point;
	matingPoint.originNormal = normal;
	matingPoint.error = ErrorCode::NO_ERROR;
	// cerr << endl << "normal: ";
	// print(normal);
	// cerr << endl;

	hpreal valueUnderRoot = (glm::dot(normal, point) * glm::dot(normal, point)
	                       - glm::dot(point, point) + m_originalRadius * m_originalRadius);
	if(valueUnderRoot < 0) {
		matingPoint.error = ErrorCode::NO_CUT_WITH_REFERENCE_RADIUS;
		cerr << "NO_CUT_WITH_REFERENCE_RADIUS found" << endl;
		return matingPoint;
	}
	hpreal t = -glm::dot(normal, point) + sqrt(valueUnderRoot);
	hpvec2 dirToCutOnRefRadius = glm::normalize(point + t * normal);

	// cerr << "dirToCutOnRefRadius: ";
	// print(dirToCutOnRefRadius);

	hpreal angleA = -asin(dirToCutOnRefRadius.y); //angleA is negative or positive, depending on the normals
	hpreal angleB = angleA * m_originalRadius / m_matingRadius;

	// cerr << ", angleA: " << angleA << ", angleB: " << angleB;

	hpreal radToDegree = 180.0f / M_PI;
	hpvec2 pointRotated = glm::rotate(point, angleA * radToDegree);
	matingPoint.point = glm::rotate((pointRotated - hpvec2(m_distanceOfCenters, 0.0f)), angleB * radToDegree);
	hpvec2 normalOppositeDir = glm::rotate(normal, angleA * radToDegree);
	matingPoint.normal = glm::rotate(glm::rotate(normalOppositeDir, 180.0f), angleB * radToDegree);

	// cerr << ", pointRotated:";
	// print(pointRotated);
	// cerr << ", matingPoint: ";
	// print(matingPoint.point);
	// cerr << endl << endl;

	insertThicknessInMatingPoint(matingPoint);

	// print(matingPoint);

	return matingPoint;
}


//Given MatingPoint already needs its point, normal originPoint and originNormal!
void MatingGearConstructor::insertThicknessInMatingPoint(MatingPoint& matingPoint) {
	Ray ray(hpvec3(matingPoint.originPoint, 0.0f), hpvec3(-matingPoint.originNormal, 0.0f));
	std::vector<hpvec2> intersectionPoints;
	m_originalGearCurve->getIntersectionPointsWithRay(ray, intersectionPoints);
	if(intersectionPoints.empty()) {
		std::cerr << "CURIOS THINGS HAPPENED! A ray of the gear hadn't found a cutting!" << std::endl;
		matingPoint.error = ErrorCode::NO_THICKNESS;
	} else {
		hpreal epsilon = 0.00001f; //prevent finding point as intersection point
		hpreal thickness = 3.0f * m_originalToothProfile->getTipRadius(); //gear can only have a thickness of 2.0f * getTipRadius()
		for(std::vector<hpvec2>::iterator it = intersectionPoints.begin(), end = intersectionPoints.end(); it != end; ++it) {
			hpreal distance = glm::length(*it - matingPoint.originPoint);
			if(distance > epsilon && thickness > distance) {
				thickness = distance;
			}
		}
		matingPoint.forbiddenAreaLength = thickness;
		matingPoint.forbiddenAreaEndPoint = matingPoint.point + matingPoint.normal * thickness;
	}
}

hpvec2 MatingGearConstructor::getNormalAt(hpreal t) {
	hpvec2 derivative = m_originalGearCurve->getDerivativeAt(t);
	if(!m_originalToothProfile->pointsSavedInClockDirection()) {
		derivative *= -1.0f;
	}
	return glm::normalize(hpvec2(-derivative.y, derivative.x));
}

hpvec2 MatingGearConstructor::getValueAt(hpreal t) {
	return m_originalGearCurve->getValueAt(t);
}


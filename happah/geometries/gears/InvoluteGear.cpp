#include "happah/geometries/gears/InvoluteGear.h"
#include <cmath>
#include <sstream>
#include <iostream>

// Constructor for a general gear. Gears are always centered on 0,0,0 with the z axis being the gear axis.
InvoluteGear::InvoluteGear(hpuint nTeeth, hpreal module, hpreal faceWidth, hpreal pressureAngle,
					hpreal bottomClearance, hpreal filletRadius, hpreal helixAngle) : CylindricalGear(),
					m_nTeeth(nTeeth), m_module(module), m_faceWidth(faceWidth),
					m_pressureAngle(pressureAngle),
					m_bottomClearance(bottomClearance), m_filletRadius(filletRadius), m_helixAngle(helixAngle) {
}

InvoluteGear::InvoluteGear(const InvoluteGear& other) : CylindricalGear(),
				m_nTeeth(other.m_nTeeth), m_module(other.m_module), m_faceWidth(other.m_faceWidth),
				m_pressureAngle(other.m_pressureAngle), m_bottomClearance(other.m_bottomClearance),
				m_filletRadius(other.m_filletRadius), m_helixAngle(other.m_helixAngle) {
}

InvoluteGear::~InvoluteGear() {}

//TODO: do we need this?
InvoluteGear& InvoluteGear::operator=(const InvoluteGear& other) {
	if(this != &other) {
		m_nTeeth = other.m_nTeeth;
		m_module = other.m_module;
		m_faceWidth = other.m_faceWidth;
		m_pressureAngle = other.m_pressureAngle;
		m_bottomClearance = other.m_bottomClearance;
		m_filletRadius = other.m_filletRadius;
		m_helixAngle = other.m_helixAngle;
	}
	return *this;
}

//TODO: use logging here!
bool InvoluteGear::verifyAndLog(bool condition, string message) {
	if(!condition)
		cerr << message << endl;
	return condition;
}

bool InvoluteGear::verifyConstraints(bool print) {
	if(print) {
		return verifyAndLog((m_nTeeth > 2), "No involutes possible with only two or less teeth!")
			&& verifyAndLog((m_pressureAngle < M_PI / 2.0f),
					"Pressure angle is too big! A pressure angle of PI/2 would be a circle")
			&& verifyAndLog((getBaseRadius() <= getReferenceRadius() - m_module),
					"Working depth (gemeinsame Zahnhöhe) starts earlier than involute can start!")
			&& verifyAndLog(((pow((getRootRadius() + m_filletRadius) / getBaseRadius(), 2.0f)) - 1.0f >= 0.0f),
					"Bottom clearance is too big!")
			&& verifyAndLog((getStopFilletInvoluteAngle() >= 0),
					"Fillet and involute can't merge as fillet radius is too small or bottom clearance too big!")
			&& verifyAndLog((getShiftAngle() - getStartFilletAngle() >= 0),
					"Fillet is too big for the gap between the teeth!")
			&& verifyAndLog(getStopFilletInvoluteAngle() <= involuteAngleOfIntersectionWithCircle(getReferenceRadius() - m_module),
					"Fillet ends when working depth (gemeinsame Zahnhöhe) already started!")
			&& verifyAndLog(getAngularPitch() / 2.0f >= getShiftAngle() + involuteToCircleAngle(involuteAngleOfIntersectionWithCircle(getTipRadius())),
					"Involute ends after half of angular pitch!");
	} else {
		return (m_nTeeth > 2)
			&& (m_pressureAngle < M_PI / 2.0f)
			&& (getBaseRadius() <= getReferenceRadius() - m_module)
			&& ((pow((getRootRadius() + m_filletRadius) / getBaseRadius(), 2.0f)) - 1.0f >= 0.0f)
			&& (getStopFilletInvoluteAngle() >= 0)
			&& (getShiftAngle() - getStartFilletAngle() >= 0)
			&& (getStopFilletInvoluteAngle() <= involuteAngleOfIntersectionWithCircle(getReferenceRadius() - m_module))
			&& (getAngularPitch() / 2.0f >= getShiftAngle() + involuteToCircleAngle(involuteAngleOfIntersectionWithCircle(getTipRadius())));
	}
}

hpuint InvoluteGear::getNumberOfTeeth() { return m_nTeeth; }
hpreal InvoluteGear::getModule() { return m_module; }
hpreal InvoluteGear::getFaceWidth() { return m_faceWidth; }
hpreal InvoluteGear::getPressureAngle() { return m_pressureAngle; }
hpreal InvoluteGear::getBottomClearance() { return m_bottomClearance; }
hpreal InvoluteGear::getFilletRadius() { return m_filletRadius; }
hpreal InvoluteGear::getHelixAngle() { return m_helixAngle; }

//Teilkreisradius - where width of gaps and width of teeths have same size
hpreal InvoluteGear::getReferenceRadius() {
	return m_nTeeth * m_module / 2.0f;
}
//Kopfkreisradius
hpreal InvoluteGear::getTipRadius() {
	return getReferenceRadius() + m_module;
}
//Fußkreisradius
hpreal InvoluteGear::getRootRadius() {
	return (getReferenceRadius() - m_module - m_bottomClearance);
}
//Grundkreisradius 
hpreal InvoluteGear::getBaseRadius() {
	return getReferenceRadius() * glm::cos(m_pressureAngle);
}
//Teilungswinkel
hpreal InvoluteGear::getAngularPitch() {
	return 2.0f * M_PI / getNumberOfTeeth();
}
hpreal InvoluteGear::getStopFilletInvoluteAngle() {
	hpreal ratio = pow((getRootRadius() + m_filletRadius) / getBaseRadius(), 2.0f);
	return ((sqrt(ratio - 1.0f)) - (m_filletRadius / getBaseRadius()));
}
hpreal InvoluteGear::getStartFilletAngle() {
	hpreal tangens = ((m_filletRadius + getStopFilletInvoluteAngle() * getBaseRadius()) / getBaseRadius());
	return glm::atan(tangens) - getStopFilletInvoluteAngle();
}
hpreal InvoluteGear::getShiftAngle() {
	hpreal intersectRefRadius = involuteToCircleAngle(involuteAngleOfIntersectionWithCircle(getReferenceRadius()));
	return getAngularPitch() / 4.0f - intersectRefRadius;
}
hpreal InvoluteGear::involuteAngleOfIntersectionWithCircle(const hpreal &radius) {
	return glm::sqrt(pow(radius / getBaseRadius(), 2) - 1.0f); 
}
hpreal InvoluteGear::involuteToCircleAngle(const hpreal &involuteAngle) {
	return involuteAngle - glm::atan(involuteAngle);
}
hpvec2 InvoluteGear::mirrorPoint(const hpvec2 &point, const hpvec2 &axis){
	hpvec2 normal = glm::normalize(hpvec2(-axis.y, axis.x));
	return (point - (normal * (glm::dot(normal, point) * 2.0f)));
}
hpuint* InvoluteGear::getPossibleNumbersOfTeeth() {
	hpuint minCount = 3;
	hpuint maxCount = 30; //TODO: How can we set a good max value here?
	return getPossibleValues<hpuint>(m_nTeeth, minCount, maxCount, 1);
}
hpreal *InvoluteGear::getPossibleModules() {
	hpreal minSize = 0.0f;
	hpreal maxSize = 1.5f; //TODO: How can we set a good max value here?
	hpreal sampleSize = (m_module == 0.0f) ? 0.000001f : m_module / 100.0f;
	return getPossibleValues<hpreal>(m_module, minSize, maxSize, sampleSize);
}
hpreal *InvoluteGear::getPossiblePressureAngles() {
	hpreal minSize = M_PI / 180.0f;
	hpreal maxSize = M_PI / 2.0f;
	hpreal sampleSize = (m_pressureAngle == 0.0f) ? 0.000001f : m_pressureAngle / 100.0f;
	return getPossibleValues<hpreal>(m_pressureAngle, minSize, maxSize, sampleSize);
}
hpreal *InvoluteGear::getPossibleBottomClearances() {
	hpreal minSize = 0.0f;
	hpreal maxSize = getReferenceRadius() - m_module - getBaseRadius() + m_filletRadius;
	hpreal sampleSize = (glm::min(m_bottomClearance, m_filletRadius) / 10.0f);
	if (sampleSize <= 0.0f)
		sampleSize = (glm::max(m_bottomClearance, m_filletRadius) / 10.0f);
	if (sampleSize <= 0.0f)
		sampleSize = (maxSize - minSize) / 100;
	return getPossibleValues<hpreal>(m_bottomClearance, minSize, maxSize, sampleSize);
}
hpreal *InvoluteGear::getPossibleFilletRadien() {
	hpreal minSize = 0.0f;
	hpreal maxSize = getAngularPitch() / 4;
	hpreal sampleSize = (glm::min(m_bottomClearance, m_filletRadius) / 10.0f);
	if (sampleSize <= 0.0f)
		sampleSize = (glm::max(m_bottomClearance, m_filletRadius) / 10.0f);
	if (sampleSize <= 0.0f)
		sampleSize = (maxSize - minSize) / 100;
	return getPossibleValues<hpreal>(m_filletRadius, minSize, maxSize, sampleSize);
}
bool InvoluteGear::setNumberOfTeeth(hpuint nTeeth) {
	hpuint oldValue = m_nTeeth;
	m_nTeeth = nTeeth;
	if (!verifyConstraints()) {
		m_nTeeth = oldValue;
		return false;
	}
	return true;
}
bool InvoluteGear::setModule(hpreal module) {
	hpreal oldValue = m_module;
	m_module = module;
	if(!verifyConstraints()) {
		m_module = oldValue;
		return false;
	}
	return true;
}
//Actually there is not constraint concerning the facewidth at the moment. But maybe there will be one in the future. Therefore constraints are tested anyway.
bool InvoluteGear::setFaceWidth(hpreal faceWidth) {
	hpreal oldValue = m_faceWidth;
	m_faceWidth = faceWidth;
	if(!verifyConstraints()) {
		m_faceWidth = oldValue;
		return false;
	}
	return true;
}
bool InvoluteGear::setPressureAngle(hpreal pressureAngle) {
	hpreal oldValue = m_pressureAngle;
	m_pressureAngle = pressureAngle;
	if(!verifyConstraints()) {
		m_pressureAngle = oldValue;
		return false;
	}
	return true;
}
bool InvoluteGear::setBottomClearance(hpreal bottomClearance) {
	hpreal oldValue = m_bottomClearance;
	m_bottomClearance = bottomClearance;
	if(!verifyConstraints()) {
		m_bottomClearance = oldValue;
		return false;
	}
	return true;
}
bool InvoluteGear::setFilletRadius(hpreal filletRadius) {
	hpreal oldValue = m_filletRadius;
	m_filletRadius = filletRadius;
	if(!verifyConstraints()) {
		m_filletRadius = oldValue;
		return false;
	}
	return true;
}
bool InvoluteGear::setHelixAngle(hpreal helixAngle) {
	if( -(M_PI / 2.0f) < helixAngle && helixAngle < (M_PI / 2.0f) ) {
		m_helixAngle = helixAngle;
		return true;
	} else {
		return false;
	}
}

template <class T>
T *InvoluteGear::getPossibleValues(T &testParameter, T minSize, T maxSize, T sampleSize) {

	if (!verifyConstraints()) cerr << "THIS MUST NOT HAPPEN!" << endl; //TODO throw error or something like this instead of this line

	hpuint steps = (maxSize - minSize) / sampleSize;
	T min = maxSize;
	T max = minSize;
	T savedParameter = testParameter;
	bool rangeFound = false;
	bool suitableRangeFound = false;

	for (hpuint i = 0; i < steps && !suitableRangeFound; ++i) {
		T test = minSize + sampleSize * i;
		testParameter = test;
		if (verifyConstraints()) {
			rangeFound = true;
			min = glm::min(min, test);
			max = glm::max(max, test);
		} else if (rangeFound) {
			if(savedParameter > max || savedParameter < min) {
				// testParameter isn't in the found range => there has to be another range - search for it
				min = maxSize;
				max = test;
				rangeFound = false;
			} else {
				// testParameter is in the found range => search can be finished
				suitableRangeFound = true;
			}
		}
	}
	if (min > max) {
		min = savedParameter;
		max = savedParameter;
	}
	testParameter = savedParameter;
	T *minmax = new T[2];
	minmax[0] = min;
	minmax[1] = max;
	return minmax;
}

void InvoluteGear::getToothSpaceProfile(vector<hpvec2> &profile) const {
	//TODO: implement method
}

void InvoluteGear::getToothProfile(vector<hpvec2>& toothProfile) {

	hpuint toothSampleSize = toothProfile.size();

	if (!verifyConstraints()) {
		return;
	}

	//angles of important locations of the toothprofile
	//alpha for involute construction, beta is the "normal" angle, one would expect in a circle
	hpreal beta1; //start fillet (Fußrundung)
	hpreal beta2, alpha2; //end fillet (Fußrundung)
	hpreal beta3, alpha3; //start tip circle (Kopfkreis)

	alpha2 = getStopFilletInvoluteAngle();
	beta1  = getShiftAngle() - getStartFilletAngle();
	beta2  = getShiftAngle() + alpha2 - glm::atan(alpha2);
	alpha3 = involuteAngleOfIntersectionWithCircle(getTipRadius());
	beta3  = getShiftAngle() + involuteToCircleAngle(alpha3);

	hpreal sampleAngleSize = getAngularPitch() / toothSampleSize;
	int sampleBeta1 = static_cast<hpuint>(beta1 / sampleAngleSize + 0.5);
	int sampleBeta2 = static_cast<hpuint>(beta2 / sampleAngleSize + 0.5);
	int sampleBeta3 = static_cast<hpuint>(beta3 / sampleAngleSize + 0.5);
	int sampleBeta4 = (toothSampleSize % 2 == 0) ? toothSampleSize / 2 : toothSampleSize / 2 + 1;

	//if assertion fails, values haven't been possible for involute gear and construction would fail!
	assert(sampleBeta1 >= 0
		&& sampleBeta2 >= sampleBeta1
		&& sampleBeta3 >= sampleBeta2
		&& sampleBeta4 >= sampleBeta3);

	insertCirclePoints(  toothProfile,           0, sampleBeta1, sampleAngleSize, getRootRadius());
	insertFilletPoints(  toothProfile, sampleBeta1, sampleBeta2, sampleAngleSize, alpha2);
	insertInvolutePoints(toothProfile, sampleBeta2, sampleBeta3, alpha2, alpha3);
	insertCirclePoints(  toothProfile, sampleBeta3, sampleBeta4, sampleAngleSize, getTipRadius());

}

void InvoluteGear::insertCirclePoints(vector<hpvec2> &v, const hpuint &start, const hpuint &stopBefore,
		const hpreal &sampleAngleSize, const hpreal &radius) {
	for (hpuint i = start; i < stopBefore; ++i) {
		v[i].x = radius * glm::sin(sampleAngleSize * i);
		v[i].y = radius * glm::cos(sampleAngleSize * i);
		hpuint j = v.size() - 1 - i; //mirrored side
		v[j].x = radius * glm::sin(sampleAngleSize * j);
		v[j].y = radius * glm::cos(sampleAngleSize * j);
	}
}
void InvoluteGear::insertFilletPoints(vector<hpvec2> &v, const hpuint &start, const hpuint &stopBefore,
		const hpreal &sampleAngleSize, const hpreal &touchEvolvAngle) {

	hpreal shift = getShiftAngle();
	hpvec2 involutePoint = pointOnRightTurnedInvolute(shift, touchEvolvAngle);
	hpvec2 center;
	center.x = involutePoint.x - m_filletRadius * glm::cos(shift + touchEvolvAngle);
	center.y = involutePoint.y + m_filletRadius * glm::sin(shift + touchEvolvAngle);
	hpreal mirrorAngle = getAngularPitch() / 2.0f;
	hpvec2 mirrorAxis = hpvec2(sin(mirrorAngle), cos(mirrorAngle));

	for (hpuint i = start; i < stopBefore; ++i) {
		hpvec2 direction;
		direction.x = glm::sin(i * sampleAngleSize);
		direction.y = glm::cos(i * sampleAngleSize);
		hpreal dc = glm::dot(direction, center);
		hpreal cc = glm::dot(center, center);
		hpreal t = dc - (sqrt(dc * dc - cc + m_filletRadius * m_filletRadius));

		v[i] = direction * t;
		v[v.size() - 1 - i] = mirrorPoint(v[i], mirrorAxis);
	}
}

void InvoluteGear::insertInvolutePoints(vector<hpvec2> &v, const hpuint &start, const hpuint &stopBefore,
		const hpreal &startInvAngle, const hpreal &stopInvAngle) {

	hpreal mirrorAngle = getAngularPitch() / 2.0f;
	hpvec2 mirrorAxis = hpvec2(sin(mirrorAngle), cos(mirrorAngle));
	hpreal angleStep = (stopInvAngle - startInvAngle) / (stopBefore - start);

	for (hpuint i = start; i < stopBefore; ++i) {
		v[i] = pointOnRightTurnedInvolute(getShiftAngle(), startInvAngle + (i - start) * angleStep);
		v[v.size() - 1 - i] = mirrorPoint(v[i], mirrorAxis);
	}
}

hpvec2 InvoluteGear::pointOnRightTurnedInvolute(const hpreal &involuteStartAngle, const hpreal &angle){
	hpreal radius = getBaseRadius();
	hpvec2 point;
	point.x = radius * glm::sin(involuteStartAngle + angle) - radius * angle * glm::cos(involuteStartAngle + angle);
	point.y = radius * glm::cos(involuteStartAngle + angle) + radius * angle * glm::sin(involuteStartAngle + angle);
	return point;
}
TriangleMesh* InvoluteGear::toTriangleMesh(hpuint toothSampleSize, hpuint zSampleSize) {

	TriangleMesh* mesh = CylindricalGear::toTriangleMesh(toothSampleSize, zSampleSize);
	vector<hpvec2> profile(toothSampleSize * getNumberOfTeeth());
	//TODO: replace following two lines with good value for innerGearRadius
	getTraverseProfile(0, profile);
	hpreal innerGearRadius = glm::length(profile[0]) / 2.0f;
	vector<hpvec3>* vertexData = mesh->getVertexData();
	vector<hpuint>* indices = mesh->getIndices();

	for(hpuint side = 0; side < 2; ++side) {
		getTraverseProfile(side * getFaceWidth(), profile);
		hpreal z = side * getFaceWidth();
		hpuint startIndex = vertexData->size() / 2;
		hpvec3 normal = hpvec3(0.0f, 0.0f, 1.0f);
		if (side == 1)
			normal *= -1.0f;
		for(vector<hpvec2>::iterator it = profile.begin(), end = profile.end(); it != end; ++it) {
			hpvec2 currentProfilePoint = *it;
			hpvec2 currentInnerPoint = glm::normalize(currentProfilePoint) * innerGearRadius;

			vertexData->push_back(hpvec3(currentInnerPoint, z));
			vertexData->push_back(normal);
			vertexData->push_back(hpvec3(currentProfilePoint, z));
			vertexData->push_back(normal);
		}

		hpuint nNewIndices = vertexData->size() / 2 - 2;
		for(hpuint i = startIndex, g = 0; i < nNewIndices; ++i, ++g) {
			indices->push_back(i);
			if(g % 2 == 0) {
				indices->push_back(i + 1);
				indices->push_back(i + 2);
			} else {
				indices->push_back(i + 2);
				indices->push_back(i + 1);
			}
		}
		indices->push_back(vertexData->size() / 2 - 2);
		indices->push_back(vertexData->size() / 2 - 1);
		indices->push_back(startIndex);

		indices->push_back(vertexData->size() / 2 - 1);
		indices->push_back(startIndex);
		indices->push_back(startIndex + 1);
	}
	return mesh;
}

SimpleGear* InvoluteGear::toSimpleGear(hpuint toothSampleSize) {
	BSplineGearCurve *toothProfileCurve = new BSplineGearCurve();
	toothProfileCurve->setDegree(1);
	toothProfileCurve->setPeriodic(false);
	vector<hpvec2> toothProfilePoints(toothSampleSize);
	getToothProfile(toothProfilePoints);
	toothProfileCurve->approximatePoints(&toothProfilePoints, toothSampleSize);
	SimpleGear *simpleGear = new SimpleGear(toothProfileCurve, m_helixAngle, m_faceWidth);
	return simpleGear;
}
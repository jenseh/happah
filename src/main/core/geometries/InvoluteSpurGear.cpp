#include "InvoluteSpurGear.h"
#include <exception> //TODO: delete this or put it in header!

// Constructor for a general gear. Gears are always centered on 0,0,0 with the z axis being the gear axis.
InvoluteSpurGear::InvoluteSpurGear(uint toothCount, hpreal module, hpreal facewidth, hpreal pressureAngle,
                   hpreal bottomClearance, hpreal filletRadius, hpreal helixAngle, std::string name) : Gear(name),
                   m_toothCount(toothCount), m_module(module), m_facewidth(facewidth),
                   m_pressureAngle(pressureAngle),
                   m_bottomClearance(bottomClearance), m_filletRadius(filletRadius), m_helixAngle(helixAngle) {

	//std::cout << toString() << std::endl;
}

InvoluteSpurGear::InvoluteSpurGear(const InvoluteSpurGear& other) : Gear(other.m_name),
				m_toothCount(other.m_toothCount), m_module(other.m_module), m_facewidth(other.m_facewidth),
				m_pressureAngle(other.m_pressureAngle), m_bottomClearance(other.m_bottomClearance),
				m_filletRadius(other.m_filletRadius), m_helixAngle(other.m_helixAngle) {
}

InvoluteSpurGear::~InvoluteSpurGear() {}

//TODO: do we need this?
InvoluteSpurGear& InvoluteSpurGear::operator=(const InvoluteSpurGear& other) {
	m_toothCount = other.m_toothCount;
	m_module = other.m_module;
	m_facewidth = other.m_facewidth;
	m_pressureAngle = other.m_pressureAngle;
	m_bottomClearance = other.m_bottomClearance;
	m_filletRadius = other.m_filletRadius;
	m_helixAngle = other.m_helixAngle;
	m_name = other.m_name;
}

bool InvoluteSpurGear::verifyConstraints(bool print) {
	bool isCorrect = true;
	try {
		if (m_toothCount <= 2) {
			isCorrect = false;
			throw "No involutes possible with only two or less teeth!";
		}
		if (m_pressureAngle >= M_PI / 2.0f) {
			isCorrect = false;
			throw "Pressure angle is too big. This would be a circle.";
		}
		if (getBaseRadius() > getReferenceRadius() - m_module) {
			isCorrect = false;
			throw "Working depth (gemeinsame Zahnhöhe) starts earlier than involute can start!";
		}
		if ((pow((getRootRadius() + m_filletRadius) / getBaseRadius(), 2.0f)) - 1.0f < 0.0f) {
			isCorrect = false;
			throw "Bottom clearance is too big!";
		}
	} catch (char const* s) {
		if (print) std::cerr << s << std::endl;
	}

	//start fillet has to be in first quarter of the angular pitch
	try {
		if (getStopFilletInvoluteAngle() < 0) {
			isCorrect = false;
			throw "Fillet and involute can't merge as fillet radius is too small or bottom clearance too big!";
		}
		if (getShiftAngle() - getStartFilletAngle() < 0) {
			isCorrect = false;
			throw "Fillet is too big for the gap between the teeth!";
		}
//		if (getStopFilletInvoluteAngle() 
//			> involuteAngleOfIntersectionWithCircle(getReferenceRadius() - m_module)) {
//			isCorrect = false;
//			throw "Fillet ends when working depth (gemeinsame Zahnhöhe) already started!";
//		}
	} catch (char const* s) {
		if (print) std::cerr << s << std::endl;
	} catch (std::exception &e) {
		isCorrect = false;
		if (print) std::cerr << e.what() << std::endl;
	}
	return isCorrect;
}

uint   InvoluteSpurGear::getToothCount() { return m_toothCount; }
hpreal InvoluteSpurGear::getModule() { return m_module; }
hpreal InvoluteSpurGear::getFacewidth() { return m_facewidth; }
hpreal InvoluteSpurGear::getPressureAngle() { return m_pressureAngle; }
hpreal InvoluteSpurGear::getBottomClearance() { return m_bottomClearance; }
hpreal InvoluteSpurGear::getFilletRadius() { return m_filletRadius; }
hpreal InvoluteSpurGear::getHelixAngle() { return m_helixAngle; }

//Teilkreisradius - where width of gaps and width of teeths have same size
hpreal InvoluteSpurGear::getReferenceRadius() {
	return m_toothCount * m_module / 2.0f;
}
//Kopfkreisradius
hpreal InvoluteSpurGear::getTipRadius() {
	return getReferenceRadius() + m_module;
}
//Fußkreisradius
hpreal InvoluteSpurGear::getRootRadius() {
	return (getReferenceRadius() - m_module - m_bottomClearance);
}
//Grundkreisradius 
hpreal InvoluteSpurGear::getBaseRadius() {
	return getReferenceRadius() * glm::cos(m_pressureAngle);
}
//Teilungswinkel
hpreal InvoluteSpurGear::getAngularPitch() {
	return 2.0f * M_PI / getToothCount();
}
hpreal InvoluteSpurGear::getStopFilletInvoluteAngle() {
	hpreal ratio = pow((getRootRadius() + m_filletRadius) / getBaseRadius(), 2.0f);
	return ((sqrt(ratio - 1.0f)) - (m_filletRadius / getBaseRadius()));
}
hpreal InvoluteSpurGear::getStartFilletAngle() {
	hpreal tangens = ((m_filletRadius + getStopFilletInvoluteAngle() * getBaseRadius()) / getBaseRadius());
	return glm::atan(tangens) - getStopFilletInvoluteAngle();
}
hpreal InvoluteSpurGear::getShiftAngle() {
	hpreal intersectRefRadius = involuteToCircleAngle(involuteAngleOfIntersectionWithCircle(getReferenceRadius()));
	return getAngularPitch() / 4.0f - intersectRefRadius;
}
hpreal InvoluteSpurGear::involuteAngleOfIntersectionWithCircle(const hpreal &radius) {
	return glm::sqrt(pow(radius / getBaseRadius(), 2) - 1.0f); 
}
hpreal InvoluteSpurGear::involuteToCircleAngle(const hpreal &involuteAngle) {
	return involuteAngle - glm::atan(involuteAngle);
}
hpvec2 InvoluteSpurGear::mirrorPoint(const hpvec2 &point, const hpvec2 &axis){
	hpvec2 normal = glm::normalize(hpvec2(-axis.y, axis.x));
	return (point - (normal * (glm::dot(normal, point) * 2.0f)));
}
uint* InvoluteSpurGear::getPossibleToothCounts() {
	uint minCount = 3;
	uint maxCount = 30; //TODO: How can we set a good max value here?
	return getPossibleValues<uint>(m_toothCount, minCount, maxCount, 1);
}
hpreal *InvoluteSpurGear::getPossibleModules() {
	hpreal minSize = 0.0f;
	hpreal maxSize = 1.5f; //TODO: How can we set a good max value here?
	hpreal sampleSize = (m_module == 0.0f) ? 0.000001f : m_module / 100.0f;
	return getPossibleValues<hpreal>(m_module, minSize, maxSize, sampleSize);
}
hpreal *InvoluteSpurGear::getPossiblePressureAngles() {
	hpreal minSize = M_PI / 180.0f;
	hpreal maxSize = M_PI / 2.0f;
	hpreal sampleSize = (m_pressureAngle == 0.0f) ? 0.000001f : m_pressureAngle / 100.0f;
	return getPossibleValues<hpreal>(m_pressureAngle, minSize, maxSize, sampleSize);
}
hpreal *InvoluteSpurGear::getPossibleBottomClearances() {
	hpreal minSize = 0.0f;
	hpreal maxSize = getReferenceRadius() - m_module - getBaseRadius() + m_filletRadius;
	hpreal sampleSize = (glm::min(m_bottomClearance, m_filletRadius) / 10.0f);
	if (sampleSize <= 0.0f)
		sampleSize = (glm::max(m_bottomClearance, m_filletRadius) / 10.0f);
	if (sampleSize <= 0.0f)
		sampleSize = (maxSize - minSize) / 100;
	return getPossibleValues<hpreal>(m_bottomClearance, minSize, maxSize, sampleSize);
}
hpreal *InvoluteSpurGear::getPossibleFilletRadien() {
	hpreal minSize = 0.0f;
	hpreal maxSize = getAngularPitch() / 4;
	hpreal sampleSize = (glm::min(m_bottomClearance, m_filletRadius) / 10.0f);
	if (sampleSize <= 0.0f)
		sampleSize = (glm::max(m_bottomClearance, m_filletRadius) / 10.0f);
	if (sampleSize <= 0.0f)
		sampleSize = (maxSize - minSize) / 100;
	return getPossibleValues<hpreal>(m_filletRadius, minSize, maxSize, sampleSize);
}
bool InvoluteSpurGear::setToothCount(uint toothCount) {
	uint oldValue = m_toothCount;
	m_toothCount = toothCount;
	if (!verifyConstraints()) {
		m_toothCount = oldValue;
		return false;
	}
	return true;
}
bool InvoluteSpurGear::setModule(hpreal module) {
	hpreal oldValue = m_module;
	m_module = module;
	if(!verifyConstraints()) {
		m_module = oldValue;
		return false;
	}
	return true;
}
//Actually there is not constraint concerning the facewidth at the moment. But maybe there will be one in the future. Therefore constraints are tested anyway.
bool InvoluteSpurGear::setFacewidth(hpreal facewidth) {
	hpreal oldValue = m_facewidth;
	m_facewidth = facewidth;
	if(!verifyConstraints()) {
		m_facewidth = oldValue;
		return false;
	}
	return true;
}
bool InvoluteSpurGear::setPressureAngle(hpreal pressureAngle) {
	hpreal oldValue = m_pressureAngle;
	m_pressureAngle = pressureAngle;
	if(!verifyConstraints()) {
		m_pressureAngle = oldValue;
		return false;
	}
	return true;
}
bool InvoluteSpurGear::setBottomClearance(hpreal bottomClearance) {
	hpreal oldValue = m_bottomClearance;
	m_bottomClearance = bottomClearance;
	if(!verifyConstraints()) {
		m_bottomClearance = oldValue;
		return false;
	}
	return true;
}
bool InvoluteSpurGear::setFilletRadius(hpreal filletRadius) {
	hpreal oldValue = m_filletRadius;
	m_filletRadius = filletRadius;
	if(!verifyConstraints()) {
		m_filletRadius = oldValue;
		return false;
	}
	return true;
}
bool InvoluteSpurGear::setHelixAngle(hpreal helixAngle) {
	if( -(M_PI / 2.0f) < helixAngle && helixAngle < (M_PI / 2.0f) ) {
		m_helixAngle = helixAngle;
		return true;
	} else {
		return false;
	}
}

template <class T>
T *InvoluteSpurGear::getPossibleValues(T &testParameter, T minSize, T maxSize, T sampleSize) {

	if (!verifyConstraints()) std::cerr << "THIS MUST NOT HAPPEN!" << std::endl; //TODO throw error or something like this instead of this line

	uint steps = (maxSize - minSize) / sampleSize;
	T min = maxSize;
	T max = minSize;
	T savedParameter = testParameter;
	bool rangeFound = false;
	bool suitableRangeFound = false;

	for (uint i = 0; i < steps && !suitableRangeFound; ++i) {
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

std::vector<hpvec2>* InvoluteSpurGear::getToothProfile() {

	std::vector<hpvec2>* profile = new std::vector<hpvec2>(TOOTH_SAMPLE_SIZE);

	if (!verifyConstraints()) {
		return profile;
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

	hpreal sampleAngleSize = getAngularPitch() / TOOTH_SAMPLE_SIZE;
	int sampleBeta1 = static_cast<uint>(beta1 / sampleAngleSize + 0.5);
	int sampleBeta2 = static_cast<uint>(beta2 / sampleAngleSize + 0.5);
	int sampleBeta3 = static_cast<uint>(beta3 / sampleAngleSize + 0.5);
	int sampleBeta4 = (TOOTH_SAMPLE_SIZE % 2 == 0) ? TOOTH_SAMPLE_SIZE / 2 : TOOTH_SAMPLE_SIZE / 2 + 1;

	//if assertion fails, values haven't been possible for involute gear and construction would fail!
	assert(sampleBeta1 >= 0
		&& sampleBeta2 >= sampleBeta1
		&& sampleBeta3 >= sampleBeta2
		&& sampleBeta4 >= sampleBeta3);

	insertCirclePoints(  *profile,           0, sampleBeta1, sampleAngleSize, getRootRadius());
	insertFilletPoints(  *profile, sampleBeta1, sampleBeta2, sampleAngleSize, alpha2);
	insertInvolutePoints(*profile, sampleBeta2, sampleBeta3, alpha2, alpha3);
	insertCirclePoints(  *profile, sampleBeta3, sampleBeta4, sampleAngleSize, getTipRadius());

	return profile;
}

void InvoluteSpurGear::insertCirclePoints(std::vector<hpvec2> &v, const uint &start, const uint &stopBefore,
		const hpreal &sampleAngleSize, const hpreal &radius) {
	for (uint i = start; i < stopBefore; ++i) {
		v[i].x = radius * glm::sin(sampleAngleSize * i);
		v[i].y = radius * glm::cos(sampleAngleSize * i);
		uint j = v.size() - 1 - i; //mirrored side
		v[j].x = radius * glm::sin(sampleAngleSize * j);
		v[j].y = radius * glm::cos(sampleAngleSize * j);
	}
}
void InvoluteSpurGear::insertFilletPoints(std::vector<hpvec2> &v, const uint &start, const uint &stopBefore,
		const hpreal &sampleAngleSize, const hpreal &touchEvolvAngle) {

	hpreal shift = getShiftAngle();
	hpvec2 involutePoint = pointOnRightTurnedInvolute(shift, touchEvolvAngle);
	hpvec2 center;
	center.x = involutePoint.x - m_filletRadius * glm::cos(shift + touchEvolvAngle);
	center.y = involutePoint.y + m_filletRadius * glm::sin(shift + touchEvolvAngle);
	hpreal mirrorAngle = getAngularPitch() / 2.0f;
	hpvec2 mirrorAxis = hpvec2(sin(mirrorAngle), cos(mirrorAngle));

	for (uint i = start; i < stopBefore; ++i) {
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

void InvoluteSpurGear::insertInvolutePoints(std::vector<hpvec2> &v, const uint &start, const uint &stopBefore,
		const hpreal &startInvAngle, const hpreal &stopInvAngle) {

	hpreal mirrorAngle = getAngularPitch() / 2.0f;
	hpvec2 mirrorAxis = hpvec2(sin(mirrorAngle), cos(mirrorAngle));
	hpreal angleStep = (stopInvAngle - startInvAngle) / (stopBefore - start);

	for (uint i = start; i < stopBefore; ++i) {
		v[i] = pointOnRightTurnedInvolute(getShiftAngle(), startInvAngle + (i - start) * angleStep);
		v[v.size() - 1 - i] = mirrorPoint(v[i], mirrorAxis);
	}
}

hpvec2 InvoluteSpurGear::pointOnRightTurnedInvolute(const hpreal &involuteStartAngle, const hpreal &angle){
	hpreal radius = getBaseRadius();
	hpvec2 point;
	point.x = radius * glm::sin(involuteStartAngle + angle) - radius * angle * glm::cos(involuteStartAngle + angle);
	point.y = radius * glm::cos(involuteStartAngle + angle) + radius * angle * glm::sin(involuteStartAngle + angle);
	return point;
}
/*
std::vector<hpvec2>* InvoluteSpurGear::getGearProfile(hpreal depth) {

	// last point of tooth profile isn't taken because next tooth profile would have the same one
	std::vector<hpvec2> *profile = new std::vector<hpvec2>((TOOTH_SAMPLE_SIZE - 1) * getToothCount());
	std::vector<hpvec2> *toothProfile = getToothProfile();

	//TODO: here we could insert something for the helixangle!
	//TODO: I use this code to refuse an array-resizing, as we know the array size from the beginning
	//But is this really necessary? Is it maybe even faster to use already provided methods?
	for (uint i = 0; i < TOOTH_SAMPLE_SIZE - 1; ++i) {
		profile->at(i) = toothProfile->at(i);
	}

	delete toothProfile; //memory is freed as toothProfile isn't needed any longer

	for (uint i = 1; i < getToothCount(); ++i) {
		hpreal mirrorAngle = getAngularPitch() * (i);
		hpvec2 mirrorAxis = hpvec2(sin(mirrorAngle), cos(mirrorAngle));

		for (uint j = 0; j < TOOTH_SAMPLE_SIZE - 1; ++j) {
			uint k = i * (TOOTH_SAMPLE_SIZE - 1) + j;
			profile->at(k) = mirrorPoint(profile->at(k - 1 - 2 * j), mirrorAxis);
		}
	}

	return profile;
}*/

ZCircleCloud* InvoluteSpurGear::toZCircleCloud() {
	// Create the profile given the current gear settings
	std::vector<hpvec2> *profile = getGearProfile(0);
	
	const unsigned int profSize = profile->size();

	// Determine resolution (important for following simulations)
	const unsigned int resolutionXY = profSize;
	const unsigned int resolutionZ = 10;

	std::vector<glm::vec2>* points = this->getGearProfile(0);
	std::vector<float>* posZ = new std::vector<float>;

	for (unsigned int stepZ = 0; stepZ < resolutionZ; stepZ++) {
		float posZValue = m_facewidth / resolutionZ;
		posZ->push_back(posZValue);
	}

	glm::vec3 referenceDir = glm::vec3(1.0f, 0.0f, 0.0f);

	ZCircleCloud* result = new ZCircleCloud(points, posZ, resolutionXY, resolutionZ, referenceDir);
	result->setModelMatrix(m_modelMatrix);
	return result;
}

SimpleGear* InvoluteSpurGear::toSimpleGear() {
	BSplineCurve *toothProfile = new BSplineCurve();
	toothProfile->setDegree(1);
	toothProfile->setPeriodic(false);
	toothProfile->approximatePoints(getToothProfile(), 20);
	SimpleGear *simpleGear = new SimpleGear(new BSplineToothProfile(toothProfile, 20), m_helixAngle, m_facewidth);
	return simpleGear;
}


std::string InvoluteSpurGear::toString() {
	std::stringstream info;
	info << "Gear:" << std::endl;
	info << "tooth count      = " << getToothCount()<< std::endl;
	info << "module           = " << m_module << std::endl;
	info << "pressure angle   = " << m_pressureAngle << std::endl;
	info << "tip radius       = " << getTipRadius() << std::endl;
	info << "ref. radius      = " << getReferenceRadius() << std::endl;
	info << "base radius      = " << getBaseRadius() << std::endl;
	info << "root radius      = " << getRootRadius() << std::endl;
	info << "fillet radius    = " << m_filletRadius << std::endl;
	info << "bottom clearance = " << m_bottomClearance << std::endl;
	info << "helix angle      = " << m_helixAngle << std::endl;
	info << "angular pitch    = " << getAngularPitch() << std::endl;
	return info.str();
}

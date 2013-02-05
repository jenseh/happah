#include "InvoluteSpurGear.h"
#include <exception> //TODO: delete this or put it in header!

// Constructor for a general gear. Gears are always centered on 0,0,0 with the z axis being the gear axis.
InvoluteSpurGear::InvoluteSpurGear(uint toothCount, hpreal module, hpreal facewidth, hpreal pressureAngle,
                   hpreal bottomClearance, hpreal filletRadius, std::string name) :
                   m_toothCount(toothCount), m_module(module), m_facewidth(facewidth),
                   m_pressureAngle(pressureAngle),
                   m_bottomClearance(bottomClearance), m_filletRadius(filletRadius), NonDrawable(name) {

	//std::cout << toString() << std::endl;
}

InvoluteSpurGear::~InvoluteSpurGear() {}

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
		if (getStopFilletInvoluteAngle() 
			> involuteAngleOfIntersectionWithCircle(getReferenceRadius() - m_module)) {
			isCorrect = false;
			throw "Fillet ends when working depth (gemeinsame Zahnhöhe) already started!";
		}
	} catch (char const* s) {
		if (print) std::cerr << s << std::endl;
	} catch (exception &e) {
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

std::vector<hpvec2>* InvoluteSpurGear::getToothProfile(uint sampleSize) {

	std::vector<hpvec2>* profile = new std::vector<hpvec2>(sampleSize);

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

	hpreal sampleAngleSize = getAngularPitch() / sampleSize;
	int sampleBeta1 = static_cast<uint>(beta1 / sampleAngleSize + 0.5);
	int sampleBeta2 = static_cast<uint>(beta2 / sampleAngleSize + 0.5);
	int sampleBeta3 = static_cast<uint>(beta3 / sampleAngleSize + 0.5);
	int sampleBeta4 = (sampleSize % 2 == 0) ? sampleSize / 2 : sampleSize / 2 + 1;

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

std::vector<hpvec2>* InvoluteSpurGear::getGearProfile(uint toothSampleSize) {

	// last point of tooth profile isn't taken because next tooth profile would have the same one
	std::vector<hpvec2> *profile = new std::vector<hpvec2>((toothSampleSize - 1) * getToothCount());
	std::vector<hpvec2> *toothProfile = getToothProfile(toothSampleSize);

	//TODO: I use this code to refuse an array-resizing, as we know the array size from the beginning
	//But is this really necessary? Is it maybe even faster to use already provided methods?
	for (uint i = 0; i < toothSampleSize - 1; ++i) {
		profile->at(i) = toothProfile->at(i);
	}
	//TODO: irgendwie muss speicherplatz für toothprofile freigegeben werden!

	for (uint i = 1; i < getToothCount(); ++i) {
		//TODO: Katja please look at this: I changed i to i + 1 since
		// otherwise there would be 2 equal points in a sequence and
		// that would lead to corrupt normals in my simulation...
		hpreal mirrorAngle = getAngularPitch() * (i);
		hpvec2 mirrorAxis = hpvec2(sin(mirrorAngle), cos(mirrorAngle));

		for (uint j = 0; j < toothSampleSize - 1; ++j) {
			uint k = i * (toothSampleSize - 1) + j;
			profile->at(k) = mirrorPoint(profile->at(k - 1 - 2 * j), mirrorAxis);
		}
	}

	return profile;
}

TriangleMesh* InvoluteSpurGear::toTriangleMesh(uint toothSampleSize, uint widthSampleSize) {
    std::vector<hpvec4>* vertexData = toMesh(toothSampleSize, widthSampleSize, &InvoluteSpurGear::putTogetherAsTriangles);
    smoothTriangleMeshNormals(vertexData, widthSampleSize);
    TriangleMesh* mesh = new TriangleMesh(*vertexData, m_name + " - Instance ");
    mesh->setModelMatrix(m_modelMatrix);
    return mesh;
}

void InvoluteSpurGear::putTogetherAsTriangles(const hpvec4 (&points)[4], const hpvec4 &normal, std::vector<hpvec4> *&vertexData) {
			//first triangle
			vertexData->push_back(points[0]);
			vertexData->push_back(normal);
			vertexData->push_back(points[1]);
			vertexData->push_back(normal);
			vertexData->push_back(points[2]);
			vertexData->push_back(normal);
			//second triangle
			vertexData->push_back(points[0]);
			vertexData->push_back(normal);
			vertexData->push_back(points[2]);
			vertexData->push_back(normal);
			vertexData->push_back(points[3]);
			vertexData->push_back(normal);
}

QuadMesh* InvoluteSpurGear::toQuadMesh(uint toothSampleSize, uint widthSampleSize) {
    std::vector<hpvec4>* vertexData = toMesh(toothSampleSize, widthSampleSize, &InvoluteSpurGear::putTogetherAsQuads);
    QuadMesh* mesh = new QuadMesh(*vertexData, m_name + " - Instance 1");
    mesh->setModelMatrix(m_modelMatrix);
    return mesh;
}

void InvoluteSpurGear::putTogetherAsQuads(const hpvec4 (&points)[4], const hpvec4 &normal, std::vector<hpvec4> *&vertexData) {
	vertexData->push_back(points[0]);
	vertexData->push_back(normal);
	vertexData->push_back(points[1]);
	vertexData->push_back(normal);
	vertexData->push_back(points[2]);
	vertexData->push_back(normal);
	vertexData->push_back(points[3]);
	vertexData->push_back(normal);
}

std::vector<hpvec4>* InvoluteSpurGear::toMesh(uint toothSampleSize, uint widthSampleSize,
		void (InvoluteSpurGear::*putTogetherAs)(const hpvec4(&)[4], const hpvec4&, std::vector<hpvec4>*&)) {
	// Create vector for the result
	std::vector<hpvec4> *vertexData = new std::vector<hpvec4>;
	std::vector<hpvec2> *profile = getGearProfile(toothSampleSize);

	hpreal dz = m_facewidth / widthSampleSize;

	hpvec4 wildcard = hpvec4(1.0f);

	for (uint i = 0; i < widthSampleSize; ++i) {
		for (uint j = 0; j < profile->size(); ++j) {
			//TODO: why can't I use points[0].xy = ... ?
			uint jNext = (j == profile->size() - 1) ? 0 : (j + 1);
			hpvec4 points[4];
			points[0].x = profile->at(jNext).x;
			points[0].y = profile->at(jNext).y;
			points[0].z = i * dz;
			points[0].w = 1.0f;
			points[1].x = profile->at(j).x;
			points[1].y = profile->at(j).y;
			points[1].z = i * dz;
			points[1].w = 1.0f;
			points[2].x = profile->at(j).x;
			points[2].y = profile->at(j).y;
			points[2].z = (i + 1) * dz;
			points[2].w = 1.0f;
			points[3].x = profile->at(jNext).x;
			points[3].y = profile->at(jNext).y;
			points[3].z = (i + 1) * dz;
			points[3].w = 1.0f;
			
			(this->*putTogetherAs)(points, wildcard, vertexData);
		}
	}
	//TODO profile Speicher freigeben!
	return vertexData;
}

void InvoluteSpurGear::smoothTriangleMeshNormals(std::vector<hpvec4> *&vertexData, uint numOfRows) {
	//12 entries per knot of the profile in a triangleMesh (2 * 3 points, each with a normal)
	uint pointsInRow = vertexData->size() / numOfRows;
	uint quadsInRow  = pointsInRow / 12;
	//array steps is necessary to walk in the vertexData array to the right places
	int steps[] = {0, 6, 8, -(pointsInRow - 6), -4, -6};

	for(uint i = 0; i < numOfRows; ++i) {
		for (uint j = 0; j < quadsInRow; ++j) {
			std::vector<hpvec3> nnnormals;//not normalized normals as size is needed for smoothing
			hpreal areaSum = 0.0f;

			//calculate not normalized normals of the 6
			//surrounding triangles and sum their area
			//for every point of the gear profile
			for (uint k = 0; k < 6; ++k) {
				int da, db; //distances in vertexData array to other two triangle points
				if(k < 2) {
					da = 4; db = 2;
				} else if (k < 4) {
					da = -2; db = 2;
				} else {
					da = -2; db = -4;
				}

				//TODO: n ist int und wird mit uint verglichen! => static_cast???
				int n = i * pointsInRow + j * 12 + steps[k];
				if (k == 2 && j == quadsInRow - 1)
					n-= pointsInRow;
				//not every point has 6 surrounding triangles. Use only the ones available:
				if (n >= 0 && n < vertexData->size()) {
					hpvec4 a = vertexData->at(n + da) - vertexData->at(n);
					hpvec4 b = vertexData->at(n + db) - vertexData->at(n);
					nnnormals.push_back(hpvec3(glm::cross(hpvec3(a.x, a.y, a.z), hpvec3(b.x, b.y, b.z))));
					areaSum += glm::length(nnnormals.back());
				}
			}
			hpvec4 normal = hpvec4(0.0f);
			for (uint k = 0; k < nnnormals.size(); ++k) {
				hpreal weight = (glm::length(nnnormals[k])) / areaSum;
				normal += hpvec4(weight * glm::normalize(nnnormals[k]), 1.0f);
			}
			for (uint k = 0; k < 6; ++k) {
				int n = i * pointsInRow + j * 12 + steps[k];
				if (k == 2 && j == quadsInRow - 1)
					n-= pointsInRow;
				//not every point has 6 surrounding triangles. Use only the ones available:
				if (n >= 0 && n < vertexData->size())
					vertexData->at(n + 1) = normal; //insert the normal in the cell after the vertex
			}
		}
	}
}

ZCircleCloud* InvoluteSpurGear::toZCircleCloud() {
	// Create the profile given the current gear settings
	std::vector<hpvec2> *profile = getGearProfile();
	
	const unsigned int profSize = profile->size();

	// Determine resolution (important for following simulations)
	const unsigned int resolutionXY = profSize;
	const unsigned int resolutionZ = 10;

	std::vector<glm::vec2>* points = this->getGearProfile();
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
	info << "angular pitch    = " << getAngularPitch() << std::endl;
	return info.str();
}

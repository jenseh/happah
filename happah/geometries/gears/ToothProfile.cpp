#include "happah/geometries/gears/ToothProfile.h"
#include "glm/gtx/rotate_vector.hpp"
#include <vector>
#include <iostream>

ToothProfile::ToothProfile() {
	m_toothProfileCurve = BSplineCurve<hpvec3>();
	m_toothProfileCurve.setClamped(true);
	m_toothProfileCurve.setDegree(3);
}

ToothProfile::ToothProfile(const BSplineCurve<hpvec2>& toothProfile) {
	BSplineCurve<hpvec3>* curve = toothProfile.to3dBSplineCurve();
	m_toothProfileCurve = BSplineCurve<hpvec3>(*curve);
	delete curve;
	ensureClamping();
}

ToothProfile::ToothProfile(const BSplineCurve<hpvec3>& toothProfile) : m_toothProfileCurve(toothProfile) {
	ensureClamping();
}

ToothProfile::~ToothProfile() {
}

hpreal ToothProfile::getAngularPitch() const {
	hpvec3 first, last;
	getFirstAndLastPoint(first, last);
	// if angularPitch > PI (more than half of circle), concstruction will fail!
	return glm::acos((glm::dot(glm::normalize(first), glm::normalize(last))));
}

//TODO: Maybe turning in xy plane before ???
void ToothProfile::getCurve(BSplineCurve<hpvec2>& curve) const {
	BSplineCurve<hpvec2>* profile2d = m_toothProfileCurve.to2dBSplineCurve();
	curve = BSplineCurve<hpvec2>(*profile2d);
	delete profile2d;
}

void ToothProfile::getCurve(BSplineCurve<hpvec3>& curve) const {
	curve = BSplineCurve<hpvec3>(m_toothProfileCurve);
}

hpuint ToothProfile::getNumberOfPoints() const {
	return m_toothProfileCurve.getNumberOfControlPoints();
}

hpuint ToothProfile::getNumberOfTeeth() const {
	return (hpuint) floor(((M_PI * 2.0) / getAngularPitch()) + 0.5);
}

Plane* ToothProfile::getPlaneToothProfileLiesIn() const {
	hpvec3 first, last;
	getFirstAndLastPoint(first, last);
	hpvec3 origin = hpvec3(0.0f, 0.0f, 0.0f);
	if(first == last) {
		if(first == origin)
			return new Plane(origin, hpvec3(0.0f, 0.0f, 1.0f));
		if(first != hpvec3(1.0f, 0.0f, 0.0f))
			first = hpvec3(1.0f, 0.0f, 0.0f);
		else //first == hpvec3(1.0f, 0.0f, 0.0f);
			first = hpvec3(0.0f, 1.0f, 0.0f);
	}
	return new Plane(hpvec3(0.0f, 0.0f, 0.0f), glm::cross(last, first));
}

hpreal ToothProfile::getRootRadius() const {
	hpreal min = glm::length(m_toothProfileCurve.getValueAt(0));
	for(unsigned int i = 1; i <= 100; ++i) {
		hpreal value = glm::length(m_toothProfileCurve.getValueAt((1.0f / 100) * i));
		if (value < min)
			min = value;
	}
	return min;
}

hpreal ToothProfile::getTipRadius() const {
	hpreal max = glm::length(m_toothProfileCurve.getValueAt(0));
	for(unsigned int i = 1; i <= 100; ++i) {
		hpreal value = glm::length(m_toothProfileCurve.getValueAt((1.0f / 100) * i));
		if (value > max)
			max = value;
	}
	return max;
}

bool ToothProfile::liesInXYPlane() const {
	hpvec3 first, last;
	getFirstAndLastPoint(first, last);
	if(first.z == 0.0f && last.z == 0.0f)
		return true;
	else
		return false;
}

bool ToothProfile::pointsSavedInClockDirection() const {
	hpvec3 first, last;
	getFirstAndLastPoint(first, last);
	return (first.x * last.y - first.y * last.x < 0.0f);
}

// Returns a new BSplineCurve representing the whole gear by putting together
// many of copies of the tooth profile bspline.
//
// Example with degree = 3 and 4 teeth
//
// Given knots: 0---0---0---0---1---2---5---6---8---9---9---9---9
// New knots:   0---0---0---0---1---2---5---6---8---
//                  9---9---9--10--11--14--15--17---
//                 18--18--18--19--20--23--24--26---
//                 27--27--27--28--29--32--33--35--35--35--35--35
//
// Given points: a--b--c--d--e--f--g--h--i
// New points:   a0-b0-c0-d0-e0-f0-g0-h0
//               a1-b1-c1-d1-e1-f1-g1-h1
//               a2-b2-c2-d2-e2-f2-g2-h2
//               a3-b3-c3-d3-e3-f3-g3-h3
//
// Remark: the numbers behind the literals mean, that the corresponding points
// are rotated around the origin. As point a equals point i when rotated with
// one anuglar pitch, point i is dropped
void ToothProfile::extendToGearCurve(BSplineCurve<hpvec3>& gearProfile) const {

	hpuint nTeeth = getNumberOfTeeth();
	hpuint degree = m_toothProfileCurve.getDegree();
	hpreal direction = 1.0f;
	if(pointsSavedInClockDirection())
		direction = -1.0f;

	std::vector<hpvec3> controlPoints = m_toothProfileCurve.getControlPoints();
	std::vector<hpreal> knots = m_toothProfileCurve.getKnots();
	std::vector<hpreal> knotOffsets(knots.size() - 2 * degree - 1);
	for(hpuint i = 0; i < knotOffsets.size(); ++i) {
		knotOffsets[i] = knots[degree + 1 + i] - knots[degree];
	}
	std::vector<hpvec3> gearControlPoints(((controlPoints.size() - 1) * nTeeth + 1));
	std::vector<hpreal> gearKnots((knots.size() - degree - 2) * nTeeth + degree + 2);

	std::vector<hpvec3>::iterator gearPointIt = gearControlPoints.begin();
	std::vector<hpreal>::iterator gearKnotIt = gearKnots.begin();
	hpreal lastKnotValue;
	*gearKnotIt = knots.front();
	*(++gearKnotIt) = knots.front();

	Plane* plane = getPlaneToothProfileLiesIn();
	hpvec3 rotationAxis = plane->getNormal();
	delete plane;
	for(hpuint tooth = 0; tooth < nTeeth; ++tooth) {

		lastKnotValue = *gearKnotIt;
		for(hpuint i = 0; i < (degree - 1); ++i) {
			*(++gearKnotIt) = lastKnotValue;
		}
		for(std::vector<hpreal>::iterator it = knotOffsets.begin(), end = knotOffsets.end(); it != end; ++it) {
			*(++gearKnotIt) = lastKnotValue + *it;
		}

		hpreal degreeRotation = direction * (tooth * 360.0f / nTeeth);
		for(std::vector<hpvec3>::iterator it = controlPoints.begin(), end = --(controlPoints.end()); it != end; ++it) {
			*gearPointIt = glm::rotate(*it, degreeRotation, rotationAxis);
			++gearPointIt;
		}
	}
	lastKnotValue = *gearKnotIt;
	for(hpuint i = 0; i < degree; ++i) {
		*(++gearKnotIt) = lastKnotValue;
	}
	*gearPointIt = gearControlPoints.front();
	gearProfile = BSplineCurve<hpvec3>(gearControlPoints, gearKnots);
}

void ToothProfile::extendToGearCurve(BSplineCurve<hpvec2>& gearProfile) const {

	hpuint nTeeth = getNumberOfTeeth();
	hpuint degree = m_toothProfileCurve.getDegree();
	hpreal direction = 1.0f;
	if(pointsSavedInClockDirection())
		direction = -1.0f;

	if(!liesInXYPlane()) {
		cerr << "Attiontion! The tooth profile does not lie in the xy plane. As parameter for return value is only a 2D BSplineCurve, third dimension is cut off!" << endl;
	}
	std::vector<hpvec3> controlPoints = m_toothProfileCurve.getControlPoints();
	std::vector<hpreal> knots = m_toothProfileCurve.getKnots();
	std::vector<hpreal> knotOffsets(knots.size() - 2 * degree - 1);
	for(hpuint i = 0; i < knotOffsets.size(); ++i) {
		knotOffsets[i] = knots[degree + 1 + i] - knots[degree];
	}
	std::vector<hpvec2> gearControlPoints(((controlPoints.size() - 1) * nTeeth + 1));
	std::vector<hpreal> gearKnots((knots.size() - degree - 2) * nTeeth + degree + 2);

	std::vector<hpvec2>::iterator gearPointIt = gearControlPoints.begin();
	std::vector<hpreal>::iterator gearKnotIt = gearKnots.begin();
	hpreal lastKnotValue;
	*gearKnotIt = knots.front();
	*(++gearKnotIt) = knots.front();
	for(hpuint tooth = 0; tooth < nTeeth; ++tooth) {

		lastKnotValue = *gearKnotIt;
		for(hpuint i = 0; i < (degree - 1); ++i) {
			*(++gearKnotIt) = lastKnotValue;
		}
		for(std::vector<hpreal>::iterator it = knotOffsets.begin(), end = knotOffsets.end(); it != end; ++it) {
			*(++gearKnotIt) = lastKnotValue + *it;
		}

		hpreal degreeRotation = direction * (tooth * 360.0f / nTeeth);
		for(std::vector<hpvec3>::iterator it = controlPoints.begin(), end = --(controlPoints.end()); it != end; ++it) {
			*gearPointIt = glm::rotate(hpvec2(it->x, it->y), degreeRotation);
			++gearPointIt;
		}
	}
	lastKnotValue = *gearKnotIt;
	for(hpuint i = 0; i < degree; ++i) {
		*(++gearKnotIt) = lastKnotValue;
	}
	*gearPointIt = gearControlPoints.front();
	gearProfile = BSplineCurve<hpvec2>(gearControlPoints, gearKnots);
}


void ToothProfile::rotate(hpreal degree) {
	std::vector<hpvec3> controlPoints = m_toothProfileCurve.getControlPoints();
	if(liesInXYPlane()) {
		for(std::vector<hpvec3>::iterator it = controlPoints.begin(), end = controlPoints.end(); it != end; ++it) {
			*it = hpvec3(glm::rotate(hpvec2(it->x, it->y), degree), 0.0f);
		}
	} else {
		Plane* plane = getPlaneToothProfileLiesIn();
		hpvec3 rotationAxis = plane->getNormal();
		delete plane;
		for(std::vector<hpvec3>::iterator it = controlPoints.begin(), end = controlPoints.end(); it != end; ++it) {
			*it = hpvec3(glm::rotate(*it, degree, rotationAxis));
		}
	}
	m_toothProfileCurve.setControlPoints(controlPoints);
}

void ToothProfile::setPointOfGear(hpuint index, hpvec2 newValue) {
	setPointOfGear(index, hpvec3(newValue, 0.0f));
}

void ToothProfile::setPointOfGear(hpuint index, hpvec3 newValue) {
	hpuint maxToothProfileIndex = m_toothProfileCurve.getNumberOfControlPoints() - 1;
	hpuint indexIsInTooth = index / maxToothProfileIndex;
	hpuint toothProfileIndex = index;

	if(indexIsInTooth == getNumberOfTeeth()) {
		toothProfileIndex = 0;

	} else if(index >= maxToothProfileIndex) {
		hpvec3 first, last;
		getFirstAndLastPoint(first, last);
		hpreal rotation = getAngularPitch() * indexIsInTooth * 180.0f / M_PI;
		hpvec3 rotatedNewValue = glm::rotate(newValue, rotation, glm::cross(last, first));
		newValue = rotatedNewValue;
		toothProfileIndex = index % maxToothProfileIndex;
	}
	setPointOfToothProfile(toothProfileIndex, newValue);
}

void ToothProfile::setPointOfToothProfile(hpuint toothProfileIndex, hpvec2 newValue) {
	m_toothProfileCurve.setControlPoint(toothProfileIndex, hpvec3(newValue, 0.0f));
}

void ToothProfile::setPointOfToothProfile(hpuint toothProfileIndex, hpvec3 newValue) {
	m_toothProfileCurve.setControlPoint(toothProfileIndex, newValue);
}

PointCloud* ToothProfile::toPointCloud() {
	BSplineCurve<hpvec3> curve;
	extendToGearCurve(curve);
	return curve.toPointCloud();
}

LineMesh* ToothProfile::toLineMesh() {
	BSplineCurve<hpvec3> curve;
	extendToGearCurve(curve);
	return curve.toLineMesh();
}

void ToothProfile::getFirstAndLastPoint(hpvec3& first, hpvec3& last) const {
	hpreal startValue, stopValue;
	m_toothProfileCurve.getParameterRange(startValue, stopValue);
	first = m_toothProfileCurve.getValueAt(startValue);
	last = m_toothProfileCurve.getValueAt(stopValue);
}

void ToothProfile::ensureClamping() {
	if(!m_toothProfileCurve.getClamped()) {
		std::cerr << "A BSplineCurve for a ToothProfile has to be clamed! Otherwise the resulting gear will look against expectation." << std::endl;
		m_toothProfileCurve.setClamped(true);
	}
}
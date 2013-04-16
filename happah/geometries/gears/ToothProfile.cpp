#include "happah/geometries/gears/ToothProfile.h"
#include "glm/gtx/rotate_vector.hpp"
#include <vector>
#include <iostream>

ToothProfile::ToothProfile(const BSplineCurve& toothProfile) : m_toothProfileCurve(toothProfile){
	if(!m_toothProfileCurve.getClamped()) {
		std::cerr << "A BSplineCurve for a ToothProfile has to be clamed! Otherwise the resulting gear will look against expectation." << std::endl;
		m_toothProfileCurve.setClamped(true);
	}
}

ToothProfile::~ToothProfile() {}

hpreal ToothProfile::getAngularPitch() const {
	hpreal startValue, stopValue;
	m_toothProfileCurve.getParameterRange(startValue, stopValue);
	hpvec3 first = m_toothProfileCurve.getValueAt(startValue);
	hpvec3 last = m_toothProfileCurve.getValueAt(stopValue);
	// if angularPitch > PI (more than half of circle), concstruction will fail!
	return glm::acos((glm::dot(glm::normalize(first), glm::normalize(last))));
}

hpuint ToothProfile::getNumberOfTeeth() const {
	return (hpuint) floor(((M_PI * 2.0) / getAngularPitch()) + 0.5);
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

hpreal ToothProfile::getRootRadius() const {
	hpreal min = glm::length(m_toothProfileCurve.getValueAt(0));
	for(unsigned int i = 1; i <= 100; ++i) {
		hpreal value = glm::length(m_toothProfileCurve.getValueAt((1.0f / 100) * i));
		if (value < min)
			min = value;
	}
	return min;
}

bool ToothProfile::pointsSavedInClockDirection() const {
	hpreal startValue, stopValue;
	m_toothProfileCurve.getParameterRange(startValue, stopValue);
	hpvec3 first = m_toothProfileCurve.getValueAt(startValue);
	hpvec3 last = m_toothProfileCurve.getValueAt(stopValue);
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
BSplineCurve* ToothProfile::getEntireGear() const {

	hpuint nTeeth = getNumberOfTeeth();
	hpuint degree = m_toothProfileCurve.getDegree();
	hpreal direction = -1.0f;
	if(pointsSavedInClockDirection())
		direction = 1.0f;

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
			*gearPointIt = glm::rotate(hpvec2((*it).x, (*it).y), degreeRotation);
			++gearPointIt;
		}
	}
	lastKnotValue = *gearKnotIt;
	for(hpuint i = 0; i < degree; ++i) {
		*(++gearKnotIt) = lastKnotValue;
	}
	*gearPointIt = gearControlPoints.front();
	BSplineCurve* gearCurve = new BSplineCurve(gearControlPoints, gearKnots);
	return gearCurve;
}

BSplineCurve ToothProfile::getCurve() const {
	return m_toothProfileCurve;
}
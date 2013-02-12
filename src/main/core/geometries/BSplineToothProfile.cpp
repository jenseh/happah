#include "BSplineToothProfile.h"
#include "glm/gtx/rotate_vector.hpp"
#include "iostream"

BSplineToothProfile::BSplineToothProfile(BSplineCurve *curve, unsigned int sampleRate) : m_curve(curve), m_sampleRate(sampleRate) {}
BSplineToothProfile::~BSplineToothProfile() {
	delete m_curve;
}

BSplineCurve* BSplineToothProfile::getRepresentation() {
	//TODO: BAD!!! things of inner class shouldn't be returned!!!
	return m_curve;
}

void BSplineToothProfile::rotate(hpreal angle) {
	BSplineCurve *curve = new BSplineCurve();
	for (uint i = 0; i < m_curve->getNumberOfControlPoints(); ++i) {
		curve->addControlPoint(glm::rotate(m_curve->getControlPoint(i), angle, hpvec3(0, 0, 1)));
	}
	delete m_curve;
	m_curve = curve;
}

std::vector<hpvec2>* BSplineToothProfile::getAs2DPoints(){
	return getAs2DPoints(hpvec3(0, 0, 1));
}

std::vector<hpvec2>* BSplineToothProfile::getAs2DPoints(hpvec3 removeDirection){
	removeDirection = glm::normalize(removeDirection);
	bool rotate = true;
	if (removeDirection == hpvec3(0, 0, 1))
		rotate = false;
	hpvec3 rotationAxis = glm::cross(removeDirection, hpvec3(0, 0, 1));
	hpreal angle = (glm::acos(glm::dot(removeDirection, hpvec3(0, 0, 1)))) * 180.0f / M_PI;
	
	std::vector<hpvec2> *points = new std::vector<hpvec2>;
	for (uint i = 0; i <= m_sampleRate; ++i) {//TODO: Attention, at the moment is "<=" to get the whole tooth
		hpvec3 pointInZDirection;
		if (rotate)
			pointInZDirection = glm::rotate(m_curve->getValueAt((hpreal) i / m_sampleRate), angle, rotationAxis);
		else
			pointInZDirection = m_curve->getValueAt((hpreal) i / m_sampleRate);
		points->push_back(hpvec2(pointInZDirection.x, pointInZDirection.y));
	}
	return points;
}

bool BSplineToothProfile::isInClockDirection() {
	hpvec3 first = m_curve->getValueAt(0.0f);
	hpvec3 last = m_curve->getValueAt(1.0f);
	return (first[0] * last[1] - first[1] * last[0]) < 0;
}

bool BSplineToothProfile::isInCounterClockDirection() {
	return !isInClockDirection();
}

hpreal BSplineToothProfile::getAngularPitch() {
	hpvec3 first = m_curve->getValueAt(0.0f);
	hpvec3 last = m_curve->getValueAt(1.0f);
	// if angularPitch > PI (more than half of circle), concstruction will fail!
	return glm::acos((glm::dot(glm::normalize(first), glm::normalize(last))));
}
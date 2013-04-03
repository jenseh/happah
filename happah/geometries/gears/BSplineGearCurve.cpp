#include "happah/geometries/gears/BSplineGearCurve.h"
#include "glm/gtx/rotate_vector.hpp"

BSplineGearCurve::BSplineGearCurve() {}

BSplineGearCurve::BSplineGearCurve(const BSplineCurve& bspline) : BSplineCurve(bspline){
}

BSplineGearCurve::~BSplineGearCurve() {}

hpreal BSplineGearCurve::getAngularPitch() const {
	hpvec3 first = getValueAt(0.0f);
	hpvec3 last = getValueAt(1.0f);
	// if angularPitch > PI (more than half of circle), concstruction will fail!
	return glm::acos((glm::dot(glm::normalize(first), glm::normalize(last))));
}

unsigned int BSplineGearCurve::getNumberOfTeeth() const {
	return (unsigned int) floor(((M_PI * 2.0) / getAngularPitch()) + 0.5);
}

hpreal BSplineGearCurve::getMiddleLength() const {
	return getMinLength() + 0.5f * (getMaxLength() - getMinLength());
}

hpreal BSplineGearCurve::getMaxLength() const {
	hpreal max = glm::length(getValueAt(0));
	for (unsigned int i = 1; i <= 100; ++i) {
		hpreal value = glm::length(getValueAt((1.0f / 100) * i));
		if (value > max)
			max = value;
	}
	return max;
}

hpreal BSplineGearCurve::getMinLength() const {
	hpreal min = glm::length(getValueAt(0));
	for (unsigned int i = 1; i <= 100; ++i) {
		hpreal value = glm::length(getValueAt((1.0f / 100) * i));
		if (value < min)
			min = value;
	}
	return min;
}

void BSplineGearCurve::scale(hpreal scaleFactor) {
	for(unsigned int i = 0; i < m_controlPoints.size(); ++i) {
		setControlPoint(i, scaleFactor * getControlPoint(i));
	}
}

void BSplineGearCurve::getBounds(hpvec2* min, hpvec2* max) const {
	getEntireGear()->getBounds(min, max);
}

BSplineCurve* BSplineGearCurve::getEntireGear() const {
	BSplineCurve *gearProfile = new BSplineCurve();
	gearProfile->setPeriodic(true);
	gearProfile->setDegree(m_degree);

	for (unsigned int tooth = 0; tooth < getNumberOfTeeth(); ++tooth) {
		hpreal degreeRotation = -(M_PI * 2.0f * tooth / getNumberOfTeeth()) * 180.0f / M_PI;
		for (unsigned int i = 0; i < getNumberOfControlPoints(); ++i) {
			hpvec3 controlPoint = getControlPoint(i);
			hpvec3 turnedPoint = hpvec3(glm::rotate(controlPoint, degreeRotation, hpvec3(0,0,1)));;
			gearProfile->addControlPoint(turnedPoint);
		}
	}
	return gearProfile;
}

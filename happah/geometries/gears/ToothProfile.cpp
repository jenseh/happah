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
	hpvec3 first = m_toothProfileCurve.getValueAt(0.0f);
	hpvec3 last = m_toothProfileCurve.getValueAt(1.0f);
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

// TODO: Repair this method
BSplineCurve* ToothProfile::getEntireGear() const {
	BSplineCurve *gearProfile = new BSplineCurve();
	gearProfile->setPeriodic(true);
	gearProfile->setDegree(m_degree);
	// std::vector<hpvec3> copiedControlPoints = m_controlPoints; //to be able to use the iterator. TODO: should we do it like this?

	// hpuint nTeeth = getNumberOfTeeth();
	// for(unsigned int tooth = 0; tooth < nTeeth; ++tooth) {
	// 	hpreal degreeRotation = -(M_PI * 2.0f * tooth / nTeeth) * 180.0f / M_PI;
	// 	for(std::vector<hpvec3>::iterator it = copiedControlPoints.begin(), end = copiedControlPoints.end(); it != end; ++it) {
	// 		hpvec3 turnedPoint = hpvec3(glm::rotate(*it, degreeRotation, hpvec3(0,0,1)));;
	// 		gearProfile->addControlPoint(turnedPoint);
	// 	}
	// }
	return gearProfile;
}

BSplineCurve ToothProfile::getCurve() const {
	return m_toothProfileCurve;
}
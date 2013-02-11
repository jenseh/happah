#include "SimpleGear.h"
#include "glm/gtx/rotate_vector.hpp"

SimpleGear::SimpleGear(BSplineToothProfile *toothProfile, hpreal helixAngle, hpreal faceWidth) :
	m_toothProfile(toothProfile), m_helixAngle(helixAngle), m_facewidth(faceWidth) {}

SimpleGear::~SimpleGear(){}


// Um einen Grundschrägungswinkel beta (helixAngle) zu erzielen, muss das Stirnprofil bei
// Verschiebung um z in Richtung der Zahnradachse um den Winkel(!) z * tan(beta) gedreht werden.
BSplineCurve* SimpleGear::toTransverseToothProfileSystem(hpreal z){
	hpreal rotation = glm::tan(m_helixAngle) * z;

	BSplineCurve *gearProfile = new BSplineCurve();
//	gearProfile->setPeriodic(true);
//	gearProfile->setDegree(2);
	for (uint tooth = 0; tooth < getToothCount(); ++tooth) {
		m_toothProfile->rotate(tooth * getAngularPitch() + rotation);
		gearProfile->addCurve(m_toothProfile->getRepresentation());
	}
	return gearProfile;
}

hpreal SimpleGear::getAngularPitch() {
	return m_toothProfile->getAngularPitch();
}

uint SimpleGear::getToothCount() {
	return (uint) floor(((M_PI * 2.0) / m_toothProfile->getAngularPitch()) + 0.5);
}

hpreal SimpleGear::getFacewidth() {
	return m_facewidth;
}

std::vector<hpvec2>* SimpleGear::getToothProfile() {
	return m_toothProfile->getAs2DPoints();
}

std::vector<hpvec2>* SimpleGear::getGearProfile(hpreal depth) {
	hpreal rotation = glm::tan(m_helixAngle) * depth;

	std::vector<hpvec2>* toothProfile = getToothProfile();
	std::vector<hpvec2>* gearProfile = new std::vector<hpvec2>();
	hpreal angularPitch = getAngularPitch();
	for(uint i = 0; i < getToothCount(); ++i) {
		for(uint j = 0; j < toothProfile->size() - 1; ++j) {
			gearProfile->push_back(glm::rotate(toothProfile->at(j), angularPitch * i + rotation));
		}
	}
	return gearProfile;
}

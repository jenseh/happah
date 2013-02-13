#include "SimpleGear.h"
#include "glm/gtx/rotate_vector.hpp"

SimpleGear::SimpleGear(BSplineToothProfile *toothProfile, hpreal helixAngle, hpreal facewidth) :
	m_toothProfile(toothProfile), m_helixAngle(helixAngle), m_facewidth(facewidth) {}

SimpleGear::~SimpleGear(){}

// Um einen Grundschrägungswinkel beta (helixAngle) zu erzielen, muss das Stirnprofil bei
// Verschiebung um z in Richtung der Zahnradachse um den Winkel(!) z * tan(beta) gedreht werden.
BSplineCurve* SimpleGear::toTransverseToothProfileSystem(hpreal depth){

	BSplineCurve *gearProfile = new BSplineCurve();
	gearProfile->setPeriodic(true);
	gearProfile->setDegree(2);

	hpreal rotation = glm::tan(m_helixAngle) * depth;
	hpreal angleStep = (m_toothProfile->isInClockDirection()) ? getAngularPitch() * (-1.0f) : getAngularPitch();
	BSplineCurve *toothProfile = m_toothProfile->getRepresentation();

	for (uint tooth = 0; tooth < getToothCount(); ++tooth) {
		hpreal degreeRotation = (float) ((angleStep * tooth + rotation) * 180.0f / M_PI);
		for (uint i = 0; i < toothProfile->getNumberOfControlPoints(); ++i) {
			hpvec3 controlPoint = toothProfile->getControlPoint(i);
			hpvec3 turnedPoint = hpvec3(glm::rotate(controlPoint, degreeRotation, hpvec3(0,0,1)));;
			gearProfile->addControlPoint(hpvec3(300, 300, 0) + turnedPoint * 250.0f); //TODO: only to make it "bigger" - find something else instead
		}
	}
	return gearProfile;
}

hpreal SimpleGear::getAngularPitch() {
	return m_toothProfile->getAngularPitch();
}

uint SimpleGear::getToothCount() {
	return (uint) floor(((M_PI * 2.0) / m_toothProfile->getAngularPitch()) + 0.5);
}

hpreal SimpleGear::getHelixAngle() {
	return m_helixAngle;
}
hpreal SimpleGear::getFacewidth() {
	return m_facewidth;
}
void SimpleGear::setHelixAngle(hpreal angle) {
	m_helixAngle = angle;
}
void SimpleGear::setFacewidth(hpreal facewidth) {
	m_facewidth = facewidth;
}

std::vector<hpvec2>* SimpleGear::getToothProfile() {
	return m_toothProfile->getAs2DPoints();
}

std::vector<hpvec2>* SimpleGear::getGearProfile(hpreal depth) {
	hpreal rotation = glm::tan(m_helixAngle) * depth;

	std::vector<hpvec2>* toothProfile = getToothProfile();
	std::vector<hpvec2>* gearProfile = new std::vector<hpvec2>();
	hpreal angularPitch = getAngularPitch();
	if (m_toothProfile->isInClockDirection())
		angularPitch *= (-1.0f);
	for(uint i = 0; i < getToothCount(); ++i) {
		for(uint j = 0; j < toothProfile->size() - 1; ++j) {
			hpreal degreeRotation = (float) ((angularPitch * i + rotation) * 180.0f / M_PI);
			gearProfile->push_back(glm::rotate(toothProfile->at(j), degreeRotation));
		}
	}
	return gearProfile;
}

#include "happah/geometries/SimpleGear.h"
#include "glm/gtx/rotate_vector.hpp"

SimpleGear::SimpleGear(BSplineGearCurve *toothProfile, hpreal helixAngle, hpreal facewidth) :
	m_toothProfile(toothProfile), m_helixAngle(helixAngle), m_facewidth(facewidth) {
}

SimpleGear::~SimpleGear(){
	delete m_toothProfile; //TODO is this correct here?
}

// Um einen Grundschrägungswinkel beta (helixAngle) zu erzielen, muss das Stirnprofil bei
// Verschiebung um z in Richtung der Zahnradachse um den Winkel(!) z * tan(beta) gedreht werden.
BSplineCurve* SimpleGear::toTransverseToothProfileSystem(hpreal depth){

	BSplineCurve *gearProfile = new BSplineCurve();
	gearProfile->setPeriodic(true);
	gearProfile->setDegree(2);

	hpreal rotation = glm::tan(m_helixAngle) * depth;

	for (uint tooth = 0; tooth < getToothCount(); ++tooth) {
		hpreal degreeRotation = (float) (-(getAngularPitch() * tooth + rotation) * 180.0f / M_PI);
		for (uint i = 0; i < m_toothProfile->getNumberOfControlPoints(); ++i) {
			hpvec3 controlPoint = m_toothProfile->getControlPoint(i);
			hpvec3 turnedPoint = hpvec3(glm::rotate(controlPoint, degreeRotation, hpvec3(0,0,1)));;
			gearProfile->addControlPoint(turnedPoint);
		}
	}
	return gearProfile;
}

BSplineGearCurve* SimpleGear::getBSplineToothProfileInXYPlane() {
	BSplineGearCurve *toothProfileToTop = new BSplineGearCurve();
	toothProfileToTop->setPeriodic(false);
	toothProfileToTop->setDegree(2);

	hpvec3 stop = glm::normalize(m_toothProfile->getValueAt(1.0f));
	hpvec3 start = glm::normalize(m_toothProfile->getValueAt(0.0f));
	hpvec3 facesTo = glm::normalize(glm::cross(stop, start));
	hpmat3x3 toothPMatrix = hpmat3x3(glm::normalize(glm::cross(start, facesTo)), start, facesTo);
	hpmat3x3 goalMatrix = hpmat3x3(hpvec3(1, 0, 0), hpvec3(0, 1, 0), hpvec3(0, 0, 1));
	hpmat3x3 transformation = goalMatrix * glm::inverse(toothPMatrix);

		for (uint i = 0; i < m_toothProfile->getNumberOfControlPoints(); ++i) {
			hpvec3 turnedPoint = transformation * m_toothProfile->getControlPoint(i);
			toothProfileToTop->addControlPoint(turnedPoint);
		}
	return toothProfileToTop;
}

hpreal SimpleGear::getAngularPitch() {
	return m_toothProfile->getAngularPitch();
}

uint SimpleGear::getToothCount() {
	return m_toothProfile->getToothCount();
}

hpreal SimpleGear::getRadius() {
	return m_toothProfile->getMiddleLength();
}

hpreal SimpleGear::getHelixAngle() {
	return m_helixAngle;
}
hpreal SimpleGear::getFacewidth() {
	return m_facewidth;
}
bool SimpleGear::toothProfileIsInClockDirection() {
	return true; //no calculation needed as bspline is oriented in a way that this is always true
}
void SimpleGear::setHelixAngle(hpreal angle) {
	m_helixAngle = angle;
}
void SimpleGear::setFacewidth(hpreal facewidth) {
	m_facewidth = facewidth;
}
void SimpleGear::setRadius(hpreal radius) {
	m_toothProfile->scale(radius / m_toothProfile->getMiddleLength());
}

void SimpleGear::setToothProfile(BSplineGearCurve* curve) {
	//TODO: do we need 'delete m_toothProfile'?
	m_toothProfile = curve;
}

std::vector<hpvec2>* SimpleGear::getToothProfile() {
	std::vector<hpvec2> *points = new std::vector<hpvec2>;
	BSplineCurve* splineXY = getBSplineToothProfileInXYPlane();
	for (uint i = 0; i <= TOOTH_SAMPLE_SIZE; ++i) { //"<=" to get the whole tooth
		hpvec3 point = splineXY->getValueAt((hpreal) i / TOOTH_SAMPLE_SIZE);
		points->push_back(hpvec2(point.x, point.y));
	}
	return points;
}

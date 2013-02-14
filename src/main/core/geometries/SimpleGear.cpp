#include "SimpleGear.h"
#include "glm/gtx/rotate_vector.hpp"

SimpleGear::SimpleGear(BSplineGearCurve *toothProfile, hpreal helixAngle, hpreal facewidth) :
	m_toothProfile(toothProfile), m_helixAngle(helixAngle), m_facewidth(facewidth) {
		m_scalingActivated = false; //TODO remove
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
	hpreal scaleFactor = getScaleFactor();

	for (uint tooth = 0; tooth < getToothCount(); ++tooth) {
		hpreal degreeRotation = (float) (-(getAngularPitch() * tooth + rotation) * 180.0f / M_PI);
		for (uint i = 0; i < m_toothProfile->getNumberOfControlPoints(); ++i) {
			hpvec3 controlPoint = m_toothProfile->getControlPoint(i);
			hpvec3 turnedPoint = hpvec3(glm::rotate(controlPoint, degreeRotation, hpvec3(0,0,1)));;
			gearProfile->addControlPoint(scaleFactor * turnedPoint); //TODO: only to make it "bigger" - find something else instead
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
	hp3x3 toothPMatrix = hp3x3(glm::normalize(glm::cross(start, facesTo)), start, facesTo);
	hpreal alpha = getAngularPitch() / 2.0f;
	hp3x3 goalMatrix = hp3x3(hpvec3(1, 0, 0), hpvec3(0, 1, 0), hpvec3(0, 0, 1));
	hp3x3 transformation = goalMatrix * glm::inverse(toothPMatrix);

	hpreal scaleFactor = getScaleFactor();

		for (uint i = 0; i < m_toothProfile->getNumberOfControlPoints(); ++i) {
			hpvec3 turnedPoint = transformation * m_toothProfile->getControlPoint(i);
			toothProfileToTop->addControlPoint(scaleFactor * turnedPoint); //TODO: only to make it "bigger" - find something else instead
		}
	return toothProfileToTop;
}

hpreal SimpleGear::getScaleFactor() { //TODO: only to have bigger values in editorscene as it is in 3d as the moment
	if (m_scalingActivated) {
		hpvec2 vmin, vmax;
		m_toothProfile->getBounds(&vmin, &vmax);
		hpreal max = (vmax.x > vmax.y) ? (vmax.x - 5): (vmax.y - 5); //TODO: 5 is ellipse around controlpoints which is included in getBounds(...)
		hpreal scaleFactor = (max < 100) ? (max == 0 ? 200 : (100 / max)) : 1.0f;
		return scaleFactor;
	} else {
		return 1.0f;
	}
}

hpreal SimpleGear::getAngularPitch() {
	return m_toothProfile->getAngularPitch();
}

uint SimpleGear::getToothCount() {
	return m_toothProfile->getToothCount();
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

//TODO remove following!
void SimpleGear::setScalingActivated(bool activate) {
	m_scalingActivated = activate;
}
/*
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
*/
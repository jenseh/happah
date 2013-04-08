#include "glm/gtx/rotate_vector.hpp"
#include "happah/geometries/gears/SimpleGear.h"


SimpleGear::SimpleGear(BSplineGearCurve *toothProfile, hpreal helixAngle, hpreal faceWidth) :
	m_toothProfile(toothProfile), m_helixAngle(helixAngle), m_faceWidth(faceWidth) {
}

SimpleGear::SimpleGear(const SimpleGear& other)
	: m_toothProfile(new BSplineGearCurve(*(other.m_toothProfile))), m_helixAngle(other.m_helixAngle), m_faceWidth(other.m_faceWidth) {}

SimpleGear::~SimpleGear(){
	delete m_toothProfile; //TODO is this correct here?
}

// Um einen Grundschrägungswinkel beta (helixAngle) zu erzielen, muss das Stirnprofil bei
// Verschiebung um z in Richtung der Zahnradachse um den Winkel(!) z * tan(beta) gedreht werden.
void SimpleGear::getTraverseProfile(hpreal z, BSplineCurve* gearProfile) {
//BSplineCurve* SimpleGear::toTransverseToothProfileSystem(hpreal z) {

	//gearProfile->resetPoints(); or something like that. TODO: insert this!!!
	gearProfile->setPeriodic(true);
	hpreal rotation = glm::tan(m_helixAngle) * z;

	for(hpuint tooth = 0; tooth < getNumberOfTeeth(); ++tooth) {
		hpreal degreeRotation = (float) (-(getAngularPitch() * tooth + rotation) * 180.0f / M_PI);
		for(hpuint i = 0; i < m_toothProfile->getNumberOfControlPoints(); ++i) {
			hpvec3 controlPoint = m_toothProfile->getControlPoint(i);
			hpvec3 turnedPoint = hpvec3(glm::rotate(controlPoint, degreeRotation, hpvec3(0,0,1)));;
			gearProfile->addControlPoint(turnedPoint);
		}
	}
}

//TODO: This method doesn't suit in here! Move it to BSplineGear or somewhere else!!!
BSplineGearCurve* SimpleGear::getCopyWithBeginOfToothAtTop() const {
	// We assume, that the given Curve lies only in the XY-Plane,
	// and we turn it in a way, that the curve starts at the positive y-axis
	// and turns in the direction to the positiv x-axis.
	// (Considered a right-hand coordinate system with the z-axis pointing
	// towards the observer it turns clockwise.)
	BSplineGearCurve *toothProfileToTop = new BSplineGearCurve();
	toothProfileToTop->setPeriodic(false);
	toothProfileToTop->setDegree(m_toothProfile->getDegree());

	hpvec3 stop = glm::normalize(m_toothProfile->getValueAt(1.0f));
	hpvec3 start = glm::normalize(m_toothProfile->getValueAt(0.0f));
	hpvec2 startX = hpvec2(start.y, -start.x);    //facesTo = [0,0,+1]
	if(stop.x * start.y - stop.y * start.x < 0) { //facesTo = [0,0,-1]
		startX = hpvec2(-start.y, start.x);
	}
	hpreal c = 1.0f / (start.x * start.x + start.y * start.y);
	for(hpuint i = 0; i < m_toothProfile->getNumberOfControlPoints(); ++i) {
		hpvec3 controlPoint = m_toothProfile->getControlPoint(i);
		hpvec3 turnedPoint = hpvec3(startX.x * controlPoint.x + start.x * controlPoint.y,
									startX.y * controlPoint.x + start.y * controlPoint.y,
									0) * c;
		toothProfileToTop->addControlPoint(turnedPoint);
	}
	return toothProfileToTop;
}

hpreal SimpleGear::getAngularPitch() {
	return m_toothProfile->getAngularPitch();
}

hpreal SimpleGear::getRootRadius() {
	return m_toothProfile->getMinLength();
}

hpuint SimpleGear::getNumberOfTeeth() {
	return m_toothProfile->getNumberOfTeeth();
}

hpreal SimpleGear::getRadius() {
	return m_toothProfile->getMiddleLength();
}

hpreal SimpleGear::getHelixAngle() {
	return m_helixAngle;
}
hpreal SimpleGear::getFaceWidth() {
	return m_faceWidth;
}

BSplineGearCurve SimpleGear::getToothProfile() {
	return *m_toothProfile;
}

void SimpleGear::setHelixAngle(hpreal angle) {
	m_helixAngle = angle;
}
void SimpleGear::setFaceWidth(hpreal faceWidth) {
	m_faceWidth = faceWidth;
}
void SimpleGear::setRadius(hpreal radius) {
	m_toothProfile->scale(radius / m_toothProfile->getMiddleLength());
}

void SimpleGear::setToothProfile(BSplineGearCurve* curve) {
	//TODO: do we need 'delete m_toothProfile'?
	m_toothProfile = curve;
}

void SimpleGear::getToothSpaceProfile(vector<hpvec2>& toothSpaceProfile) {
	BSplineCurve* splineXY = getCopyWithBeginOfToothAtTop();
	hpreal low,high;
	splineXY->getParameterRange(low, high);
	hpreal delta = (high - low) / (hpreal)(toothSpaceProfile.capacity() - 1); // -1 so whole thooth is sampled
	for(int i = toothSpaceProfile.capacity()/2-1;  i >= 0; i--) {
		hpvec3 point = splineXY->getValueAt(low + i*delta);
		toothSpaceProfile.push_back(hpvec2(-point.x, point.y));
	}
	for(uint i = 0; i < toothSpaceProfile.capacity()/2; i++) {
		hpvec3 point = splineXY->getValueAt(low + i*delta);
		toothSpaceProfile.push_back(hpvec2(point.x, point.y));
	}
	delete splineXY;
}

void SimpleGear::getToothProfile(vector<hpvec2>& toothProfile) {
	hpuint nPointsPerTooth = toothProfile.size();
	BSplineCurve* splineXY = getCopyWithBeginOfToothAtTop();
	hpreal low,high;
	splineXY->getParameterRange(low, high);
	hpreal delta = (high - low) / (hpreal)(nPointsPerTooth - 1); // -1 so whole thooth is sampled
	for(hpuint i = 0; i < nPointsPerTooth; ++i) {
		hpvec3 point = splineXY->getValueAt(low + (hpreal) (i * delta));
		toothProfile[i] = hpvec2(point.x, point.y);
	}
	delete splineXY;
}


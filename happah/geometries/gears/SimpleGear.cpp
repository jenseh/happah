#include "glm/gtx/rotate_vector.hpp"
#include "happah/geometries/gears/SimpleGear.h"


SimpleGear::SimpleGear(const ToothProfile& toothProfile, hpreal helixAngle, hpreal faceWidth) :
	m_toothProfile(ToothProfile_ptr(new ToothProfile(toothProfile))), m_helixAngle(helixAngle), m_faceWidth(faceWidth) {
}

SimpleGear::SimpleGear(const BSplineCurve<hpvec2>& toothProfileCurve, hpreal helixAngle, hpreal faceWidth) :
	m_helixAngle(helixAngle), m_faceWidth(faceWidth) {
	m_toothProfile = ToothProfile_ptr(new ToothProfile(toothProfileCurve));
}

SimpleGear::SimpleGear(const BSplineCurve<hpvec3>& toothProfileCurve, hpreal helixAngle, hpreal faceWidth) :
	m_helixAngle(helixAngle), m_faceWidth(faceWidth) {
	m_toothProfile = ToothProfile_ptr(new ToothProfile(toothProfileCurve));
}

SimpleGear::SimpleGear(const SimpleGear& other)
	: m_toothProfile(ToothProfile_ptr(new ToothProfile(*(other.m_toothProfile)))), m_helixAngle(other.m_helixAngle), m_faceWidth(other.m_faceWidth) {}

SimpleGear::~SimpleGear() {}

// Um einen Grundschrägungswinkel beta (helixAngle) zu erzielen, muss das Stirnprofil bei
// Verschiebung um z in Richtung der Zahnradachse um den Winkel(!) z * tan(beta) gedreht werden.
void SimpleGear::getTraverseProfile(hpreal z, BSplineCurve<hpvec3>& gearProfile) {
	hpreal rotation = -glm::tan(m_helixAngle) * z * 180.0f / M_PI;
	m_toothProfile->rotate(rotation);
	m_toothProfile->extendToGearCurve(gearProfile);
}

//TODO: This method doesn't suit in here! Move it to BSplineGear or somewhere else!!!
ToothProfile_ptr SimpleGear::getCopyWithBeginOfToothAtTop() const {
	return m_toothProfile;
	// We assume, that the given Curve lies only in the XY-Plane,
	// and we turn it in a way, that the curve starts at the positive y-axis
	// and turns in the direction to the positiv x-axis.
	// (Considered a right-hand coordinate system with the z-axis pointing
	// towards the observer it turns clockwise.)
	// ToothProfile *toothProfileToTop = new ToothProfile();
	// toothProfileToTop->setPeriodic(false);
	// toothProfileToTop->setDegree(m_toothProfile->getDegree());

	// hpvec3 stop = glm::normalize(m_toothProfile->getValueAt(1.0f));
	// hpvec3 start = glm::normalize(m_toothProfile->getValueAt(0.0f));
	// hpvec2 startX = hpvec2(start.y, -start.x);    //facesTo = [0,0,+1]
	// if(stop.x * start.y - stop.y * start.x < 0) { //facesTo = [0,0,-1]
	// 	startX = hpvec2(-start.y, start.x);
	// }
	// hpreal c = 1.0f / (start.x * start.x + start.y * start.y);
	// for(hpuint i = 0; i < m_toothProfile->getNumberOfControlPoints(); ++i) {
	// 	hpvec3 controlPoint = m_toothProfile->getControlPoint(i);
	// 	hpvec3 turnedPoint = hpvec3(startX.x * controlPoint.x + start.x * controlPoint.y,
	// 								startX.y * controlPoint.x + start.y * controlPoint.y,
	// 								0) * c;
	// 	toothProfileToTop->addControlPoint(turnedPoint);
	// }
	// return toothProfileToTop;
}

hpreal SimpleGear::getAngularPitch() {
	return m_toothProfile->getAngularPitch();
}

hpreal SimpleGear::getRootRadius() {
	return m_toothProfile->getRootRadius();
}

hpuint SimpleGear::getNumberOfTeeth() {
	return m_toothProfile->getNumberOfTeeth();
}

hpreal SimpleGear::getRadius() {
	//at the moment this takes the points with minimal and maximal distance to the centers and returns the averaged value
	return m_toothProfile->getRootRadius() + 0.5f * (m_toothProfile->getTipRadius() - m_toothProfile->getRootRadius());
}

hpreal SimpleGear::getHelixAngle() {
	return m_helixAngle;
}
hpreal SimpleGear::getFaceWidth() {
	return m_faceWidth;
}

ToothProfile SimpleGear::getToothProfile() {
	return *m_toothProfile;
}

void SimpleGear::setHelixAngle(hpreal angle) {
	m_helixAngle = angle;
}
void SimpleGear::setFaceWidth(hpreal faceWidth) {
	m_faceWidth = faceWidth;
}
void SimpleGear::setRadius(hpreal radius) {
//	m_toothProfile->scale(radius / m_toothProfile->getMiddleLength());
}

void SimpleGear::setToothProfile(ToothProfile* curve) {
	// //TODO: do we need 'delete m_toothProfile'?
	// m_toothProfile = curve;
}

void SimpleGear::getToothSpaceProfile(vector<hpvec2>& toothSpaceProfile) {
	BSplineCurve<hpvec2> curve;
	m_toothProfile->getCurve(curve);
	hpreal low,high;
	curve.getParameterRange(low, high);
	hpreal delta = (high - low) / (hpreal)(toothSpaceProfile.capacity() - 1); // -1 so whole thooth is sampled
	for(int i = toothSpaceProfile.capacity() / 2 - 1;  i >= 0; i--) {
		hpvec2 point = curve.getValueAt(low + i * delta);
		toothSpaceProfile.push_back(hpvec2(-point.x, point.y));
	}
	for(uint i = 0; i < toothSpaceProfile.capacity()/2; i++) {
		hpvec2 point = curve.getValueAt(low + i*delta);
		toothSpaceProfile.push_back(point);
	}
}

void SimpleGear::getToothProfile(vector<hpvec2>& toothProfile) {
	hpuint nPointsPerTooth = toothProfile.size();
	BSplineCurve<hpvec2> curve;
	m_toothProfile->getCurve(curve);
	hpreal low,high;
	curve.getParameterRange(low, high);
	hpreal delta = (high - low) / (hpreal)(nPointsPerTooth - 1); // -1 so whole thooth is sampled
	for(hpuint i = 0; i < nPointsPerTooth; ++i) {
		hpvec2 point = curve.getValueAt(low + (hpreal) (i * delta));
		toothProfile[i] = point;
	}
}

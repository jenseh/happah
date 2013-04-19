#include "FocalBezierCurve.h"
#include "happah/HappahUtils.h"
#define RADIUS 1.0f


FocalBezierCurve::FocalBezierCurve(hpreal phi,vector<hpvec3>* controlPoints)
	: m_phi(phi),m_controlPoints(controlPoints),m_center(hpvec3(0.0f)) {
	m_currentControlPoints = new vector<hpvec3>;
	m_currentDegree = m_controlPoints->size()-1;
}

FocalBezierCurve::~FocalBezierCurve() {
	// TODO Auto-generated destructor stub
}

hpvec3 FocalBezierCurve::evaluate(hpreal delta){
	m_currentDegree = (m_controlPoints->size()-1);
	*m_currentControlPoints = *m_controlPoints;
	while(m_currentDegree > 0){
		generateNewControlPoints(delta);
	}
	return m_currentControlPoints->at(0);
}

void FocalBezierCurve::update(hpreal phi, vector<hpvec3>* controlPoints){
	m_phi = phi;
	m_controlPoints = controlPoints;
}


void FocalBezierCurve::generateNewControlPoints(hpreal delta){
	hpvec3 result[m_currentDegree];
	// Erstelle Schnittpunkte d1...dn mit dem Kreis
	hpvec3 dn[m_currentDegree+1];
	for(int i = 0; i<(m_currentDegree+1);i++){
		dn[i]=hpvec3(m_currentControlPoints->at(i).x,0.0f,RADIUS);
	}
	// TODO : SAVE LOOPS BY CALCULATING STUFF EARLIER and be more careful with where to end
	// Berechne As
	hpvec3 an[m_currentDegree];
	for (int i = 0; i< m_currentDegree; i++){
	hpvec3 direction = HPUtils::polarToCartesianCoordinates(dn[i+1])-HPUtils::polarToCartesianCoordinates(dn[i]);
	an[i] = HPUtils::polarToCartesianCoordinates(dn[i])+(delta * direction);
	}

	// Berechne Neue Kontrollpunkte
	for (int i = 0; i<m_currentDegree; i++){
		result[i] = HPUtils::cartesianToPolarCoordinates(HPUtils::calculate2DLineIntersection(m_center,an[i],HPUtils::polarToCartesianCoordinates(m_currentControlPoints->at(i)),HPUtils::polarToCartesianCoordinates(m_currentControlPoints->at(i+1))));
	}

	// write Back
	for(int i = 0; i<m_currentDegree; i++){
		m_currentControlPoints->at(i)= result[i];
	}
	m_currentDegree--;
}

hpreal FocalBezierCurve::getPhi(){
	return m_phi;
}

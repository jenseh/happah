#include "FocalSpline.h"
#include <iostream>

using namespace std;

FocalSpline::FocalSpline()
	: m_center(hpvec3(0.0f,0.0f,0.0f)),m_radius(1.0f),m_detail(50),m_currentDegree(0),m_phi(0),m_fraction(0) {
	m_controlPoints = new vector<hpvec3>;
	m_generatedSpline = new vector<hpvec3>;
	m_currentControlPoints = new vector<hpvec3>;



}

FocalSpline::~FocalSpline() {

}
void FocalSpline::setPolarControlPoint(hpuint index, hpvec3 controlPoint){
	m_controlPoints->at(index)=controlPoint;
	adjustControlPoints(index);
}

hpvec3 FocalSpline::getPolarControlPoint(hpuint index){
	return m_controlPoints->at(index);
}


void FocalSpline::setCartesianControlPoint(hpuint index, hpvec3 controlPoint){
	m_controlPoints->at(index)=cartesianToPolarCoordinates(controlPoint);
	adjustControlPoints(index);
}

hpvec3 FocalSpline::getCartesianControlPoint(hpuint index){
	return polarToCartesianCoordinates(m_controlPoints->at(index));
}

void FocalSpline::init(int degree){
	hpreal radius = 3.0f;
	m_phi = (M_PI/(float)(degree))/2.0f;
	for (int i = 0; i <= degree ; i++){
		hpvec3 controlPoint = hpvec3(i*m_phi,0.0f,radius);
		m_controlPoints->push_back(controlPoint);
	}
	m_phiComplete = m_controlPoints->at(degree).x - m_controlPoints->at(0).x;
	cout << "phiComplete: " << m_phiComplete << endl;
	update();
}

void FocalSpline::update(){

	generateFocalSpline();

}

void FocalSpline::generateFocalSpline(){
	m_generatedSpline->clear();
	m_fraction = 0.0f;

	for(int i = 0 ; i < m_detail;i++){
		m_fraction = m_fraction + 1.0f/((hpreal)m_detail + 1.0f);
		m_currentDegree = (m_controlPoints->size()-1);
		*m_currentControlPoints = *m_controlPoints;
		while(m_currentDegree > 0){
			generateNewControlPoints();
		}
		m_generatedSpline->push_back(m_currentControlPoints->at(0));
	}
}
void FocalSpline::generateNewControlPoints(){
	hpvec3 result[m_currentDegree];
	// Erstelle Schnittpunkte d1...dn mit dem Kreis
	hpvec3 dn[m_currentDegree+1];
	for(int i = 0; i<(m_currentDegree+1);i++){
		dn[i]=hpvec3(m_currentControlPoints->at(i).x,0.0f,m_radius);
	}
	// TODO : SAVE LOOPS BY CALCULATING STUFF EARLIER and be more careful with where to end
	// Berechne As
	hpvec3 an[m_currentDegree];
	for (int i = 0; i< m_currentDegree; i++){
	hpvec3 direction = polarToCartesianCoordinates(dn[i+1])-polarToCartesianCoordinates(dn[i]);
	an[i] = polarToCartesianCoordinates(dn[i])+(m_fraction * direction);
	}

	// Berechne Neue Kontrollpunkte
	for (int i = 0; i<m_currentDegree; i++){
		result[i] = cartesianToPolarCoordinates(calculateIntersection(m_center,an[i],polarToCartesianCoordinates(m_currentControlPoints->at(i)),polarToCartesianCoordinates(m_currentControlPoints->at(i+1))));
	}

	// write Back
	for(int i = 0; i<m_currentDegree; i++){
		m_currentControlPoints->at(i)= result[i];
	}
	m_currentDegree--;
}

hpvec3 FocalSpline::calculateIntersection(hpvec3 a1,hpvec3 a2, hpvec3 b1, hpvec3 b2){
	hpreal x1 = a1.x , x2=a2.x, x3 = b1.x, x4 = b2.x;
	hpreal y1 = a1.y , y2=a2.y, y3 = b1.y, y4 = b2.y;

	hpreal m = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);
	if (m == 0)
		return hpvec3(0.0f,0.0f,0.0f);
	float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
	float x = ( pre * (x3 - x4) - (x1 - x2) * post ) / m;
	float y = ( pre * (y3 - y4) - (y1 - y2) * post ) / m;

	return hpvec3(x,y,0.0f);
}

void FocalSpline::adjustControlPoints(int index){
	if (index == 0)
		m_phi = m_controlPoints->at(index+1).x - m_controlPoints->at(index).x;
	else
		m_phi = m_controlPoints->at(index).x - m_controlPoints->at(index-1).x;
	m_phiComplete = m_phi*m_controlPoints->size();
	if (m_phiComplete > M_PI){
		m_phiComplete = M_PI;
		m_phi = m_phiComplete/m_controlPoints->size();
	}
	for(int i= 0; i < m_controlPoints->size(); i++){
		cout << "Came here " << endl;
		hpreal phiPoint = m_controlPoints->at(index).x;
		hpreal newPhi = 0.0f;
		newPhi=phiPoint+(i-index)*m_phi;
		m_controlPoints->at(i).x = newPhi;
	}

}

LineMesh* FocalSpline::toLineMesh(){
	std::vector<hpvec3>* verticesAndNormals = new std::vector<hpvec3>;
	std::vector<hpuint>* indices = new std::vector<hpuint>;

	//draw controlpolygon
	int i = 0;
	for(vector<hpvec3>::iterator it = m_controlPoints->begin(); it != m_controlPoints->end(); ++it){
			hpvec3 vertexPosition = polarToCartesianCoordinates(*it);
			hpvec3 vertexNormal = vertexPosition - m_center;
			verticesAndNormals->push_back(vertexPosition);
			verticesAndNormals->push_back(vertexNormal);
			if (it != m_controlPoints->begin()){
				indices->push_back(i);
			}
			indices->push_back(i);
			i++;
		}
	indices->pop_back();

	// draw Circle
	int iTemp = i;
	int detail = 30;
	hpreal phi_c = (2*M_PI)/(float)detail;
	for (int j = 0; j < detail ; j++){
		hpvec3 vertexPosition = polarToCartesianCoordinates(hpvec3(j*phi_c,0.0f,m_radius));
		hpvec3 vertexNormal = vertexPosition - m_center;

		verticesAndNormals->push_back(vertexPosition);
		verticesAndNormals->push_back(vertexNormal);
		if (j != 0){
			indices->push_back(i);
		}
		indices->push_back(i);
		i++;
	}
	indices->push_back(iTemp);
	//draw generated Spline
	{
		for(vector<hpvec3>::iterator it = m_generatedSpline->begin(); it != m_generatedSpline->end(); ++it){
				hpvec3 vertexPosition = polarToCartesianCoordinates(*it);
				hpvec3 vertexNormal = vertexPosition - m_center;
				verticesAndNormals->push_back(vertexPosition);
				verticesAndNormals->push_back(vertexNormal);
				if (it != m_generatedSpline->begin()){
					indices->push_back(i);
				}
				indices->push_back(i);
				i++;
			}
		indices->pop_back();
	}
	return new LineMesh(verticesAndNormals, indices);
}

PointCloud* FocalSpline::toPointCloud(){
	std::vector<hpvec3>* vertices = new std::vector<hpvec3>;
	for(vector<hpvec3>::iterator it = m_controlPoints->begin(); it != m_controlPoints->end(); ++it){
		vertices->push_back(polarToCartesianCoordinates(*it));


	}
	/*
	// Draw Generated Spline as Points
	for(vector<hpvec3>::iterator it = m_generatedSpline->begin(); it != m_generatedSpline->end(); ++it){
			vertices->push_back(polarToCartesianCoordinates(*it));
	}
	*/
	return new PointCloud(vertices);
}


hpvec3 FocalSpline::cartesianToPolarCoordinates(hpvec3 cartesian){
	hpreal radius = sqrt((cartesian.x*cartesian.x)+(cartesian.y*cartesian.y));
	hpreal x = cartesian.x-m_center.x;
	hpreal y = cartesian.y-m_center.y;
	hpreal phi = 0.0f;
	if (x>0.0f)
		phi = atan(y/x);
	if (x<0.0f)
		phi = M_PI+atan(y/x);
	if (x==0.0f)
		phi = M_PI/2.0f;

	hpvec3 polar = hpvec3(phi,0.0f,radius);
	return polar;
}

hpvec3 FocalSpline::polarToCartesianCoordinates(hpvec3 polar){
	hpvec3 cartesian;
	cartesian.x = polar.z * cos(polar.x);
	cartesian.y = polar.z * sin(polar.x);
	cartesian.z = 0.0f;
	return cartesian;
}

#include "FocalSpline.h"
#include <iostream>

using namespace std;

FocalSpline::FocalSpline()
	: m_center(hpvec3(0.0f,0.0f,0.0f)),m_radius(1.0f),m_detail(50),m_currentDegree(0),m_phi(0),m_fraction(0),m_phiComplete(0) {
	m_controlPoints = new vector<hpvec3>;
	m_generatedSpline = new vector<hpvec3>;
	m_currentControlPoints = new vector<hpvec3>;



}

FocalSpline::~FocalSpline() {

}
void FocalSpline::setPolarControlPoint(hpuint index, hpvec3 controlPoint){
	m_controlPoints->at(index)=controlPoint;
	adjustControlPoints(index);
	update();
}

hpvec3 FocalSpline::getPolarControlPoint(hpuint index){
	return m_controlPoints->at(index);
}


void FocalSpline::setCartesianControlPoint(hpuint index, hpvec3 controlPoint){
	m_controlPoints->at(index)=cartesianToPolarCoordinates(controlPoint);
	adjustControlPoints(index);
	update();
}

hpvec3 FocalSpline::getCartesianControlPoint(hpuint index){
	return polarToCartesianCoordinates(m_controlPoints->at(index));
}

void FocalSpline::init(int degree){
	hpreal radius = 3.0f;
	if (degree  <1){
		update();
		return;
	}
	else
	{
			m_phi = (M_PI/(float)(degree))/2.0f;
		for (int i = 0; i <= degree ; i++){
			hpvec3 controlPoint = hpvec3(i*m_phi,0.0f,radius);
			m_controlPoints->push_back(controlPoint);
		}
		if (m_controlPoints->size() > 0){
		m_phiComplete = m_controlPoints->at(degree).x - m_controlPoints->at(0).x;
		update();
		}
	}
}

void FocalSpline::addControlPoint(){
	hpvec3 newPoint;
	hpreal newPhi;
	hpreal newRadius;

	if (m_controlPoints->size()<1){
		newPhi = M_PI/4.0f;
		newRadius = m_radius*3;
		m_phi = newPhi;

	}
	else{
	newPhi= m_controlPoints->back().x + m_phi;
	if  (newPhi == 0){
		newPhi = M_PI/4.0f;
		m_phi = newPhi;
	}
	newRadius = m_controlPoints->back().z;
	if (newRadius == 0)
		newRadius== m_radius*3;
	}

	newPoint = hpvec3(newPhi,0,newRadius);
	m_controlPoints->push_back(newPoint);
	if (m_controlPoints->size() > 1){
	adjustControlPoints(m_controlPoints->size()-1);
	}
	update();
}

void FocalSpline::addControlPoint(hpvec3 point){
	hpvec3 newPoint = cartesianToPolarCoordinates(point);
	int insertionIndex;

	int smaller = 0;
	for(int i=0; i < m_controlPoints->size(); i++){
		if (newPoint.x < m_controlPoints->at(i).x){
			m_controlPoints->insert(m_controlPoints->begin()+i,newPoint);
			adjustControlPoints(i);
			break;
		}
	if (newPoint.x > m_controlPoints->back().x){
		m_controlPoints->push_back(newPoint);
		adjustControlPoints(m_controlPoints->size()-1);
	}
	}
	update();

}

void FocalSpline::update(){

	generateFocalSpline();

}

void FocalSpline::generateFocalSpline(){
	if (m_controlPoints->size() <1){
		return;
	}

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
	if (m_phi < 0)
		m_phi = 0.0f;
	m_phiComplete = m_phi*m_controlPoints->size();
	if (m_phiComplete > M_PI){
		m_phiComplete = M_PI;
		m_phi = m_phiComplete/m_controlPoints->size();
	}

	for(int i= 0; i < m_controlPoints->size(); i++){
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
	if (m_controlPoints->size()>0){
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
	}
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
	if (m_generatedSpline->size()>0){
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
	if (m_controlPoints->size()>0){
	for(vector<hpvec3>::iterator it = m_controlPoints->begin(); it != m_controlPoints->end(); ++it){
		vertices->push_back(polarToCartesianCoordinates(*it));


	}
	}
	/*
	// Draw Generated Spline as Points
	for(vector<hpvec3>::iterator it = m_generatedSpline->begin(); it != m_generatedSpline->end(); ++it){
			vertices->push_back(polarToCartesianCoordinates(*it));
	}
	*/
	// draw Center
	vertices->push_back(m_center);
	return new PointCloud(vertices);
}


hpvec3 FocalSpline::cartesianToPolarCoordinates(hpvec3 cartesian){
	hpreal radius = sqrt((cartesian.x*cartesian.x)+(cartesian.y*cartesian.y));
	hpreal x = cartesian.x-m_center.x;
	hpreal y = cartesian.y-m_center.y;
	hpreal phi = 0.0f;
	if (y >= 0){
	if (x>0.0f)
		phi = atan(y/x);
	if (x<0.0f)
		phi = M_PI+atan(y/x);
	if (x==0.0f)
		phi = M_PI/2.0f;
	}
	else {
		if (x>0.0f){
			phi=2*M_PI+atan(y/x);
		}
		if (x<0.0f){
			phi = atan(y/x) + M_PI;
		}
		if (x==0.0f){
			phi= 3*M_PI/2.0f;
		}

	}

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

int FocalSpline::getDegree(){
	return m_controlPoints->size()-1;
}

void FocalSpline::removeControlPoint(int index){

	m_controlPoints->erase(m_controlPoints->begin()+index);
	if (index > 1)
		adjustControlPoints(index-1);
	update();

}

void FocalSpline::setDetail(int detail){
	m_detail = detail;
	update();
}

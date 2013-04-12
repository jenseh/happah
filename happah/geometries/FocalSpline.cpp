#include "FocalSpline.h"
#include <iostream>

using namespace std;

FocalSpline::FocalSpline()
	: m_center(hpvec3(0.0f,0.0f,0.0f)),m_radius(1.0f) {
	m_controlPoints = new vector<hpvec3>;
	m_generatedSpline = new vector<hpvec3>;
	init(2);
	generateFocalSpline();

}

FocalSpline::~FocalSpline() {

}

void FocalSpline::init(int degree){
	hpreal radius = 3.0f;
	hpreal phi = M_PI/(float)(degree);
	for (int i = 0; i <= degree ; i++){
		hpvec3 controlPoint = hpvec3(i*phi,0.0f,radius);
		cout << "FocalSpline CP: " << controlPoint.x<< endl;
		m_controlPoints->push_back(controlPoint);
	}
}

void FocalSpline::update(){
	hpvec3 point = m_controlPoints->at(1);
	point.z = point.z*2;
	m_controlPoints->at(1)= point;
	generateFocalSpline();

}

void FocalSpline::generateFocalSpline(){
	m_generatedSpline->clear();
	for(vector<hpvec3>::iterator it = m_controlPoints->begin(); it != m_controlPoints->end(); ++it){
		hpvec3 point = *it;
		point.z = point.z/2.0f;
		m_generatedSpline->push_back(point);
	}
}

LineMesh* FocalSpline::toLineMesh(){
	std::vector<hpvec3>* vertexData = new std::vector<hpvec3>;
	std::vector<hpuint>* indices = new std::vector<hpuint>;

	//draw controlpolygon
	int i = 0;
	for(vector<hpvec3>::iterator it = m_controlPoints->begin(); it != m_controlPoints->end(); ++it){
			hpvec3 vertexPosition = polarToCartesianCoordinates(*it);
			hpvec3 vertexNormal = vertexPosition - m_center;
			vertexData->push_back(vertexPosition);
			vertexData->push_back(vertexNormal);
			cout << "CP Position: " << vertexPosition.x << " " << vertexPosition.y << " " << vertexPosition.z << endl;
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

		vertexData->push_back(vertexPosition);
		vertexData->push_back(vertexNormal);
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
				vertexData->push_back(vertexPosition);
				vertexData->push_back(vertexNormal);
				cout << "Spline point Position: " << vertexPosition.x << " " << vertexPosition.y << " " << vertexPosition.z << endl;
				if (it != m_generatedSpline->begin()){
					indices->push_back(i);
				}
				indices->push_back(i);
				i++;
			}
		indices->pop_back();
	}
	return new LineMesh(vertexData, indices);
}

PointCloud* FocalSpline::toPointCloud(){
	std::vector<hpvec3>* vertices = new std::vector<hpvec3>;
	for(vector<hpvec3>::iterator it = m_controlPoints->begin(); it != m_controlPoints->end(); ++it){
		vertices->push_back(polarToCartesianCoordinates(*it));


	}
	return new PointCloud(vertices);
}

void FocalSpline::handleSelection(){

}

void FocalSpline::handleSelection(int pointIndex){

}

hpvec3 FocalSpline::cartesianToPolarCoordinates(hpvec3 cartesian){
	hpvec3 polar;
	return polar;
}

hpvec3 FocalSpline::polarToCartesianCoordinates(hpvec3 polar){
	hpvec3 cartesian;
	cartesian.x = polar.z * cos(polar.x);
	cartesian.y = polar.z * sin(polar.x);
	cartesian.z = 0.0f;
	return cartesian;
}

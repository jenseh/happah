#include "FocalSpline.h"
#include <iostream>

using namespace std;

FocalSpline::FocalSpline()
	: m_center(hpvec3(0.0f,0.0f,0.0f)),m_radius(1.0f) {
	m_controlPoints = new vector<hpvec3>;
	m_generatedSpline = new vector<hpvec3>;
	init(2);

}

FocalSpline::~FocalSpline() {

}

void FocalSpline::init(int degree){
	hpreal radius = 2.0f;
	hpreal phi = 180.0f/(float)(degree);
	for (hpreal i = 0.0f; i <= 180.0f ; i = i+phi){
		hpvec3 controlPoint = hpvec3(i,0.0f,radius);
		cout << "FocalSpline CP: " << controlPoint.x<< endl;
		m_controlPoints->push_back(controlPoint);
	}
}

void FocalSpline::update(){

}

void FocalSpline::generateFocalSpline(){
	for(vector<hpvec3>::iterator it = m_controlPoints->begin(); it != m_controlPoints->end(); ++it){
		m_generatedSpline->push_back(*it);
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
			if (it != m_controlPoints->begin()){
				indices->push_back(i);
			}
			indices->push_back(i);
			i++;
		}
	indices->pop_back();
	//draw generated Spline
	{
		// nothing here yet
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

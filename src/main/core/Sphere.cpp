/*
 * Sphere.cpp
 *
 *  Created on: Nov 28, 2012
 *      Author: matthias
 */

#include "Sphere.h"

Sphere::Sphere(vec4 center,float radius) : GeometryObject(center){
	// TODO Auto-generated constructor stub
	center_=center;
	radius_=radius;
}

Sphere::~Sphere() {
	// TODO Auto-generated destructor stub
}


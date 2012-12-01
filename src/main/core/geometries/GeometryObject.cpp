/*
 * GeomtryObject.cpp
 *
 *  Created on: Nov 28, 2012
 *      Author: matthias
 */

#include "GeometryObject.h"

GeometryObject::GeometryObject() {
	// TODO Auto-generated constructor stub

}

GeometryObject::~GeometryObject() {
	// TODO Auto-generated destructor stub
}

void GeometryObject::init() {
    modelMatrix_.setToIdentity();
}

void GeometryObject::dataPushback(glm::vec4 data) {
    vertexData_.push_back(data);
}

void GeometryObject::rotate(float angle, float x, float y, float z) {
    modelMatrix_.rotate(angle, x, y, z);
}

void GeometryObject::translate(float x, float y, float z) {
    modelMatrix_.translate(x, y, z);
}


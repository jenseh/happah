/*
 * GeomtryObject.cpp
 *
 *  Created on: Nov 28, 2012
 *      Author: matthias
 */

#include "GeometryObject.h"

GeometryObject::GeometryObject() {
    modelMatrix_.setToIdentity();
}

GeometryObject::~GeometryObject() {}

void GeometryObject::rotate(float angle, float x, float y, float z) {
    modelMatrix_.rotate(angle, x, y, z);
}

void GeometryObject::translate(float x, float y, float z) {
    modelMatrix_.translate(x, y, z);
}

void GeometryObject::scale(float x, float y, float z) {
    modelMatrix_.scale(x, y, z);
}

std::string GeometryObject::getName() {
    return name_;
}

void GeometryObject::setName(std::string name) {
    name_ = name;
}

/*
 * GeomtryObject.cpp
 *
 *  Created on: Nov 28, 2012
 *      Author: matthias
 */

#include "GeometryObject.h"
int GeometryObject::objectIdCounter_ = 0;

GeometryObject::GeometryObject() {
    objectId_ = GeometryObject::objectIdCounter_++;
    modelMatrix_.setToIdentity();
}

GeometryObject::~GeometryObject() {}

// Rotate the geometry by the specified angle (in degrees) around axis (x,y,z)
void GeometryObject::rotate(float angle, float x, float y, float z) {
    modelMatrix_.rotate(angle, x, y, z);
}

void GeometryObject::translate(float x, float y, float z) {
    modelMatrix_.translate(x, y, z);
}

// This function may never be used since the model internally is already in world coordinates
//void GeometryObject::scale(float x, float y, float z) {
//    modelMatrix_.scale(x, y, z);
//}

std::string GeometryObject::getName() {
    return name_;
}

int GeometryObject::getObjectId() {
  return objectId_;
}

void GeometryObject::setName(std::string name) {
    name_ = name;
}

QMatrix4x4* GeometryObject::getModelMatrix() {
    return &modelMatrix_;
}
void GeometryObject::setModelMatrix(QMatrix4x4& modelMatrix) {
    modelMatrix_ = modelMatrix;
}

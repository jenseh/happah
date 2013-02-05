/*
 * GeomtryObject.cpp
 *
 *  Created on: Nov 28, 2012
 *      Author: matthias
 */

#include "GeometryObject.h"
int GeometryObject::m_objectIdCounter = 0;

std::string concatStringNumber(std::string str, int number) {
  std::ostringstream sstream;
  sstream << str << number;
  return sstream.str();
}

GeometryObject::GeometryObject(const std::string name) {
    m_objectId = GeometryObject::m_objectIdCounter++;
    m_modelMatrix.setToIdentity();

    int randomInt = rand() % 255 + 1;
    m_name = concatStringNumber("Unnamed", randomInt);
}

GeometryObject::~GeometryObject() {}

// Rotate the geometry by the specified angle (in degrees) around axis (x,y,z)
void GeometryObject::rotate(float angle, float x, float y, float z) {
    m_modelMatrix.rotate(angle, x, y, z);
}

void GeometryObject::translate(float x, float y, float z) {
    m_modelMatrix.translate(x, y, z);
}

// This function may never be used since the model internally is already in world coordinates
//void GeometryObject::scale(float x, float y, float z) {
//    m_modelMatrix.scale(x, y, z);
//}

std::string GeometryObject::getName() {
    return m_name;
}

int GeometryObject::getObjectId() {
  return m_objectId;
}

void GeometryObject::setName(std::string name) {
    m_name = concatStringNumber(name, m_objectIdCounter);
}

QMatrix4x4* GeometryObject::getModelMatrix() {
    return &m_modelMatrix;
}
void GeometryObject::setModelMatrix(QMatrix4x4 modelMatrix) {
    m_modelMatrix = modelMatrix;
}

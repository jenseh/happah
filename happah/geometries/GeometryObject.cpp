/*
 * GeomtryObject.cpp
 *
 *  Created on: Nov 28, 2012
 *      Author: matthias
 */

#include "happah/geometries/GeometryObject.h"
int GeometryObject::m_objectIdCounter = 0;

GeometryObject::GeometryObject(const std::string name) {
    m_modelMatrix.setToIdentity();
    m_name = name;
}

GeometryObject::GeometryObject() {
    m_modelMatrix.setToIdentity();

    int randomInt = rand() % 1000;
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
    std::cout << "Thou shalt not change an objects name if possible" << std::endl;
    m_name = concatStringNumber(name, m_objectIdCounter);
}

QMatrix4x4* GeometryObject::getModelMatrix() {
    return &m_modelMatrix;
}
void GeometryObject::setModelMatrix(QMatrix4x4 modelMatrix) {
    m_modelMatrix = modelMatrix;
}

// Just a utility function that appends a number to a string
std::string GeometryObject::concatStringNumber(std::string str, int number) {
  std::ostringstream sstream;
  sstream << str << number;
  return sstream.str();
}

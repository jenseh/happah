/*
 * GeomtryObject.h
 *
 *  Created on: Nov 28, 2012
 *      Author: matthias
 */

#ifndef GEOMETRYOBJECT_H_
#define GEOMETRYOBJECT_H_

#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <QMatrix4x4>
#include "happah/primitives/Color.h"

class GeometryObject{

public:
    GeometryObject(const std::string name);
    GeometryObject();
    virtual ~GeometryObject();


    // Transformations
    void rotate(float angle, float x, float y, float z);
    void translate(float x, float y, float z);
    void scale(float x, float y, float z);

    std::string getName();
    int getObjectId();
    void setName(std::string name);
    QMatrix4x4* getModelMatrix();
    void setModelMatrix(QMatrix4x4 modelMatrix);

    std::string concatStringNumber(std::string str, int number);

protected:
    QMatrix4x4 m_modelMatrix;
    std::string m_name;
    int m_objectId;
    static int m_objectIdCounter;
};

#endif /* GEOMETRYOBJECT_H_ */

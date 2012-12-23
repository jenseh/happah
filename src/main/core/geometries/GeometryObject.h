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
#include <QMatrix4x4>

class GeometryObject{

public:
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

protected:
    QMatrix4x4 modelMatrix_;
    std::string name_;
    int objectId_;
    static int objectIdCounter_;
};

#endif /* GEOMETRYOBJECT_H_ */

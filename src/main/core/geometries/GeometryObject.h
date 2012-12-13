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
    void setName(std::string name);

protected:
    QMatrix4x4 modelMatrix_;

private:
    std::string name_;
};

#endif /* GEOMETRYOBJECT_H_ */

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
#include <QMatrix4x4>

class GeometryObject {

public:
    GeometryObject();
    virtual ~GeometryObject();

    // For drawing
    void init();

    void createVertexData();


    // Transformations
    void rotate(float angle, float x, float y, float z);
    void translate(float x, float y, float z);

protected:
    std::vector<glm::vec4> vertexData_;
    QMatrix4x4 modelMatrix_;

    void dataPushback(glm::vec4 data);
};

#endif /* GEOMETRYOBJECT_H_ */

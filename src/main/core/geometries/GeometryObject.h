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

#include "../models/QuadliteralMesh.h"

class GeometryObject{

public:
    GeometryObject();
    virtual ~GeometryObject();

    void createVertexData();
    QuadliteralMesh* toQuadrilateralMesh();

protected:
    std::vector<glm::vec4> vertexData_;
    void dataPushback(glm::vec4 data);
};

#endif /* GEOMETRYOBJECT_H_ */

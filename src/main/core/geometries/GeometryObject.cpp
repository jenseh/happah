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



void GeometryObject::dataPushback(glm::vec4 data) {
    vertexData_.push_back(data);
}

QuadliteralMesh* GeometryObject::toQuadrilateralMesh() {
    return new QuadliteralMesh(vertexData_);
}

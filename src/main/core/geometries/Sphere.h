/*
 * Sphere.h
 *
 *  Created on: Nov 28, 2012
 *      Author: matthias
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include <math.h>
#include <glm/glm.hpp>
#include "NonDrawable.h"
#include "../models/QuadMesh.h"

using namespace std;

class Sphere: public NonDrawable {

public:
    Sphere(float radius = 1.0f, glm::vec4 center= glm::vec4(0.0f,0.0f,0.0f,1.0f),
           std::string name = "Sphere");
           
    ~Sphere();

    float getRadius();

    QuadMesh* toQuadMesh();
    TriangleMesh* toTriangleMesh();

private:
    float m_radius;
    glm::vec4 m_center;
    std::vector<glm::vec4> m_vertexData;
};
#endif /* SPHERE_H_ */

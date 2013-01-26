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
    Sphere(float radius = 1.0f);
    ~Sphere();

    bool hit(glm::vec3 rayPos, glm::vec3 rayDir);
    float getRadius();
    glm::vec3 getHitpoint();
    QuadMesh* toQuadMesh();
    TriangleMesh* toTriangleMesh();

private:
    float m_radius;
    glm::vec3 m_hitpoint;
    std::vector<glm::vec4> m_vertexData;

    bool quad(float A, float B, float C, float *t0, float* t1);
};
#endif /* SPHERE_H_ */

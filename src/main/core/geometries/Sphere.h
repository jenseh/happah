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
#include "GeometryObject.h"

using namespace std;

class Sphere: public GeometryObject {

public:
    Sphere(float radius = 1.0f);

    virtual ~Sphere();
    bool hit(glm::vec3 rayPos, glm::vec3 rayDir);
    float getRadius();
    glm::vec3 getHitpoint();
    void createVertexData();

private:
    float radius_;
    glm::vec3 hitpoint_;

    bool quad(float A, float B, float C, float *t0, float* t1);
};
#endif /* SPHERE_H_ */

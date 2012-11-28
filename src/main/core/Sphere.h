/*
 * Sphere.h
 *
 *  Created on: Nov 28, 2012
 *      Author: matthias
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include "GeometryObject.h"

using glm::vec4;

class Sphere: public GeometryObject {
public:
	Sphere(vec4 center=vec4(0.0f,0.0f,0.0f,0.0f),float radius=1.0f);
	virtual ~Sphere();
private:
	vec4 center_;
	float radius_;
};

#endif /* SPHERE_H_ */

#ifndef SPHERE_H_
#define SPHERE_H_

#include <glm/glm.hpp>
#include "GeometryObject.h"

class Sphere: public GeometryObject {

public:
    Sphere(float radius = 1.0f, QMatrix4x4* projectionMatrix = 0,
            QMatrix4x4 *viewMatrix = 0, QVector3D* camPos = 0);
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

#endif
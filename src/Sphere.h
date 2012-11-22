#ifndef SPHERE_H_
#define SPHERE_H_

#include <glm/glm.hpp>
#include "GeometryObject.h"

class Sphere: public GeometryObject {
public:
	Sphere(float _radius = 1.0f, QMatrix4x4 *_projectionMatrix = 0,
			QMatrix4x4 *_viewMatrix = 0, QVector3D* _camPos = 0);
	virtual ~Sphere();
	bool hit(glm::vec3 rayPos, glm::vec3 rayDir);
	float getRadius();
	glm::vec3 getHitpoint();
	void CreateVertexData();
private:
	float radius;
	bool quad(float A, float B, float C, float *t0, float* t1);
	glm::vec3 hitpoint;
};

#endif

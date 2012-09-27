#ifndef SPHERE_H_
#define SPHERE_H_

#include <glm/glm.hpp>

class Sphere {
public:
	Sphere(glm::vec3 _center = glm::vec3(0.0f,0.0f,0.0f),float _radius = 1.0f);
	virtual ~Sphere();
	bool hit(glm::vec3 rayPos,glm::vec3 rayDir);
	float getRadius();
	glm::vec3 getCenter();
	glm::vec3 getHitpoint();

private:
	glm::vec3 center;
	float radius;
	bool quad(float A,float B,float C, float *t0,float* t1);
	glm::vec3 hitpoint;


};

#endif

#include <math.h>

#include "sphere.h"

using namespace std;

Sphere::Sphere(glm::vec3 _center,float _radius) {
	center = _center;
	radius = _radius;

}

Sphere::~Sphere() {
}

bool Sphere::hit(glm::vec3 rayPos, glm::vec3 rayDir){
	float A,B,C;
	A = rayDir.x*rayDir.x + rayDir.y*rayDir.y+rayDir.z*rayDir.z;
	B = 2*(rayDir.x*rayPos.x + rayDir.y*rayPos.y+rayDir.z*rayPos.z);
	C = rayPos.x*rayPos.x + rayPos.y*rayPos.y+rayPos.z*rayPos.z -radius*radius;

	float t0,t1;
	if(!quad(A,B,C,&t0,&t1))
		return false;
	float tmin = glm::min(t0,t1);
	hitpoint = rayPos + tmin*rayDir;

	return true;
}

bool Sphere::quad(float A,float B,float C,float *t0,float *t1){
	float q;
	float discrim = B*B - 4.0f*A*C;

	if (discrim < 0)
		return false;
	float root = std::sqrt(discrim);
	if ( B< 0)
		q = -0.5f *(B-root);
	else
		q = -0.5f*(B+root);
	 *t0 = q/A;
	 *t1 = C / q;

	 if(*t0>*t1){
		 float temp = *t0;
	 	 *t0 = *t1;
	 	 *t1 = temp;
	 }
	 return true;

}

float Sphere::getRadius(){
	return radius;
}

glm::vec3 Sphere::getCenter(){
	return center;
}

glm::vec3 Sphere::getHitpoint(){
	return hitpoint;

}


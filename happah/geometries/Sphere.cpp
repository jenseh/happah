#include "happah/geometries/Sphere.h"

Sphere::Sphere(const hpvec3& center, hpreal radius) : m_center(center), m_radius(radius) {}

Sphere::~Sphere() {}

bool Sphere::isSphere(const hpvec3& v1, const hpvec3& v2, const hpvec3& v3, hpreal radius, hpvec3& center1, hpvec3& center2) {
	//TODO
	return false;
}

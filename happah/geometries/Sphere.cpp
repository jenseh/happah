#include "happah/geometries/Sphere.h"

Sphere::Sphere(const hpvec3& center, hpreal radius) : m_center(center), m_radius(radius) {}

Sphere::~Sphere() {}

const hpvec3& Sphere::getCenter() const {
	return m_center;
}

hpreal Sphere::getRadius() const {
	return m_radius;
}

bool Sphere::isSphere(const hpvec3& v1, const hpvec3& v2, const hpvec3& v3, hpreal radius, hpvec3& center1, hpvec3& center2) {
	//TODO
	return false;
}


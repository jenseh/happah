#include <exception>

using namespace std;

#include "happah/geometries/Plane.h"

Plane::Plane(hpvec3 origin, hpvec3 normal) 
	: m_normal(check(normal)), m_origin(origin) {}

Plane::Plane(const Plane& other)
	: m_normal(other.m_normal), m_origin(other.m_origin) {}

Plane::~Plane() {}

hpvec3& Plane::check(hpvec3& normal) {
	if(normal.x == 0.0 && normal.y == 0.0 && normal.z == 0.0) throw;
	return normal;
}

hpvec3 Plane::getNormal() const {
	return m_normal;
}

hpvec3 Plane::getOrigin() const {
	return m_origin;
}

void Plane::setNormal(hpvec3 normal) {
	check(normal);
	m_normal = normal;
}

void Plane::setOrigin(hpvec3 origin) {
	m_origin = origin;
}

Plane& Plane::operator=(const Plane& other) {
	if(this != &other) {
		m_normal = other.m_normal;
		m_origin = other.m_origin;
	}
	return *this;
}


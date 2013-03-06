#include "happah/geometries/Plane.h"

Plane::Plane( hpvec3 normal, hpvec3 basePoint ) :
	m_normal(normal), m_basePoint(basePoint) {
}

Plane::Plane( const Plane& other ) :
	m_normal( other.m_normal ), m_basePoint( other.m_basePoint ) {
}

Plane::~Plane() {}

Plane& Plane::operator=( const Plane& other ) {
	m_normal = other.m_normal;
	m_basePoint = other.m_basePoint;
}


hpvec3 Plane::getNormal() {
	return m_normal;
}

hpvec3 Plane::getBasePoint() {
	return m_basePoint;
}

//hpvec2 Plane::getExtent() {
//	return m_extent;
//}

bool Plane::setNormal( hpvec3 normal ) {
	if( normal != glm::vec3(0,0,0) ) {
		m_normal = normal;
		return true;
	}
	return false;
}

bool Plane::setBasePoint( hpvec3 basePoint ) {
	m_basePoint = basePoint;
	return true;
}

//bool Plane::setExtent( hpvec2 extent ) {
//	m_extent = extent;
//}

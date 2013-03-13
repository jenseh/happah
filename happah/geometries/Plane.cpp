#include <iostream>

using namespace std;

#include "happah/geometries/Plane.h"

Plane::Plane(hpvec3 origin, hpvec3 normal) 
	: m_normal(check(normal)), m_origin(origin) {
}

Plane::Plane(const Plane& other)
	: m_normal(other.m_normal), m_origin(other.m_origin) {}

Plane::~Plane() {}

hpvec3& Plane::check(hpvec3& normal) {
	if(normal.x == 0.0 && normal.y == 0.0 && normal.z == 0.0) {
		std::cerr << "Plane with normal == 0 generated!" << std::endl;
	}
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

TriangleMesh* Plane::toTriangleMesh() {
	hpreal edgeLength = 1.0f;
	std::vector<hpvec3>* vertexData = new std::vector<hpvec3>;
	std::vector<hpuint>* indices = new std::vector<hpuint>;

	hpvec3 normal = glm::normalize(m_normal);
	hpvec3 a = hpvec3(1.f, 0.f, 0.f);
	if( a == normal ) {
		a = hpvec3(0.f, 0.f, 1.f);
	}
	a -= glm::dot(a,normal)*normal;
	a = 0.5f*edgeLength*glm::normalize(a);
	hpvec3 b = 0.5f*edgeLength*glm::normalize(glm::cross(a,normal));

//	std::cout << a.x << a.y << a.z << std::endl;
//	std::cout << b.x << b.y << b.z << std::endl;
	
	vertexData->push_back(m_origin + a + b);
	vertexData->push_back(m_normal);
	vertexData->push_back(m_origin - a + b);
	vertexData->push_back(m_normal);
	vertexData->push_back(m_origin - a - b);
	vertexData->push_back(m_normal);
	vertexData->push_back(m_origin + a - b);
	vertexData->push_back(m_normal);

	indices->push_back(0);
	indices->push_back(2);
	indices->push_back(1);
	indices->push_back(0);
	indices->push_back(2);
	indices->push_back(3);
	return new TriangleMesh(vertexData, indices);
}

Plane& Plane::operator=(const Plane& other) {
	if(this != &other) {
		m_normal = other.m_normal;
		m_origin = other.m_origin;
	}
	return *this;
}


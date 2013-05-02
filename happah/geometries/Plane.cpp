#include <iostream>

using namespace std;

#include "happah/geometries/Plane.h"
#include "happah/HappahConstants.h"
#include "happah/HappahUtils.h"

Plane::Plane(hpvec3 origin, hpvec3 normal) 
	: m_normal(check(normal)), m_origin(origin) {
		setSystemXVector(hpvec3( 0.f, 0.f, -1.f ));
		setSystemXVector(hpvec3( 1.f, 0.f, 0.f ));
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

bool Plane::intersect( Ray& ray, hpvec3& intersectionPoint ) {
	if( glm::abs(glm::dot(ray.getDirection(), m_normal)) < HP_EPSILON ) {
		return false;
	}
	hpreal t = -(glm::dot(ray.getOrigin(), m_normal) + glm::dot(m_origin, m_normal)) / glm::dot(ray.getDirection(), m_normal);
	intersectionPoint = ray.getOrigin() + t*ray.getDirection();
	return true;
}

bool Plane::intersect( Ray& ray, hpvec2& intersectionPoint ) {
	hpvec3 tmpPoint;
	if( !intersect( ray, tmpPoint ) ) return false;

	hpvec3 directionY = glm::cross( glm::normalize(m_normal), m_localSystemXVector );
	intersectionPoint.x = glm::dot( m_localSystemXVector, tmpPoint - m_origin );
	intersectionPoint.y = glm::dot( glm::normalize(directionY), tmpPoint - m_origin );

	return true;
}

void Plane::setNormal(hpvec3 normal) {
	check(normal);
	if( glm::length( normal ) < HP_EPSILON ) return;
	hpvec3 newNormal    = glm::normalize( normal );
	hpvec3 normalAxis   = glm::normalize( m_normal );

	// if normal was infinitesimally changed, no need for proper rotation
	if( glm::length( newNormal - normalAxis ) < HP_EPSILON ) {
		m_normal = normal;
		setSystemXVector( m_localSystemXVector );
		return;
	}
	if( glm::length( newNormal + normalAxis ) < HP_EPSILON ) {
		m_normal = normal;
		setSystemXVector( -m_localSystemXVector );
		return;
	}

	// rotate local system x-vector to fit to new normal
	hpvec3 rotationAxis = glm::normalize( glm::cross( normal, m_normal ) );
	hpvec3 thirdAxis    = glm::normalize( glm::cross( m_normal, rotationAxis ) );

	// TODO rotation still wrong
	hpvec3 newSystemXVector = rotationAxis * glm::dot(m_localSystemXVector, rotationAxis)
		+ thirdAxis  * glm::dot(normalAxis, newNormal) * glm::dot(thirdAxis, m_localSystemXVector)
		- normalAxis * glm::dot(thirdAxis, newNormal)  * glm::dot(thirdAxis, m_localSystemXVector);

	m_normal = normal;
	setSystemXVector( newSystemXVector );
}

void Plane::setOrigin(hpvec3 origin) {
	m_origin = origin;
}

void Plane::setSystemXVector(hpvec3 systemXVector) {
	hpvec3 normal = glm::normalize( m_normal );
	if( glm::length( normal - glm::normalize(systemXVector) ) < HP_EPSILON ) return;
	if( glm::length( normal + glm::normalize(systemXVector) ) < HP_EPSILON ) return;
	systemXVector = systemXVector - glm::dot( normal, systemXVector ) * normal;
	m_localSystemXVector = glm::normalize( systemXVector );
}

hpvec3 Plane::getSystemXVector() {
	return m_localSystemXVector;
}

TriangleMesh* Plane::toTriangleMesh() {
	hpreal edgeLength = 1.0f;
	std::vector<hpvec3>* verticesAndNormals = new std::vector<hpvec3>;
	std::vector<hpuint>* indices = new std::vector<hpuint>;

	hpvec3 normal = hpvec3(0.f, 0.f, 1.f);
	hpvec3 origin = hpvec3(0.f, 0.f, 0.f);
	hpvec3 a = 0.5f*edgeLength*hpvec3(1.f, 0.f, 0.f);
	hpvec3 b = 0.5f*edgeLength*hpvec3(0.f, 1.f, 0.f);

	verticesAndNormals->push_back(origin + a + b);
	verticesAndNormals->push_back(normal);
	verticesAndNormals->push_back(origin - a + b);
	verticesAndNormals->push_back(normal);
	verticesAndNormals->push_back(origin - a - b);
	verticesAndNormals->push_back(normal);
	verticesAndNormals->push_back(origin + a - b);
	verticesAndNormals->push_back(normal);

	indices->push_back(0);
	indices->push_back(2);
	indices->push_back(1);
	indices->push_back(0);
	indices->push_back(2);
	indices->push_back(3);
	return new TriangleMesh(verticesAndNormals, indices);
}

PointCloud* Plane::toPointCloud() {

	std::vector<hpvec3>* verticesAndNormals = new std::vector<hpvec3>;
	std::vector<hpuint>* indices = new std::vector<hpuint>;

//	for (hpreal edgeLength=0.0f;edgeLength < 5.0f; edgeLength = edgeLength+0.3f){
	hpreal edgeLength = 1.0f;
	hpvec3 normal = glm::normalize(m_normal);
	hpvec3 a = hpvec3(1.f, 0.f, 0.f);
	if( a == normal ) {
		a = hpvec3(0.f, 0.f, 1.f);
	}
	a -= glm::dot(a,normal)*normal;
	a = 0.5f*edgeLength*glm::normalize(a);
	hpvec3 b = 0.5f*edgeLength*glm::normalize(glm::cross(a,normal));


	verticesAndNormals->push_back(m_origin + a + b);
	verticesAndNormals->push_back(m_origin - a + b);
	verticesAndNormals->push_back(m_origin - a - b);
	verticesAndNormals->push_back(m_origin + a - b);

//	}

	return new PointCloud(verticesAndNormals);
}

LineMesh* Plane::toLineMesh() {
	hpreal edgeLength = 1.0f;
	std::vector<hpvec3>* verticesAndNormals = new std::vector<hpvec3>;
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

	verticesAndNormals->push_back((m_origin + a + b)*2.0f);
	verticesAndNormals->push_back(m_normal);
	verticesAndNormals->push_back((m_origin - a + b)*2.0f);
	verticesAndNormals->push_back(m_normal);
	verticesAndNormals->push_back((m_origin - a - b)*2.0f);
	verticesAndNormals->push_back(m_normal);
	verticesAndNormals->push_back((m_origin + a - b)*2.0f);
	verticesAndNormals->push_back(m_normal);

	indices->push_back(0);
	indices->push_back(2);
	indices->push_back(1);
	indices->push_back(0);
	indices->push_back(2);
	indices->push_back(3);
	return new LineMesh(verticesAndNormals, indices);
}
Plane& Plane::operator=(const Plane& other) {
	if(this != &other) {
		m_normal = other.m_normal;
		m_origin = other.m_origin;
	}
	return *this;
}



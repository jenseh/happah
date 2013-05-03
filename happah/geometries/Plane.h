#ifndef PLANE_H
#define PLANE_H

#include <memory>
#include <list>

using namespace std;

#include "happah/geometries/Geometry.h"
#include "happah/geometries/PointCloud.h"
#include "happah/geometries/LineMesh.h"
#include "happah/geometries/TriangleMesh.h"
#include "happah/HappahTypes.h"
#include "happah/math/Ray.h"

class Plane : public Geometry {

public:
	Plane(hpvec3 origin, hpvec3 normal);
	Plane(const Plane& other);
	~Plane();

	hpvec3 getNormal() const;
	hpvec3 getOrigin() const;
	hpvec3 getSystemXVector();
	bool intersect( Ray& ray, hpvec3& intersectionPoint );
	bool intersect( Ray& ray, hpvec2& intersectionPoint );
	void setNormal(hpvec3 normal);
	void setOrigin(hpvec3 origin);
	void setSystemXVector(hpvec3 systemXVector);

	Plane& operator=(const Plane& other);

	TriangleMesh* toTriangleMesh();
	LineMesh* toLineMesh();
	PointCloud* toPointCloud();

private:
	hpvec3 m_normal;
	hpvec3 m_origin;
	hpvec3 m_localSystemXVector;

	static hpvec3& check(hpvec3& normal);
};	

typedef shared_ptr<Plane> Plane_ptr;

#endif // PLANE_H

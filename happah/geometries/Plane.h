#ifndef PLANE_H
#define PLANE_H

#include <memory>
#include <list>

using namespace std;

#include "happah/geometries/Geometry.h"
#include "happah/geometries/Mesh.h"
#include "happah/geometries/PointCloud.h"
#include "happah/HappahTypes.h"
#include "happah/math/Ray.h"

class PlaneListener {
	virtual ~PlaneListener() {};

	virtual void normalChanged() = 0;
	virtual void originChanged() = 0;
};

class Plane : public Geometry {
public:
	class Listener {
		public:
		virtual void normalChanged() = 0;
		virtual void originChanged() = 0;
	};

public:
	Plane(hpvec3 origin, hpvec3 normal);
	Plane(const Plane& other);
	~Plane();

	hpvec3 getNormal() const;
	hpvec3 getOrigin() const;
	bool intersect( Ray& ray, hpvec3& intersectionPoint );
	void setNormal(hpvec3 normal);
	void setOrigin(hpvec3 origin);

	Plane& operator=(const Plane& other);

	void registerListener(Listener* listener);
	void unregisterListener(Listener* listener);

	TriangleMesh* toTriangleMesh();
	LineMesh* toLineMesh();
	PointCloud* toPointCloud();

private:
	std::list<Listener*> m_listeners;

	hpvec3 m_normal;
	hpvec3 m_origin;

	static hpvec3& check(hpvec3& normal);
};	

typedef shared_ptr<Plane> Plane_ptr;

#endif // PLANE_H

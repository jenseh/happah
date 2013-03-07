#ifndef PLANE_H
#define PLANE_H

#include <memory>

using namespace std;

#include "happah/HappahTypes.h"

class Plane {
public:
	Plane(hpvec3 origin, hpvec3 normal);
	Plane(const Plane& other);
	~Plane();

	hpvec3 getNormal() const;
	hpvec3 getOrigin() const;
	void setNormal(hpvec3 normal);
	void setOrigin(hpvec3 origin);

	Plane& operator=(const Plane& other);

private:
	hpvec3 m_normal;
	hpvec3 m_origin;

	static hpvec3& check(hpvec3& normal);
};	

typedef shared_ptr<Plane> Plane_ptr;

#endif // PLANE_H

#ifndef PLANE_H
#define PLANE_H

#include <memory>

#include "happah/HappahTypes.h"

class Plane {
public:
	Plane( hpvec3 normal, hpvec3 basePoint );
	Plane( const Plane& other );
	~Plane();
	Plane& operator=( const Plane& other );

	hpvec3 getNormal();
	hpvec3 getBasePoint();
//	hpvec2 getExtent();

	bool setNormal( hpvec3 normal );
	bool setBasePoint( hpvec3 basePoint );
//	bool setExtent( hpvec2 extent );
private:
	hpvec3 m_normal;
	hpvec3 m_basePoint;
//	hpvec2 m_extent;
};	

typedef std::shared_ptr<Plane> Plane_ptr;

#endif // PLANE_H

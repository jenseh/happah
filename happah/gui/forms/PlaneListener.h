#ifndef PLANE_LISTENER_H
#define PLANE_LISTENER_H

#include "happah/geometries/Plane.h"

class PlaneListener {

public:
	virtual void insert(Plane_ptr plane) = 0;
	virtual void update(Plane_ptr plane) = 0;

};


#endif // PLANE_LISTENER_H

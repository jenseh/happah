#ifndef SIMPLE_GEAR_LISTENER_H
#define SIMPLE_GEAR_LISTENER_H

#include "happah/geometries/SimpleGear.h"

class SimpleGearListener {

public:
	virtual void insert(SimpleGear_ptr simpleGear) = 0;
	virtual void update(SimpleGear_ptr simpleGear) = 0;

};


#endif // SIMPLE_GEAR_LISTENER_H

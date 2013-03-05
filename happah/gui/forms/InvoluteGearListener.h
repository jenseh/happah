#ifndef INVOLUTE_GEAR_LISTENER_H
#define INVOLUTE_GEAR_LISTENER_H

#include "happah/geometries/InvoluteGear.h"

class InvoluteGearListener {

public:
	virtual void insert(InvoluteGear_ptr involuteGear) = 0;
	virtual void update(InvoluteGear_ptr involuteGear) = 0;

};


#endif // INVOLUTE_GEAR_LISTENER_H

#ifndef DISCLISTENER_H_
#define DISCLISTENER_H_

#include "happah/geometries/Disc.h"

class DiscListener  {

public:
	virtual void insert(Disc_ptr simpleGear) = 0;
	virtual void update(Disc_ptr simpleGear) = 0;

};


#endif

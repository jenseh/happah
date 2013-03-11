/*
 * DiscListener.h
 *
 *  Created on: 11.03.2013
 *      Author: jlabeit
 */

#ifndef DISCLISTENER_H_
#define DISCLISTENER_H_

#include "happah/geometries/Disc.h"

class DiscListener  {

public:
	virtual void insert(Disc_ptr simpleGear) = 0;
	virtual void update(Disc_ptr simpleGear) = 0;

};


#endif /* DISCLISTENER_H_ */

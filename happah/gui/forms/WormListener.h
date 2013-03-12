#ifndef WORMLISTENER_H_
#define WORMLISTENER_H_

#include "happah/geometries/Worm.h"

class WormListener {

public:
	virtual void insert(Worm_ptr worm) = 0;
	virtual void update(Worm_ptr worm) = 0;

};


#endif /* WORMLISTENER_H_ */

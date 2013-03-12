#ifndef VIEWPORT3DLISTENER_H_
#define VIEWPORT3DLISTENER_H_

#include "happah/math/Ray.h"

class Viewport3DListener {

public:
	virtual void handleMouseClickEvent(Ray ray) = 0;
};

#endif

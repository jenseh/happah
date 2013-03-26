#ifndef VIEWPORTLISTENER_H_
#define VIEWPORTLISTENER_H_

#include "happah/math/Ray.h"

class ViewportListener {

public:
	virtual void handleMouseClickEvent(Ray& ray) = 0;
};

#endif

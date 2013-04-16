#ifndef VIEWPORTLISTENER_H_
#define VIEWPORTLISTENER_H_

#include "happah/math/Ray.h"

class ViewportListener {

public:
	virtual void handleMouseClickEvent(Ray& ray) = 0;
	virtual void handleMouseMoveEvent(Ray& ray) = 0;
	virtual void handleMouseMoveStopEvent() = 0;
	virtual void handleDragEvent(float dx,float dy) = 0;
};

#endif

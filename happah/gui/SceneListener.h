#ifndef SCENELISTENER_H
#define SCENELISTENER_H

#include "happah/scene/SceneManager.h"

class SceneListener {

public:
	virtual void sceneChanged() = 0;
};
#endif //SCENELISTENER_H

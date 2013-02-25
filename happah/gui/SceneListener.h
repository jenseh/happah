#ifndef SCENELISTENER_H
#define SCENELISTENER_H
#include "../core/SceneManager.h"

class SceneListener {

public:
	virtual void sceneChanged() = 0;
};
#endif //SCENELISTENER_H
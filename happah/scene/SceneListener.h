#ifndef SCENELISTENER_H
#define SCENELISTENER_H

#include "happah/scene/Node.h"

class SceneListener {

public:
	virtual void handleSubtreeInsertedEvent(Node_ptr root) = 0;
	virtual void handleSubtreesInsertedEvent(vector<Node_ptr>& roots) = 0;
	virtual void handleSubtreeRemovedEvent(Node_ptr root) = 0;
	virtual void handleSubtreesRemovedEvent(vector<Node_ptr>& roots) = 0;
	virtual void handleSubtreeUpdatedEvent(Node_ptr root) = 0;
	virtual void handleSubtreesUpdatedEvent(vector<Node_ptr>& roots) = 0;

};

#endif //SCENELISTENER_H

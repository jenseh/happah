#ifndef SCENE_GRAPH_EXPLORER_LISTENER_H
#define SCENE_GRAPH_EXPLORER_LISTENER_H

#include "happah/scene/GUIStateNode.h"

class SceneGraphExplorerListener {

public:
	virtual void handleGUIStateNodesDeletedEvent(vector<GUIStateNode_ptr>& guiStateNodes) = 0;
	virtual void handleGUIStateNodeSelectedEvent(GUIStateNode_ptr guiStateNode) = 0;

};

#endif //SCENE_GRAPH_EXPLORER_LISTENER_H
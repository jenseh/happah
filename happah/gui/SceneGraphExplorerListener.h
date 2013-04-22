#ifndef SCENE_GRAPH_EXPLORER_LISTENER_H
#define SCENE_GRAPH_EXPLORER_LISTENER_H

#include "happah/scene/GUIStateNode.h"

class SceneGraphExplorerListener {

public:


	virtual void createDiscGearGrind(SurfaceOfRevolution_ptr, SimpleGear_ptr)= 0;
	virtual void createWormGearGrind(Worm_ptr worm, InvoluteGear_ptr gear) = 0;
	virtual void handleGUIStateNodesDeletedEvent(vector<GUIStateNode_ptr>& guiStateNodes) = 0;
	virtual void handleGUIStateNodeSelectedEvent(GUIStateNode_ptr guiStateNode) = 0;

};

#endif //SCENE_GRAPH_EXPLORER_LISTENER_H

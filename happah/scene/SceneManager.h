#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <list>
#include <vector>

using namespace std;

class SceneManager;

#include "happah/geometries/InvoluteGear.h"
#include "happah/geometries/Plane.h"
#include "happah/geometries/SimpleGear.h"
#include "happah/scene/GUIStateNode.h"
#include "happah/scene/Node.h"
#include "happah/scene/SceneListener.h"

class SceneManager : public Node {
public:
	SceneManager();
	~SceneManager();

	void insert(InvoluteGear_ptr involuteGear, InvoluteGearGUIStateNode_ptr involuteGearGUIStateNode);
	void insert(InvoluteGear_ptr involuteGear, TriangleMesh_ptr triangleMesh, hpcolor& color);
	void insert(Plane_ptr plane, PlaneGUIStateNode_ptr planeGUIStateNode);
	void insert(Plane_ptr plane, TriangleMesh_ptr triangleMesh, hpcolor& color);
	void insert(SimpleGear_ptr simpleGear, SimpleGearGUIStateNode_ptr simpleGearGUIStateNode);
	void insert(SimpleGear_ptr simpleGear, TriangleMesh_ptr triangleMesh, hpcolor& color);
	void registerSceneListener(SceneListener* sceneListener);
	Node_ptr remove(Node_ptr node);
	void remove(vector<Node_ptr>& nodes);
	void remove(vector<Node_ptr>& nodes, vector<Node_ptr>& removedNodes);
	Node_ptr removeChildContaining(shared_ptr<void> data);
	Node_ptr removeContaining(shared_ptr<void> parentData, shared_ptr<void> childData);
	void unregisterSceneListener(SceneListener* sceneListener);

private:
	list<SceneListener*> m_listeners;

	template<class G, class N, class S> 
	void doInsert(shared_ptr<G> data, shared_ptr<S> guiStateNode);
	template<class G, class N> 
	void doInsert(shared_ptr<G> geometry, TriangleMesh_ptr triangleMesh, hpcolor& color);

	void triggerSubtreeInsertedEvent(Node_ptr root);
	void triggerSubtreesInsertedEvent(vector<Node_ptr>& roots);
	void triggerSubtreeRemovedEvent(Node_ptr root);
	void triggerSubtreesRemovedEvent(vector<Node_ptr>& roots);
	void triggerSubtreeUpdatedEvent(Node_ptr root);
	void triggerSubtreesUpdatedEvent(vector<Node_ptr>& roots);

};
typedef shared_ptr<SceneManager> SceneManager_ptr;

#endif // SCENEMANAGER_H

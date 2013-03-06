#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <list>
#include <vector>

using namespace std;

class SceneManager;

#include "happah/geometries/InvoluteGear.h"
#include "happah/scene/GUIStateNode.h"
#include "happah/scene/Node.h"
#include "happah/scene/SceneListener.h"

class SceneManager : public Node {
public:
	SceneManager();
	~SceneManager();

	void insert(InvoluteGear_ptr involuteGear, InvoluteGearGUIStateNode_ptr involuteGearGUIStateNode);
	void insert(InvoluteGear_ptr involuteGear, TriangleMesh_ptr triangleMesh, hpcolor& color);
	void registerListener(SceneListener* sceneListener);
	bool remove(Node_ptr node);
	bool remove(vector<Node_ptr>& nodes);
	bool removeChildContaining(shared_ptr<void> data);
	bool removeContaining(shared_ptr<void> parentData, shared_ptr<void> childData);

private:
	list<SceneListener*> m_listeners;

	void notifyListeners();

};
typedef shared_ptr<SceneManager> SceneManager_ptr;

#endif // SCENEMANAGER_H

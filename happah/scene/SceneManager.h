#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <list>
#include <vector>

using namespace std;

#include "happah/geometries/InvoluteSpurGear.h"
#include "happah/scene/Node.h"
#include "happah/scene/InvoluteGearNode.h"
#include "happah/scene/SceneListener.h"
#include "happah/scene/TriangleMeshNode.h"
#include "happah/scene/TriangleMeshRenderStateNode.h"

class SceneManager : public Node {

public:
	SceneManager();
	~SceneManager();

	void add(InvoluteGear_ptr involuteGear, TriangleMesh_ptr triangleMesh, hpcolor& color);
	void remove(InvoluteGear_ptr involuteGear, TriangleMesh_ptr triangleMesh);

	void registerListener(SceneListener* sceneListener);

private:
	list<SceneListener*> m_listeners;
	void notifyListeners();
};

#endif // SCENEMANAGER_H

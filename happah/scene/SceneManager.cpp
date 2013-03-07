#include <ctime>
#include <iostream>

#include "happah/scene/InvoluteGearNode.h"
#include "happah/scene/PlaneNode.h"
#include "happah/scene/SceneManager.h"
#include "happah/scene/TriangleMeshNode.h"
#include "happah/scene/RenderStateNode.h"
#include "happah/scene/SimpleGearNode.h"

SceneManager::SceneManager() {}

SceneManager::~SceneManager() {}

template<class G, class N, class S>
void SceneManager::doInsert(shared_ptr<G> data, shared_ptr<S> guiStateNode) {
	Node_ptr node = findChildContaining(data);

	shared_ptr<N> dataNode;
	if(node) {
		dataNode = dynamic_pointer_cast<N>(node);
		if(dataNode->hasChild(guiStateNode)) return;
	} else {
		dataNode = shared_ptr<N>(new N(data));
		insertChild(dataNode);
	}

	dataNode->insertChild(guiStateNode);

	notifyListeners();
}

template<class G, class N>
void SceneManager::doInsert(shared_ptr<G> geometry, TriangleMesh_ptr triangleMesh, hpcolor& color) {
	Node_ptr node = findChildContaining(geometry);

	shared_ptr<N> geometryNode;
	if(node) {
		geometryNode = static_pointer_cast<N>(node);
		node = node->findChildContaining(triangleMesh);
		if(node) {
			TriangleMeshNode_ptr triangleMeshNode = dynamic_pointer_cast<TriangleMeshNode>(node);
			TriangleMeshRenderStateNode_ptr triangleMeshRenderStateNode = triangleMeshNode->getTriangleMeshRenderStateNode();
			triangleMeshRenderStateNode->setColor(color);
			return;
		}
	} else {
		geometryNode = shared_ptr<N>(new N(geometry));
		insertChild(geometryNode);
	}

	TriangleMeshNode_ptr triangleMeshNode(new TriangleMeshNode(triangleMesh));
	geometryNode->insertChild(triangleMeshNode);

	TriangleMeshRenderStateNode_ptr triangleMeshRenderStateNode(new TriangleMeshRenderStateNode(triangleMesh, color));
	triangleMeshNode->insertChild(triangleMeshRenderStateNode);

	notifyListeners();
}

void SceneManager::insert(InvoluteGear_ptr involuteGear, InvoluteGearGUIStateNode_ptr involuteGearGUIStateNode) {
	doInsert<InvoluteGear, InvoluteGearNode, InvoluteGearGUIStateNode>(involuteGear, involuteGearGUIStateNode);
}

void SceneManager::insert(InvoluteGear_ptr involuteGear, TriangleMesh_ptr triangleMesh, hpcolor& color) {
	doInsert<InvoluteGear, InvoluteGearNode>(involuteGear, triangleMesh, color);
}

void SceneManager::insert(Plane_ptr plane, PlaneGUIStateNode_ptr planeGUIStateNode) {
	doInsert<Plane, PlaneNode, PlaneGUIStateNode>(plane, planeGUIStateNode);
}

void SceneManager::insert(Plane_ptr plane, TriangleMesh_ptr triangleMesh, hpcolor& color) {
	doInsert<Plane, PlaneNode>(plane, triangleMesh, color);
}

void SceneManager::insert(SimpleGear_ptr simpleGear, SimpleGearGUIStateNode_ptr simpleGearGUIStateNode) {
	doInsert<SimpleGear, SimpleGearNode, SimpleGearGUIStateNode>(simpleGear, simpleGearGUIStateNode);
}

void SceneManager::insert(SimpleGear_ptr simpleGear, TriangleMesh_ptr triangleMesh, hpcolor& color) {
	doInsert<SimpleGear, SimpleGearNode>(simpleGear, triangleMesh, color);
}

void SceneManager::notifyListeners() {
	for(std::list<SceneListener*>::iterator it = m_listeners.begin(), end = m_listeners.end(); it != end; ++it)
		(*it)->sceneChanged();
}

void SceneManager::registerListener(SceneListener* sceneListener) {
	m_listeners.push_back(sceneListener);
}

bool SceneManager::remove(Node_ptr node) {
	bool removed = Node::remove(node);
	if(removed)
		notifyListeners();
	return removed;
}

bool SceneManager::remove(vector<Node_ptr>& nodes) {
	bool removed = Node::remove(nodes);
	if(removed)
		notifyListeners();
	return removed;
}

bool SceneManager::removeChildContaining(shared_ptr<void> data) {
	bool removed = Node::removeChildContaining(data);
	if(removed)
		notifyListeners();
	return removed;
}

bool SceneManager::removeContaining(shared_ptr<void> parentData, shared_ptr<void> childData) {
	bool removed = Node::removeContaining(parentData, childData);
	if(removed)
		notifyListeners();
	return removed;
}

void SceneManager::unregisterListener(SceneListener* sceneListener) {
	m_listeners.remove(sceneListener);
}


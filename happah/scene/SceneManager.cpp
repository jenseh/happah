#include <ctime>
#include <iostream>

#include "happah/scene/InvoluteGearNode.h"
#include "happah/scene/SceneManager.h"
#include "happah/scene/TriangleMeshNode.h"
#include "happah/scene/RenderStateNode.h"

SceneManager::SceneManager() {}

SceneManager::~SceneManager() {}

void SceneManager::insert(InvoluteGear_ptr involuteGear, InvoluteGearGUIStateNode_ptr involuteGearGUIStateNode) {
	Node_ptr node = findChildContaining(involuteGear);

	InvoluteGearNode_ptr involuteGearNode;
	if(node) {
		involuteGearNode = dynamic_pointer_cast<InvoluteGearNode>(node);
		if(involuteGearNode->hasChild(involuteGearGUIStateNode)) return;
	} else {
		involuteGearNode = InvoluteGearNode_ptr(new InvoluteGearNode(involuteGear));
		insertChild(involuteGearNode);
	}

	involuteGearNode->insertChild(involuteGearGUIStateNode);

	notifyListeners();
}

void SceneManager::insert(InvoluteGear_ptr involuteGear, TriangleMesh_ptr triangleMesh, hpcolor& color) {
	Node_ptr node = findChildContaining(involuteGear);

	InvoluteGearNode_ptr involuteGearNode;
	if(node) {
		involuteGearNode = dynamic_pointer_cast<InvoluteGearNode>(node);
		InvoluteGear_ptr foundInvoluteGear = dynamic_pointer_cast<InvoluteGear>(involuteGearNode->getGeometry());
		node = involuteGearNode->findChildContaining(triangleMesh);
		if(node) {
			TriangleMeshNode_ptr triangleMeshNode = dynamic_pointer_cast<TriangleMeshNode>(node);
			TriangleMeshRenderStateNode_ptr triangleMeshRenderStateNode = triangleMeshNode->getTriangleMeshRenderStateNode();
			triangleMeshRenderStateNode->setColor(color);
			return;
		}
	} else {
		involuteGearNode = InvoluteGearNode_ptr(new InvoluteGearNode(involuteGear));
		insertChild(involuteGearNode);
	}

	TriangleMeshNode_ptr triangleMeshNode(new TriangleMeshNode(triangleMesh));
	involuteGearNode->insertChild(triangleMeshNode);

	TriangleMeshRenderStateNode_ptr triangleMeshRenderStateNode(new TriangleMeshRenderStateNode(triangleMesh, color));
	triangleMeshNode->insertChild(triangleMeshRenderStateNode);

	notifyListeners();
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

void SceneManager::notifyListeners() {
	for(std::list<SceneListener*>::iterator it = m_listeners.begin(), end = m_listeners.end(); it != end; ++it)
		(*it)->sceneChanged();
}

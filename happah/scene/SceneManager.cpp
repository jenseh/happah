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
		addChild(involuteGearNode);
	}

	involuteGearNode->addChild(involuteGearGUIStateNode);

	notifyListeners();
}

void SceneManager::insert(InvoluteGear_ptr involuteGear, TriangleMesh_ptr triangleMesh, hpcolor& color) {
	Node_ptr node = findChildContaining(involuteGear);

	InvoluteGearNode_ptr involuteGearNode;
	if(node) {
		involuteGearNode = dynamic_pointer_cast<InvoluteGearNode>(node);
		node = involuteGearNode->findChildContaining(triangleMesh);
		if(node) {
			TriangleMeshNode_ptr triangleMeshNode = dynamic_pointer_cast<TriangleMeshNode>(node);
			TriangleMeshRenderStateNode_ptr triangleMeshRenderStateNode = triangleMeshNode->getTriangleMeshRenderStateNode();
			triangleMeshRenderStateNode->setColor(color);
			return;
		}
	} else {
		involuteGearNode = InvoluteGearNode_ptr(new InvoluteGearNode(involuteGear));
		addChild(involuteGearNode);
	}

	TriangleMeshNode_ptr triangleMeshNode(new TriangleMeshNode(triangleMesh));
	involuteGearNode->addChild(triangleMeshNode);

	TriangleMeshRenderStateNode_ptr triangleMeshRenderStateNode(new TriangleMeshRenderStateNode(triangleMesh, color));
	triangleMeshNode->addChild(triangleMeshRenderStateNode);

	notifyListeners();
}

void SceneManager::remove(InvoluteGear_ptr involuteGear, TriangleMesh_ptr triangleMesh) {
	Node_ptr node = findChildContaining(involuteGear);

	if(node) {
		InvoluteGearNode_ptr involuteGearNode = dynamic_pointer_cast<InvoluteGearNode>(node);
		involuteGearNode->removeChildContaining(triangleMesh);
		notifyListeners();
	}

}

void SceneManager::registerListener(SceneListener* sceneListener) {
	m_listeners.push_back(sceneListener);
}

void SceneManager::notifyListeners() {
	for(std::list<SceneListener*>::iterator it = m_listeners.begin(), end = m_listeners.end(); it != end; ++it)
		(*it)->sceneChanged();
}

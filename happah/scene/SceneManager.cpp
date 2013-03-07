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

	Node_ptr root = guiStateNode;
	shared_ptr<N> dataNode;
	if(node) {
		dataNode = static_pointer_cast<N>(node);
		if(dataNode->hasChild(guiStateNode)) {
			triggerSubtreeUpdatedEvent(guiStateNode);
			return;
		}
	} else {
		dataNode = shared_ptr<N>(new N(data));
		insertChild(dataNode);
		root = dataNode;
	}

	dataNode->insertChild(guiStateNode);

	triggerSubtreeInsertedEvent(root);
}

template<class G, class N>
void SceneManager::doInsert(shared_ptr<G> geometry, TriangleMesh_ptr triangleMesh, hpcolor& color) {
	Node_ptr node = findChildContaining(geometry);

	Node_ptr root;
	shared_ptr<N> geometryNode;
	if(node) {
		geometryNode = static_pointer_cast<N>(node);
		node = node->findChildContaining(triangleMesh);
		if(node) {
			TriangleMeshNode_ptr triangleMeshNode = dynamic_pointer_cast<TriangleMeshNode>(node);
			TriangleMeshRenderStateNode_ptr triangleMeshRenderStateNode = triangleMeshNode->getTriangleMeshRenderStateNode();
			triangleMeshRenderStateNode->setColor(color);
			triggerSubtreeUpdatedEvent(triangleMeshRenderStateNode);
			return;
		}
	} else {
		geometryNode = shared_ptr<N>(new N(geometry));
		insertChild(geometryNode);
		root = geometryNode;
	}

	TriangleMeshNode_ptr triangleMeshNode(new TriangleMeshNode(triangleMesh));
	geometryNode->insertChild(triangleMeshNode);

	if(!root) root = triangleMeshNode;

	TriangleMeshRenderStateNode_ptr triangleMeshRenderStateNode(new TriangleMeshRenderStateNode(triangleMesh, color));
	triangleMeshNode->insertChild(triangleMeshRenderStateNode);

	triggerSubtreeInsertedEvent(root);
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

void SceneManager::registerSceneListener(SceneListener* sceneListener) {
	m_listeners.push_back(sceneListener);
}

Node_ptr SceneManager::remove(Node_ptr node) {
	Node_ptr removed = Node::remove(node);
	if(removed) triggerSubtreeRemovedEvent(removed);
	return removed;
}

void SceneManager::remove(vector<Node_ptr>& nodes) {
	vector<Node_ptr> removedNodes;
	removedNodes.reserve(nodes.size());
	Node::remove(nodes, removedNodes);
	if(removedNodes.size() > 0) triggerSubtreesRemovedEvent(removedNodes);
}

void SceneManager::remove(vector<Node_ptr>& nodes, vector<Node_ptr>& removedNodes) {
	Node::remove(nodes, removedNodes);
	if(removedNodes.size() > 0) triggerSubtreesRemovedEvent(removedNodes);
}

Node_ptr SceneManager::removeChildContaining(shared_ptr<void> data) {
	Node_ptr node = Node::removeChildContaining(data);
	if(node) triggerSubtreeRemovedEvent(node);
	return node;
}

Node_ptr SceneManager::removeContaining(shared_ptr<void> parentData, shared_ptr<void> childData) {
	Node_ptr node = Node::removeContaining(parentData, childData);
	if(node) triggerSubtreeRemovedEvent(node);
	return node;
}

void SceneManager::triggerSubtreeInsertedEvent(Node_ptr root) {
	for(list<SceneListener*>::iterator i = m_listeners.begin(), end = m_listeners.end(); i != end; ++i)
		(*i)->handleSubtreeInsertedEvent(root);
}

void SceneManager::triggerSubtreesInsertedEvent(vector<Node_ptr>& roots) {
	for(list<SceneListener*>::iterator i = m_listeners.begin(), end = m_listeners.end(); i != end; ++i)
		(*i)->handleSubtreesInsertedEvent(roots);
}

void SceneManager::triggerSubtreeRemovedEvent(Node_ptr root) {
	for(list<SceneListener*>::iterator i = m_listeners.begin(), end = m_listeners.end(); i != end; ++i)
		(*i)->handleSubtreeRemovedEvent(root);
}

void SceneManager::triggerSubtreesRemovedEvent(vector<Node_ptr>& roots) {
	for(list<SceneListener*>::iterator i = m_listeners.begin(), end = m_listeners.end(); i != end; ++i)
		(*i)->handleSubtreesRemovedEvent(roots);
}

void SceneManager::triggerSubtreeUpdatedEvent(Node_ptr root) {
	for(list<SceneListener*>::iterator i = m_listeners.begin(), end = m_listeners.end(); i != end; ++i)
		(*i)->handleSubtreeUpdatedEvent(root);
}

void SceneManager::triggerSubtreesUpdatedEvent(vector<Node_ptr>& roots) {
	for(list<SceneListener*>::iterator i = m_listeners.begin(), end = m_listeners.end(); i != end; ++i)
		(*i)->handleSubtreesUpdatedEvent(roots);
}

void SceneManager::unregisterSceneListener(SceneListener* sceneListener) {
	m_listeners.remove(sceneListener);
}


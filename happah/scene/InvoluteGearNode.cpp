#include "happah/scene/InvoluteGearNode.h"

InvoluteGearNode::InvoluteGearNode(InvoluteGear_ptr involuteGear)
	: SimpleGeometryNode<InvoluteGear>(involuteGear) {}

InvoluteGearNode::~InvoluteGearNode() {}

void InvoluteGearNode::accept(SceneVisitor& sceneVisitor) {
	sceneVisitor.visit(*this);
	Node::accept(sceneVisitor);
}

void InvoluteGearNode::insertChild(InvoluteGearGUIStateNode_ptr involuteGearGUIStateNode) {
	Node::insertChild(involuteGearGUIStateNode);
}

void InvoluteGearNode::insertChild(TriangleMeshNode_ptr triangleMeshNode) {
	Node::insertChild(triangleMeshNode);
}

bool InvoluteGearNode::hasChild(InvoluteGearGUIStateNode_ptr involuteGearGUIStateNode) {
	return Node::hasChild(involuteGearGUIStateNode);
}

void InvoluteGearNode::removeChild(InvoluteGearGUIStateNode_ptr involuteGearGUIStateNode) {
	Node::removeChild(involuteGearGUIStateNode);
}

void InvoluteGearNode::removeChildContaining(TriangleMesh_ptr triangleMesh) {
	Node::removeChildContaining(triangleMesh);
}

void InvoluteGearNode::removeChild(TriangleMeshNode_ptr triangleMeshNode) {
	Node::removeChild(triangleMeshNode);
}

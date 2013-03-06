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


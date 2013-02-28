#include "happah/scene/InvoluteGearNode.h"

InvoluteGearNode::InvoluteGearNode(InvoluteGear_ptr involuteGear)
	: SimpleGeometryNode<InvoluteSpurGear>(involuteGear) {}

InvoluteGearNode::~InvoluteGearNode() {}

void InvoluteGearNode::accept(SceneVisitor& sceneVisitor) {
	sceneVisitor.visit(*this);
	Node::accept(sceneVisitor);
}

void InvoluteGearNode::addChild(TriangleMeshNode_ptr triangleMeshNode) {
	Node::addChild(triangleMeshNode);
}

void InvoluteGearNode::removeChild(TriangleMeshNode_ptr triangleMeshNode) {
	Node::removeChild(triangleMeshNode);
}

#include "happah/scene/InvoluteSpurGearNode.h"

InvoluteSpurGearNode::InvoluteSpurGearNode(InvoluteSpurGear_ptr involuteSpurGear)
	: SimpleGeometryNode<InvoluteSpurGear>(involuteSpurGear) {}

InvoluteSpurGearNode::~InvoluteSpurGearNode() {}

void InvoluteSpurGearNode::accept(SceneVisitor& sceneVisitor) {
	sceneVisitor.visit(*this);
	Node::accept(sceneVisitor);
}

void InvoluteSpurGearNode::addChild(TriangleMeshNode_ptr triangleMeshNode) {
	Node::addChild(triangleMeshNode);
}

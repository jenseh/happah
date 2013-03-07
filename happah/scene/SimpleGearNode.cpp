#include "happah/scene/SimpleGearNode.h"

SimpleGearNode::SimpleGearNode(SimpleGear_ptr simpleGear)
	: SimpleGeometryNode<SimpleGear>(simpleGear) {}

SimpleGearNode::~SimpleGearNode() {}

void SimpleGearNode::accept(SceneVisitor& sceneVisitor) {
	sceneVisitor.visit(*this);
	Node::accept(sceneVisitor);
}

void SimpleGearNode::insertChild(SimpleGearGUIStateNode_ptr simpleGearGUIStateNode) {
	Node::insertChild(simpleGearGUIStateNode);
}

void SimpleGearNode::insertChild(TriangleMeshNode_ptr triangleMeshNode) {
	Node::insertChild(triangleMeshNode);
}


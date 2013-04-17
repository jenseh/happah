#include "happah/scene/ToothProfileNode.h"

ToothProfileNode::ToothProfileNode(ToothProfile_ptr toothProfile) : SimpleGeometryNode<ToothProfile>(toothProfile) {
}

ToothProfileNode::~ToothProfileNode() {
}

void ToothProfileNode::accept(SceneVisitor& sceneVisitor) {
	sceneVisitor.visit(*this);
	Node::accept(sceneVisitor);
}

void ToothProfileNode::insertChild(ToothProfileGUIStateNode_ptr toothProfileGUIStateNode) {
	Node::insertChild(toothProfileGUIStateNode);
}

void ToothProfileNode::insertChild(LineMeshNode_ptr lineMeshNode) {
	Node::insertChild(lineMeshNode);
}

void ToothProfileNode::insertChild(PointCloudNode_ptr pointCloudNode) {
	Node::insertChild(pointCloudNode);
}

#include "happah/scene/PlaneNode.h"

PlaneNode::PlaneNode(Plane_ptr plane) : SimpleGeometryNode<Plane>(plane) {}

PlaneNode::~PlaneNode() {}

void PlaneNode::accept(SceneVisitor& sceneVisitor) {
	sceneVisitor.visit(*this);
	Node::accept(sceneVisitor);
}

void PlaneNode::insertChild(PlaneGUIStateNode_ptr planeGUIStateNode) {
	Node::insertChild(planeGUIStateNode);
}

void PlaneNode::insertChild(TriangleMeshNode_ptr triangleMeshNode) {
	Node::insertChild(triangleMeshNode);
}

void PlaneNode::insertChild(PointCloudNode_ptr pointCloudNode) {
	Node::insertChild(pointCloudNode);
}

void PlaneNode::insertChild(LineMeshNode_ptr LineMeshNode) {
	Node::insertChild(LineMeshNode);
}

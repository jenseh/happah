#include "WormNode.h"

WormNode::WormNode(Worm_ptr worm)
	: SimpleGeometryNode<Worm>(worm) {}

WormNode::~WormNode() {}

void WormNode::accept(SceneVisitor& sceneVisitor) {
	sceneVisitor.visit(*this);
	Node::accept(sceneVisitor);
}

void WormNode::insertChild(WormGUIStateNode_ptr wormGUIStateNode) {
	Node::insertChild(wormGUIStateNode);
}

void WormNode::insertChild(TriangleMeshNode_ptr triangleMeshNode) {
	Node::insertChild(triangleMeshNode);
}

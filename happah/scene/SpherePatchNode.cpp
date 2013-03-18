#include "SpherePatchNode.h"

SpherePatchNode::SpherePatchNode(SpherePatch_ptr spherePatch)
	: SimpleGeometryNode<SpherePatch>(spherePatch){}

SpherePatchNode::~SpherePatchNode() {}

void SpherePatchNode::accept(SceneVisitor& sceneVisitor){
	sceneVisitor.visit(*this);
	Node::accept(sceneVisitor);
}


void SpherePatchNode::insertChild(SpherePatchGUIStateNode_ptr SpherePatchGUIStateNode) {
	Node::insertChild(SpherePatchGUIStateNode);
}


void SpherePatchNode::insertChild(TriangleMeshNode_ptr triangleMeshNode) {
	Node::insertChild(triangleMeshNode);
}

/*
void SpherePatchNode::insertChild(PointCloudNode_ptr pointCloudNode) {
	Node::insertChild(pointCloudNode)
}
*/

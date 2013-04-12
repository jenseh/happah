#include "FocalSplineNode.h"

FocalSplineNode::FocalSplineNode(FocalSpline_ptr focalSpline) :SimpleGeometryNode<FocalSpline>(focalSpline) {}


FocalSplineNode::~FocalSplineNode() {
	// TODO Auto-generated destructor stub
}

void FocalSplineNode::accept(SceneVisitor& sceneVisitor) {
	sceneVisitor.visit(*this);
	Node::accept(sceneVisitor);
}

void FocalSplineNode::insertChild(FocalSplineGUIStateNode_ptr focalSplineGUIStateNode){
	Node::insertChild(focalSplineGUIStateNode);
}

void FocalSplineNode::insertChild(PointCloudNode_ptr pointCloudNode){
	Node::insertChild(pointCloudNode);
}

void FocalSplineNode::insertChild(LineMeshNode_ptr lineMeshNode){
	Node::insertChild(lineMeshNode);
}

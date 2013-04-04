#include "happah/scene/BSplineCurveNode.h"

BSplineCurveNode::BSplineCurveNode(BSplineCurve_ptr curve) : SimpleGeometryNode<BSplineCurve>(curve) {}

BSplineCurveNode::~BSplineCurveNode() {}

void BSplineCurveNode::accept(SceneVisitor& sceneVisitor) {
	sceneVisitor.visit(*this);
	Node::accept(sceneVisitor);
}

void BSplineCurveNode::insertChild(BSplineCurveGUIStateNode_ptr curveGUIStateNode) {
	Node::insertChild(curveGUIStateNode);
}

void BSplineCurveNode::insertChild(PointCloudNode_ptr pointCloudNode) {
	Node::insertChild(pointCloudNode);
}

void BSplineCurveNode::insertChild(LineMeshNode_ptr lineMeshNode) {
	Node::insertChild(lineMeshNode);
}

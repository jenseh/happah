#include "happah/scene/BSplineCurveNode.h"

BSplineCurveNode::BSplineCurveNode(BSplineCurve_ptr curve) : SimpleGeometryNode<BSplineCurve>(curve) {}

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

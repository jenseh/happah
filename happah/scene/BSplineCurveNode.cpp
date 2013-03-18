#include "happah/scene/BSplineCurveNode.h"

BSplineCurveNode::BSplineCurveNode(BSplineCurve_ptr curve) : SimpleGeometryNode<BSplineCurve>(curve) {}

void BSplineCurveNode::accept(SceneVisitor& sceneVisitor) {}

// void BSplineCurveNode::insertChild(BSplineCurveGUIStateNode_ptr curveGUIStateNode) {}

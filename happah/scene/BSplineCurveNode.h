#ifndef B_SPLINE_CURVE_NODE_H
#define B_SPLINE_CURVE_NODE_H

#include <memory>
#include <iostream>

#include "happah/geometries/BSplineCurve.h"
#include "happah/scene/GUIStateNode.h"
#include "happah/scene/LineMeshNode.h"
#include "happah/scene/PointCloudNode.h"
#include "happah/scene/SceneVisitor.h"
#include "happah/scene/SimpleGeometryNode.h"

class BSplineCurveNode : public SimpleGeometryNode<BSplineCurve<hpvec2>> {

public:
	BSplineCurveNode(BSplineCurve2D_ptr curve);
	~BSplineCurveNode();

	void accept(SceneVisitor& sceneVisitor);
	void insertChild(BSplineCurveGUIStateNode_ptr curveGUIStateNode);
	void insertChild(PointCloudNode_ptr pointCloudNode);
	void insertChild(LineMeshNode_ptr lineMeshNode);

};

typedef std::shared_ptr<BSplineCurveNode> BSplineCurveNode_ptr;

#endif // B_SPLINE_CURVE_NODE_H

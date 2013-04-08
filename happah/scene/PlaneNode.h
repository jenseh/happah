#ifndef PLANENODE_H
#define PLANENODE_H

#include <memory>

using namespace std;

#include "happah/geometries/Plane.h"
#include "happah/scene/BSplineCurveNode.h"
#include "happah/scene/GUIStateNode.h"
#include "happah/scene/SimpleGeometryNode.h"
#include "happah/scene/TriangleMeshNode.h"
#include "happah/scene/PointCloudNode.h"
#include "happah/scene/SceneVisitor.h"

class LineMeshNode;
typedef shared_ptr<LineMeshNode> LineMeshNode_ptr;

class PlaneNode : public SimpleGeometryNode<Plane> {

public:
	PlaneNode(Plane_ptr plane);
	virtual ~PlaneNode();

	virtual void accept(SceneVisitor& sceneVisitor);
	void insertChild(BSplineCurveNode_ptr curveNode);
	void insertChild(PlaneGUIStateNode_ptr planeGUIStateNode);
	void insertChild(TriangleMeshNode_ptr triangleMeshNode);
	void insertChild(PointCloudNode_ptr pointCloudNode);
	void insertChild(LineMeshNode_ptr lineMeshNode);

};

typedef shared_ptr<PlaneNode> PlaneNode_ptr;

#endif // PLANENODE_H

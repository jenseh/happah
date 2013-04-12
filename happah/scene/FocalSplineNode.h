#ifndef FOCALSPLINENODE_H_
#define FOCALSPLINENODE_H_


#include <memory>

#include "happah/geometries/FocalSpline.h"
#include "happah/scene/GUIStateNode.h"
#include "happah/scene/LineMeshNode.h"
#include "happah/scene/PointCloudNode.h"
#include "happah/scene/SimpleGeometryNode.h"


class FocalSplineNode : public SimpleGeometryNode<FocalSpline> {
public:
	FocalSplineNode(FocalSpline_ptr focalSpline);
	virtual ~FocalSplineNode();

	void accept(SceneVisitor& sceneVisitor);
	void insertChild(FocalSplineGUIStateNode_ptr focalSplineGUIStateNode);
	void insertChild(PointCloudNode_ptr pointCloudNode);
	void insertChild(LineMeshNode_ptr lineMeshNode);
};

typedef std::shared_ptr<FocalSplineNode> FocalSplineNode_ptr;

#endif /* FOCALSPLINENODE_H_ */

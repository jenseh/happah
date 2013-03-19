#ifndef POINT_CLOUD_NODE_H_
#define POINT_CLOUD_NODE_H_

#include "happah/geometries/PointCloud.h"
#include "happah/scene/SimpleGeometryNode.h"
#include "happah/scene/PointCloudRenderStateNode.h"
#include "happah/scene/RenderStateNode.h"


class PointCloudNode : public SimpleGeometryNode<PointCloud>{
public:
	PointCloudNode(PointCloud_ptr PointCloud);
	PointCloudNode(PointCloud_ptr PointCoud,RigidAffineTransformation& rigidAffineTransformation);
	virtual ~PointCloudNode();

	virtual void accept(SceneVisitor& sceneVisitor);
	void insertChild(PointCloudRenderStateNode_ptr pointCloudRenderStateNode);
	PointCloudRenderStateNode_ptr getPointCloudRenderStateNode();

private:
	PointCloudRenderStateNode_ptr m_pointCloudRenderStateNode;
};

typedef shared_ptr<PointCloudNode> PointCloudNode_ptr;

#endif /* POINT_CLOUD_NODE_H_ */

#ifndef POINT_CLOUD_NODE_H_
#define POINT_CLOUD_NODE_H_

#include "happah/geometries/Mesh.h"
#include "happah/scene/SimpleGeometryNode.h"
#include "happah/scene/RenderStateNode.h"

class PointCloudNode : public SimpleGeometryNode<PointCloud>{
public:
	PointCloudNode(PointCloud_ptr PointCloud);
	virtual ~PointCloudNode();

	virtual void accept(SceneVisitor& sceneVisitor);
	void addChild(PointCloudRenderStateNode_ptr pointCloudRenderStateNode);
	PointCloudRenderStateNode_ptr getPointCloudRenderStateNode();

private:
	PointCloudRenderStateNode_ptr m_pointCloudRenderStateNode;
};

#endif /* POINT_CLOUD_NODE_H_ */

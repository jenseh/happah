#include "happah/scene/PointCloudRenderStateNode.h"

PointCloudRenderStateNode::PointCloudRenderStateNode(PointCloud_ptr pointCloud, hpcolor& color)
	: RenderStateNode(pointCloud->getVertices(),color){}

PointCloudRenderStateNode::PointCloudRenderStateNode(PointCloud_ptr pointCloud, std::vector<hpcolor>* colorVector)
	: RenderStateNode(pointCloud->getVertices(),colorVector) {}

PointCloudRenderStateNode::~PointCloudRenderStateNode() {
	// TODO Auto-generated destructor stub
}

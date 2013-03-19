#include "happah/scene/PointCloudNode.h"

PointCloudNode::PointCloudNode(PointCloud_ptr pointCloud)
	: SimpleGeometryNode<PointCloud>(pointCloud) {}

PointCloudNode::PointCloudNode(PointCloud_ptr pointCloud, RigidAffineTransformation& rigidAffineTransformation)
	: SimpleGeometryNode<PointCloud>(pointCloud, rigidAffineTransformation){}

PointCloudNode::~PointCloudNode() {}

void PointCloudNode::accept(SceneVisitor& sceneVisitor) {
	sceneVisitor.visit(*this);
	Node::accept(sceneVisitor);
}

void PointCloudNode::insertChild(PointCloudRenderStateNode_ptr pointCloudRenderStateNode) {
	if(m_pointCloudRenderStateNode)
		Node::removeChild(m_pointCloudRenderStateNode);
	Node::insertChild(pointCloudRenderStateNode);
	m_pointCloudRenderStateNode = pointCloudRenderStateNode;
}

PointCloudRenderStateNode_ptr PointCloudNode::getPointCloudRenderStateNode() {
	return m_pointCloudRenderStateNode;
}

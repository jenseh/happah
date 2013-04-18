#include "happah/scene/ZCircleCloudNode.h"

ZCircleCloudNode::ZCircleCloudNode(ZCircleCloud_ptr zCircleCloud)
	: SimpleGeometryNode<ZCircleCloud>(zCircleCloud) {}

ZCircleCloudNode::ZCircleCloudNode(ZCircleCloud_ptr zCircleCloud, RigidAffineTransformation& transformation):
		SimpleGeometryNode<ZCircleCloud>(zCircleCloud, transformation) { }

ZCircleCloudNode::~ZCircleCloudNode() {}

void ZCircleCloudNode::accept(SceneVisitor& sceneVisitor) {
	sceneVisitor.visit(*this);
	Node::accept(sceneVisitor);
}

void ZCircleCloudNode::insertChild(ZCircleCloudRenderStateNode_ptr zCircleCloudRenderStateNode) {
	if(m_zCircleCloudRenderStateNode)
		Node::removeChild(m_zCircleCloudRenderStateNode);
	Node::insertChild(zCircleCloudRenderStateNode);
	m_zCircleCloudRenderStateNode = zCircleCloudRenderStateNode;
}

ZCircleCloudRenderStateNode_ptr ZCircleCloudNode::getZCircleCloudRenderStateNode() {
	return m_zCircleCloudRenderStateNode;
}

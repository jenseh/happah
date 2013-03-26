#include "happah/scene/PointCloudRenderStateNode.h"

PointCloudRenderStateNode::PointCloudRenderStateNode(PointCloud_ptr pointCloud, hpcolor& color)
	: RenderStateNode(pointCloud->getVertices(),color),m_mode(GL_POINTS){}

PointCloudRenderStateNode::PointCloudRenderStateNode(PointCloud_ptr pointCloud, std::vector<hpcolor>* colorVector)
	: RenderStateNode(pointCloud->getVertices(),colorVector),m_mode(GL_POINTS) {}

PointCloudRenderStateNode::~PointCloudRenderStateNode() {
	// TODO Auto-generated destructor stub
}

hpuint PointCloudRenderStateNode::getMode(){
	return m_mode;
}

void PointCloudRenderStateNode::draw(DrawVisitor& drawVisitor, RigidAffineTransformation& rigidAffineTransformation){
	drawVisitor.draw(*this, rigidAffineTransformation);
}

#include "happah/scene/PointCloudRenderStateNode.h"

PointCloudRenderStateNode::PointCloudRenderStateNode(PointCloud_ptr pointCloud, hpcolor& color)
	: RenderStateNode(pointCloud->getVertices(),color),m_mode(GL_POINTS),m_selected(0){}

PointCloudRenderStateNode::PointCloudRenderStateNode(PointCloud_ptr pointCloud, std::vector<hpcolor>* colorVector)
	: RenderStateNode(pointCloud->getVertices(),colorVector),m_mode(GL_POINTS),m_selected(0) {}

PointCloudRenderStateNode::~PointCloudRenderStateNode() {
	// TODO Auto-generated destructor stub
}

hpuint PointCloudRenderStateNode::getMode(){
	return m_mode;
}

void PointCloudRenderStateNode::draw(DrawVisitor& drawVisitor, RigidAffineTransformation& rigidAffineTransformation){
	drawVisitor.draw(getPtr(), rigidAffineTransformation);
}

void PointCloudRenderStateNode::setSelected(int selected){
	m_selected = selected;
}

int PointCloudRenderStateNode::getSelected(){
	return m_selected;
}

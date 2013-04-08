#ifndef POINT_CLOUD_RENDER_STATE_NODE_H_
#define POINT_CLOUD_RENDER_STATE_NODE_H_

#include <GL/glew.h>
#include <memory>
#include <vector>

using namespace std;

#include "happah/HappahTypes.h"
#include "happah/scene/RenderStateNode.h"
#include "happah/scene/PointCloudNode.h"

class PointCloudRenderStateNode : public RenderStateNode {

public:
	PointCloudRenderStateNode(PointCloud_ptr pointCloud,hpcolor& color);
	PointCloudRenderStateNode(PointCloud_ptr pointCloud,std::vector<hpcolor>* colorVector);
	virtual ~PointCloudRenderStateNode();
	virtual void draw(DrawVisitor& drawVisitor,RigidAffineTransformation& rigidAffineTransformation);
	PointCloudRenderStateNode_ptr getPtr(){return dynamic_pointer_cast<PointCloudRenderStateNode>(shared_from_this());}
	hpuint getMode();
	void setSelected(int selected);
	int  getSelected();

private:
	hpuint m_mode;
	int m_selected;

};
#endif /* POINT_CLOUD_RENDER_STATE_NODE_H_ */

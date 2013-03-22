#ifndef POINT_CLOUD_RENDER_STATE_NODE_H_
#define POINT_CLOUD_RENDER_STATE_NODE_H_

#include <GL/glew.h>
#include <memory>
#include <vector>

using namespace std;

class PointCloudRenderStateNode;
typedef shared_ptr<PointCloudRenderStateNode> PointCloudRenderStateNode_ptr;

#include "happah/scene/RenderStateNode.h"
#include "happah/scene/PointCloudNode.h"

class PointCloudRenderStateNode : public RenderStateNode {

public:
	PointCloudRenderStateNode(PointCloud_ptr pointCloud,hpcolor& color);
	PointCloudRenderStateNode(PointCloud_ptr pointCloud,std::vector<hpcolor>* colorVector);
	virtual ~PointCloudRenderStateNode();
	virtual void draw(DrawVisitor& drawVisitor,RigidAffineTransformation& rigidAffineTransformation);

	hpuint getMode();
private:
	hpuint m_mode;

};
#endif /* POINT_CLOUD_RENDER_STATE_NODE_H_ */

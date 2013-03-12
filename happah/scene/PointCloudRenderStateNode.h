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

};
#endif /* POINT_CLOUD_RENDER_STATE_NODE_H_ */

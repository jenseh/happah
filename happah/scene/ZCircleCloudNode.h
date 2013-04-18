#ifndef ZCIRCLECLOUDNODE_H_
#define ZCIRCLECLOUDNODE_H_

#include "happah/geometries/Mesh.h"
#include "happah/scene/SimpleGeometryNode.h"
#include "happah/scene/ElementRenderStateNode.h"

class ZCircleCloudRenderStateNode;
typedef shared_ptr<ZCircleCloudRenderStateNode> ZCircleCloudRenderStateNode_ptr;

class ZCircleCloudNode : public SimpleGeometryNode<ZCircleCloud> {

public:
	ZCircleCloudNode(ZCircleCloud_ptr zCircleCloud);
	ZCircleCloudNode(ZCircleCloud_ptr zCircleCloud, RigidAffineTransformation& transformation);
	virtual ~ZCircleCloudNode();

	virtual void accept(SceneVisitor& sceneVisitor);
	void insertChild(ZCircleCloudRenderStateNode_ptr zCircleCloudRenderStateNode);
	ZCircleCloudRenderStateNode_ptr getZCircleCloudRenderStateNode();

private:
	ZCircleCloudRenderStateNode_ptr m_zCircleCloudRenderStateNode;
};
typedef shared_ptr<ZCircleCloudNode> ZCircleCloudNode_ptr;


#endif /* ZCIRCLECLOUDNODE_H_ */

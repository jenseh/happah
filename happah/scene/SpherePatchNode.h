#ifndef SPHERE_PATCH_NODE_H_
#define SPHERE_PATCH_NODE_H_

#include "happah/geometries/SpherePatch.h"
#include "happah/scene/GUIStateNode.h"
#include "happah/scene/SimpleGeometryNode.h"
#include "happah/scene/TriangleMeshNode.h"
#include "happah/scene/PointCloudNode.h"
class SpherePatchNode : public SimpleGeometryNode<SpherePatch>{

public:
	SpherePatchNode(SpherePatch_ptr spherePatch);
	virtual ~SpherePatchNode();

	virtual void accept(SceneVisitor& sceneVisitor);
	//void insertChild(SpherePatchGUIStateNode_ptr spherePatchGUIStateNode);
	void insertChild(TriangleMeshNode_ptr triangleMeshNode);
	//void insertChild(PointCloudNode_ptr pointCloudNode);
};

typedef shared_ptr<SpherePatchNode> SpherePatchNode_ptr;

#endif /* SPHERE_PATCH_NODE_H_ */

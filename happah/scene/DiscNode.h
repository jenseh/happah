#ifndef DISCNODE_H_
#define DISCNODE_H_

#include "happah/geometries/SurfaceOfRevolution.h"
#include "happah/scene/GUIStateNode.h"
#include "happah/scene/SimpleGeometryNode.h"
#include "happah/scene/TriangleMeshNode.h"

class DiscNode : public SimpleGeometryNode<SurfaceOfRevolution> {

public:
	DiscNode(SurfaceOfRevolution_ptr disc);
	virtual ~DiscNode();

	virtual void accept(SceneVisitor& sceneVisitor);
	void insertChild(DiscGUIStateNode_ptr discGUIStateNode);
	void insertChild(TriangleMeshNode_ptr triangleMeshNode);

};
typedef shared_ptr<DiscNode> DiscNode_ptr;

#endif

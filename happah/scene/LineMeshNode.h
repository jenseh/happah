#ifndef LINE_MESH_NODE_H_
#define LINE_MESH_NODE_H_

#include "happah/geometries/LineMesh.h"
#include "happah/scene/SimpleGeometryNode.h"
#include "happah/scene/ElementRenderStateNode.h"


class LineMeshNode : public SimpleGeometryNode<LineMesh3D>  {

public:
	LineMeshNode(LineMesh3D_ptr lineMesh);
	LineMeshNode(LineMesh3D_ptr lineMesh,RigidAffineTransformation& rigidAffineTransformation);
	virtual ~LineMeshNode();

	virtual void accept(SceneVisitor& sceneVisitor);
	void insertChild(LineMeshRenderStateNode_ptr lineMeshRenderStateNode);
	LineMeshRenderStateNode_ptr getLineMeshRenderStateNode();

private:
	LineMeshRenderStateNode_ptr m_lineMeshRenderStateNode;
};

typedef shared_ptr<LineMeshNode> LineMeshNode_ptr;


#endif /* LINE_MESH_NODE_H_ */

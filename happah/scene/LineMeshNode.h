#ifndef LINE_MESH_NODE_H_
#define LINE_MESH_NODE_H_

#include "happah/geometries/Mesh.h"
#include "happah/scene/SimpleGeometryNode.h"
#include "happah/scene/RenderStateNode.h"


class LineMeshNode : public SimpleGeometryNode<LineMesh>  {

public:
	LineMeshNode(LineMesh_ptr lineMesh);
	virtual ~LineMeshNode();

	virtual void accept(SceneVisitor& sceneVisitor);
	void insertChild(LineMeshRenderStateNode_ptr lineMeshRenderStateNode);
	LineMeshRenderStateNode_ptr getLineMeshRenderStateNode();

private:
	LineMeshRenderStateNode_ptr m_lineMeshRenderStateNode;
};

typedef shared_ptr<TriangleMeshNode> TriangleMeshNode_ptr;


#endif /* LINE_MESH_NODE_H_ */

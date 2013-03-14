#ifndef TRIANGLE_MESH_NODE_H
#define TRIANGLE_MESH_NODE_H

#include "happah/geometries/Mesh.h"
#include "happah/scene/SimpleGeometryNode.h"
#include "happah/scene/ElementRenderStateNode.h"

class TriangleMeshNode : public SimpleGeometryNode<TriangleMesh> {

public:
	TriangleMeshNode(TriangleMesh_ptr triangleMesh);
	TriangleMeshNode(TriangleMesh_ptr triangleMesh, RigidAffineTransformation& transformation);
	virtual ~TriangleMeshNode();

	virtual void accept(SceneVisitor& sceneVisitor);
	void insertChild(TriangleMeshRenderStateNode_ptr triangleMeshRenderStateNode);
	TriangleMeshRenderStateNode_ptr getTriangleMeshRenderStateNode();

private:
	TriangleMeshRenderStateNode_ptr m_triangleMeshRenderStateNode;
};
typedef shared_ptr<TriangleMeshNode> TriangleMeshNode_ptr;


#endif // TRIANGLE_MESH_NODE_H

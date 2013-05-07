#ifndef TRIANGLE_MESH_NODE_H
#define TRIANGLE_MESH_NODE_H

#include "happah/geometries/TriangleMesh.h"
#include "happah/scene/GUIStateNode.h"
#include "happah/scene/SimpleGeometryNode.h"
#include "happah/scene/ElementRenderStateNode.h"

class TriangleMeshRenderStateNode;
typedef shared_ptr<TriangleMeshRenderStateNode> TriangleMeshRenderStateNode_ptr;

class TriangleMeshNode : public SimpleGeometryNode<TriangleMesh3D> {

public:
	TriangleMeshNode(TriangleMesh3D_ptr triangleMesh);
	TriangleMeshNode(TriangleMesh3D_ptr triangleMesh, RigidAffineTransformation& transformation);
	virtual ~TriangleMeshNode();

	virtual void accept(SceneVisitor& sceneVisitor);
	void insertChild(TriangleMeshGUIStateNode_ptr triangleMeshGUIStateNode);
	void insertChild(TriangleMeshRenderStateNode_ptr triangleMeshRenderStateNode);
	TriangleMeshRenderStateNode_ptr getTriangleMeshRenderStateNode();

private:
	TriangleMeshRenderStateNode_ptr m_triangleMeshRenderStateNode;
};
typedef shared_ptr<TriangleMeshNode> TriangleMeshNode_ptr;


#endif // TRIANGLE_MESH_NODE_H

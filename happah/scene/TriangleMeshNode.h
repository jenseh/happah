#ifndef TRIANGLE_MESH_NODE_H
#define TRIANGLE_MESH_NODE_H

#include <memory>

using namespace std;

class TriangleMeshNode;
typedef shared_ptr<TriangleMeshNode> TriangleMeshNode_ptr;

#include "happah/models/TriangleMesh.h"
#include "happah/scene/SceneVisitor.h"
#include "happah/scene/SimpleGeometryNode.h"
#include "happah/scene/TriangleMeshRenderStateNode.h"

class TriangleMeshNode : public SimpleGeometryNode<TriangleMesh> {

public:
	TriangleMeshNode(TriangleMesh_ptr triangleMesh);
	virtual ~TriangleMeshNode();

	virtual void accept(SceneVisitor& sceneVisitor);
	void addChild(TriangleRenderStateMeshNode_ptr triangleMeshRenderStateNode);
};

#endif // TRIANGLE_MESH_NODE_H

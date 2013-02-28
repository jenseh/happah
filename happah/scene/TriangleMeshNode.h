#ifndef TRIANGLE_MESH_NODE_H
#define TRIANGLE_MESH_NODE_H

#include <memory>

using namespace std;

class TriangleMeshNode;
typedef shared_ptr<TriangleMeshNode> TriangleMeshNode_ptr;

#include "happah/models/TriangleMesh.h"
#include "happah/scene/SceneVisitor.h"
#include "happah/scene/SimpleGeometryNode.h"

//TODO: move following typedef to TriangleMesh.h after cleanup
typedef shared_ptr<TriangleMesh> TriangleMesh_ptr;

class TriangleMeshNode : public SimpleGeometryNode<TriangleMesh> {

public:
	TriangleMeshNode(TriangleMesh_ptr triangleMesh);
	virtual ~TriangleMeshNode();

	virtual void accept(SceneVisitor& sceneVisitor);

};

#endif // TRIANGLE_MESH_NODE_H

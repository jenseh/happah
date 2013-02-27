#ifndef TRIANGLE_MESH_NODE_H
#define TRIANGLE_MESH_NODE_H

#include <memory>

#include "happah/models/TriangleMesh.h"
#include "happah/scene/Node.h"
#include "happah/scene/SceneVisitor.h"

using namespace std;

//TODO: move following typedef to TriangleMesh.h after cleanup
typedef shared_ptr<TriangleMesh> TriangleMesh_ptr;

class TriangleMeshNode : public Node {

public:
	TriangleMeshNode(TriangleMesh_ptr triangleMesh);
	virtual ~TriangleMeshNode();

	virtual void accept(SceneVisitor& sceneVisitor);
};
typedef shared_ptr<TriangleMeshNode> TriangleMeshNode_ptr;

#endif // TRIANGLE_MESH_NODE_H

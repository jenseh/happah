#include "happah/scene/TriangleMeshNode.h"

TriangleMeshNode::TriangleMeshNode(TriangleMesh_ptr triangleMesh) 
	: SimpleGeometryNode<TriangleMesh>(triangleMesh) {}

TriangleMeshNode::~TriangleMeshNode() {}

void TriangleMeshNode::accept(SceneVisitor& sceneVisitor) {
	sceneVisitor.visit(*this);
	Node::accept(sceneVisitor);
}

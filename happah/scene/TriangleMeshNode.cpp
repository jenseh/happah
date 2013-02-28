#include "happah/scene/TriangleMeshNode.h"

TriangleMeshNode::TriangleMeshNode(TriangleMesh_ptr triangleMesh) 
	: SimpleGeometryNode<TriangleMesh>(triangleMesh) {}

TriangleMeshNode::~TriangleMeshNode() {}

void TriangleMeshNode::accept(SceneVisitor& sceneVisitor) {
	sceneVisitor.visit(*this);
	Node::accept(sceneVisitor);
}

void TriangleMeshNode::addChild(TriangleMeshRenderStateNode_ptr triangleMeshRenderStateNode) {
	if(m_triangleMeshRenderStateNode)
		Node::removeChild(m_triangleMeshRenderStateNode);
	Node::addChild(triangleMeshRenderStateNode);
	m_triangleMeshRenderStateNode = triangleMeshRenderStateNode;
}

TriangleMeshRenderStateNode_ptr TriangleMeshNode::getTriangleMeshRenderStateNode() {
	return m_triangleMeshRenderStateNode;
}

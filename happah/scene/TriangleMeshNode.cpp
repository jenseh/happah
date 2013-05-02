#include "happah/scene/TriangleMeshNode.h"

TriangleMeshNode::TriangleMeshNode(TriangleMesh_ptr triangleMesh) 
	: SimpleGeometryNode<TriangleMesh>(triangleMesh) {}

TriangleMeshNode::TriangleMeshNode(TriangleMesh_ptr triangleMesh, RigidAffineTransformation& transformation):
		SimpleGeometryNode<TriangleMesh>(triangleMesh, transformation) { }

TriangleMeshNode::~TriangleMeshNode() {}

void TriangleMeshNode::accept(SceneVisitor& sceneVisitor) {
	sceneVisitor.visit(*this);
	Node::accept(sceneVisitor);
}

//TODO: GUIStateNodes should be like RenderStateNodes (only one per node)
void TriangleMeshNode::insertChild(TriangleMeshGUIStateNode_ptr triangleMeshGUIStateNode) {
	Node::insertChild(triangleMeshGUIStateNode);
}

void TriangleMeshNode::insertChild(TriangleMeshRenderStateNode_ptr triangleMeshRenderStateNode) {
	if(m_triangleMeshRenderStateNode)
		Node::removeChild(m_triangleMeshRenderStateNode);
	Node::insertChild(triangleMeshRenderStateNode);
	m_triangleMeshRenderStateNode = triangleMeshRenderStateNode;
}

TriangleMeshRenderStateNode_ptr TriangleMeshNode::getTriangleMeshRenderStateNode() {
	return m_triangleMeshRenderStateNode;
}

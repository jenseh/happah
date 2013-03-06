#include "LineMeshNode.h"

LineMeshNode::LineMeshNode(LineMesh_ptr lineMesh)
	: SimpleGeometryNode<LineMesh>(lineMesh) {}

LineMeshNode::~LineMeshNode() {}

void LineMeshNode::accept(SceneVisitor& sceneVisitor) {
	sceneVisitor.visit(*this);
	Node::accept(sceneVisitor);
}

void LineMeshNode::insertChild(LineMeshRenderStateNode_ptr lineMeshRenderStateNode) {
	if(m_lineMeshRenderStateNode)
		Node::removeChild(m_lineMeshRenderStateNode);
	Node::insertChild(lineMeshRenderStateNode);
	m_lineMeshRenderStateNode = lineMeshRenderStateNode;
}

LineMeshRenderStateNode_ptr LineMeshNode::getLineMeshRenderStateNode() {
	return m_lineMeshRenderStateNode;
}

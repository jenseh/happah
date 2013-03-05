#include "LineMeshNode.h"

LineMeshNode::LineMeshNode(LineMesh_ptr lineMesh)
	: SimpleGeometryNode<LineMesh>(lineMesh) {}

LineMeshNode::~LineMeshNode() {}

void LineMeshNode::accept(SceneVisitor& sceneVisitor) {
	sceneVisitor.visit(*this);
	Node::accept(sceneVisitor);
}

void LineMeshNode::addChild(LineMeshRenderStateNode_ptr lineMeshRenderStateNode) {
	if(m_lineMeshRenderStateNode)
		Node::removeChild(m_lineMeshRenderStateNode);
	Node::addChild(lineMeshRenderStateNode);
	m_lineMeshRenderStateNode = lineMeshRenderStateNode;
}

LineMeshRenderStateNode_ptr LineMeshNode::getLineMeshRenderStateNode() {
	return m_lineMeshRenderStateNode;
}

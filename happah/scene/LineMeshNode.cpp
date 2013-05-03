#include "LineMeshNode.h"

LineMeshNode::LineMeshNode(LineMesh3D_ptr lineMesh)
	: SimpleGeometryNode<LineMesh3D>(lineMesh) {}

LineMeshNode::LineMeshNode(LineMesh3D_ptr lineMesh,RigidAffineTransformation& rigidAffineTransformation)
	: SimpleGeometryNode<LineMesh3D>(lineMesh,rigidAffineTransformation) {}

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

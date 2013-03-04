#include "happah/scene/TriangleMeshRenderStateNode.h"
#include <exception>

TriangleMeshRenderStateNode::TriangleMeshRenderStateNode(TriangleMesh_ptr triangleMesh, hpcolor& color)
	: RenderStateNode(GL_TRIANGLES,triangleMesh->getVertexData(),triangleMesh->getIndices(),color){}

TriangleMeshRenderStateNode::TriangleMeshRenderStateNode(TriangleMesh_ptr triangleMesh, std::vector<hpcolor>* colorVector)
	: RenderStateNode(GL_TRIANGLES,triangleMesh->getVertexData(),triangleMesh->getIndices(),colorVector) {}

TriangleMeshRenderStateNode::~TriangleMeshRenderStateNode() {
	// TODO Auto-generated destructor stub
}


















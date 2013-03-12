#include "happah/scene/ElementRenderStateNode.h"
#include "happah/scene/RenderStateNode.h"
#include <exception>


using namespace std;
ElementRenderStateNode::ElementRenderStateNode(hpuint mode, vector<hpvec3>* vertexData, std::vector<hpuint>* indices, hpcolor& color)
	:RenderStateNode(vertexData,color),m_mode(mode),m_indices(indices),m_indexBufferID(0) {
}

ElementRenderStateNode::ElementRenderStateNode(hpuint mode, vector<hpvec3>* vertexData, std::vector<hpuint>* indices, vector<hpcolor>* colorVector)
	:RenderStateNode(vertexData,colorVector),m_mode(mode),m_indices(indices),m_indexBufferID(0) {
}

ElementRenderStateNode::~ElementRenderStateNode() {
	// TODO Auto-generated destructor stub
}

void ElementRenderStateNode::draw(DrawVisitor& drawVisitor, RigidAffineTransformation& rigidAffineTransformation) {
	drawVisitor.draw(*this, rigidAffineTransformation);
}

void ElementRenderStateNode::setIndexBufferID(GLuint id) {
	m_indexBufferID = id;
}

GLuint ElementRenderStateNode::getIndexBufferID() {
	return m_indexBufferID;
}

GLuint ElementRenderStateNode::getMode() {
	return m_mode;
}

vector<hpuint>* ElementRenderStateNode::getIndices(){
	return m_indices;
}

TriangleMeshRenderStateNode::TriangleMeshRenderStateNode(TriangleMesh_ptr triangleMesh, hpcolor& color)
	: ElementRenderStateNode(GL_TRIANGLES,triangleMesh->getVertexData(),triangleMesh->getIndices(),color){}

TriangleMeshRenderStateNode::TriangleMeshRenderStateNode(TriangleMesh_ptr triangleMesh, std::vector<hpcolor>* colorVector)
	: ElementRenderStateNode(GL_TRIANGLES,triangleMesh->getVertexData(),triangleMesh->getIndices(),colorVector) {}

TriangleMeshRenderStateNode::~TriangleMeshRenderStateNode() {
	// TODO Auto-generated destructor stub
}

LineMeshRenderStateNode::LineMeshRenderStateNode(LineMesh_ptr lineMesh, hpcolor& color)
	: ElementRenderStateNode(GL_LINES,lineMesh->getVertexData(),lineMesh->getIndices(),color){}

LineMeshRenderStateNode::LineMeshRenderStateNode(LineMesh_ptr lineMesh, std::vector<hpcolor>* colorVector)
	: ElementRenderStateNode(GL_LINES,lineMesh->getVertexData(),lineMesh->getIndices(),colorVector) {}

LineMeshRenderStateNode::~LineMeshRenderStateNode() {

}

#include "happah/scene/ElementRenderStateNode.h"
#include "happah/scene/RenderStateNode.h"
#include "happah/scene/DrawVisitor.h"
#include "happah/scene/SceneVisitor.h"
#include <exception>


using namespace std;
ElementRenderStateNode::ElementRenderStateNode(hpuint mode, vector<hpvec3>* verticesAndNormals, std::vector<hpuint>* indices, hpcolor& color)
	: RenderStateNode(verticesAndNormals, color), m_mode(mode), m_indices(indices), m_indexBufferID(0),m_selected(0) {
}

ElementRenderStateNode::ElementRenderStateNode(hpuint mode, vector<hpvec3>* verticesAndNormals, std::vector<hpuint>* indices, vector<hpcolor>* colorVector)
	: RenderStateNode(verticesAndNormals, colorVector), m_mode(mode), m_indices(indices), m_indexBufferID(0),m_selected(0) {
}

ElementRenderStateNode::~ElementRenderStateNode() {
	// TODO Auto-generated destructor stub
}

void ElementRenderStateNode::draw(DrawVisitor& drawVisitor, RigidAffineTransformation& rigidAffineTransformation) {
	drawVisitor.draw(getPtr(), rigidAffineTransformation);
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

void ElementRenderStateNode::setSelected(int selected){
	m_selected = selected;
}

int ElementRenderStateNode::getSelected(){
	return m_selected;
}

TriangleMeshRenderStateNode::TriangleMeshRenderStateNode(TriangleMesh3D_ptr triangleMesh, hpcolor& color)
	: ElementRenderStateNode(GL_TRIANGLES,triangleMesh->getVerticesAndNormals(),triangleMesh->getIndices(),color){

}

TriangleMeshRenderStateNode::TriangleMeshRenderStateNode(TriangleMesh3D_ptr triangleMesh, std::vector<hpcolor>* colorVector)
	: ElementRenderStateNode(GL_TRIANGLES,triangleMesh->getVerticesAndNormals(),triangleMesh->getIndices(),colorVector) {}

TriangleMeshRenderStateNode::~TriangleMeshRenderStateNode() {
	// TODO Auto-generated destructor stub
}

LineMeshRenderStateNode::LineMeshRenderStateNode(LineMesh3D_ptr lineMesh, hpcolor& color)
	: ElementRenderStateNode(GL_LINES,lineMesh->getVerticesAndNormals(),lineMesh->getIndices(),color){

}

LineMeshRenderStateNode::LineMeshRenderStateNode(LineMesh3D_ptr lineMesh, std::vector<hpcolor>* colorVector)
	: ElementRenderStateNode(GL_LINES,lineMesh->getVerticesAndNormals(),lineMesh->getIndices(),colorVector) {}

LineMeshRenderStateNode::~LineMeshRenderStateNode() {

}

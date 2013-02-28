#include "happah/scene/TriangleMeshRenderStateNode.h"
#include <exception>


TriangleMeshRenderStateNode::TriangleMeshRenderStateNode(TriangleMesh_ptr triangleMesh,hpcolor color){
	m_triangleMesh = triangleMesh;
	m_color = color;
}

TriangleMeshRenderStateNode::TriangleMeshRenderStateNode(TriangleMesh_ptr triangleMesh,std::vector<hpcolor>* colorVector){
	if (triangleMesh->getVertexData()->size() != colorVector->size())
			throw;
	m_triangleMesh = triangleMesh;
	m_colorVector = colorVector;
}

TriangleMeshRenderStateNode::~TriangleMeshRenderStateNode() {
	// TODO Auto-generated destructor stub
}

void TriangleMeshRenderStateNode::accept(SceneVisitor& sceneVisitor){
	sceneVisitor.visit(*this);
	Node::accept(sceneVisitor);
}


void TriangleMeshRenderStateNode::setVertexBufferID(GLuint id){
	m_vertexBufferID = id;
}
GLuint TriangleMeshRenderStateNode::getVertexBufferID(){
	return m_indexBufferID;
}
void TriangleMeshRenderStateNode::setIndexBufferID(GLuint id){
   m_indexBufferID = id;
}
GLuint TriangleMeshRenderStateNode::getIndexBufferID(){
	return m_indexBufferID;
}
void TriangleMeshRenderStateNode::setVertexArrayObjectID(GLuint id){
	m_vertexArrayObjectID = id;
}
GLuint TriangleMeshRenderStateNode::getVertexArrayObjectID(){
	return m_vertexArrayObjectID;
}
void TriangleMeshRenderStateNode::setColor(hpcolor color){
	m_color = color;
}
hpcolor TriangleMeshRenderStateNode::getColor(){

}

void TriangleMeshRenderStateNode::setColorVector(std::vector<hpcolor>* colorVector){
	m_colorVector = colorVector;
}

std::vector<hpcolor>* TriangleMeshRenderStateNode::getColorVector(){
	return m_colorVector;
}

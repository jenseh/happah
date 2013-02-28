#include "happah/scene/TriangleMeshRenderStateNode.h"
#include <exception>


TriangleMeshRenderStateNode::TriangleMeshRenderStateNode(TriangleMesh_ptr triangleMesh,hpcolor &color)
														:m_vertexBufferID(0),
														 m_indexBufferID(0),
														 m_vertexArrayObjectID(2){
	m_triangleMesh = triangleMesh;
	m_color = color;
}

TriangleMeshRenderStateNode::TriangleMeshRenderStateNode(TriangleMesh_ptr triangleMesh,std::vector<hpcolor>* colorVector)
														:m_vertexBufferID(0),
														 m_indexBufferID(0),
														 m_vertexArrayObjectID(1) {
	if (triangleMesh->getVertexData()->size() != colorVector->size())
			throw; // TODO: Find Proper Exception !
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

TriangleMesh_ptr TriangleMeshRenderStateNode::getTriangleMesh(){
	return m_triangleMesh;
}

void TriangleMeshRenderStateNode::setColorVector(std::vector<hpcolor>* colorVector){
	if (m_triangleMesh->getVertexData()->size() != colorVector->size())
			throw; // TODO: Find Proper Exception !
	m_colorVector = colorVector;
}

std::vector<hpcolor>* TriangleMeshRenderStateNode::getColorVector(){
	return m_colorVector;
}
//TODO: REMOVE AS SOON AS USING NEW TRIANGLE MESH !!!
GLuint TriangleMeshRenderStateNode::getColorBufferID(){
	return m_colorBufferID;
}

void TriangleMeshRenderStateNode::setColorBufferID(GLuint id){
	m_colorBufferID = id;
}






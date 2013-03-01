#include "happah/scene/TriangleMeshRenderStateNode.h"
#include <exception>


TriangleMeshRenderStateNode::TriangleMeshRenderStateNode(TriangleMesh_ptr triangleMesh,hpcolor& color,Material& material):
																									 m_vertexBufferID(0),
																									 m_indexBufferID(0),
																									 m_vertexArrayObjectID(0),
																									 m_colorBufferID(0),
																									 m_initialized(false),
																									 m_hasColorVector(false){
	m_triangleMesh = triangleMesh;
	m_color = color;
	m_material = material;
}

TriangleMeshRenderStateNode::TriangleMeshRenderStateNode(TriangleMesh_ptr triangleMesh,std::vector<hpcolor>* colorVector,Material& material):
																															m_vertexBufferID(0),
																															m_indexBufferID(0),
																															m_vertexArrayObjectID(0),
																															m_colorBufferID(0),
																															m_initialized(false),
																															m_hasColorVector(true){
	if (triangleMesh->getVertexData()->size() != colorVector->size())
			throw; // TODO: Find Proper Exception !

	m_triangleMesh = triangleMesh;
	m_colorVector = colorVector;
	m_material = material;
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
	return m_vertexBufferID;
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
	return m_color;
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

bool TriangleMeshRenderStateNode::isInitialized(){
	return m_initialized;
}

void TriangleMeshRenderStateNode::setInitialized(bool isInitialized){
	m_initialized = isInitialized;
}

bool TriangleMeshRenderStateNode::hasColorVector(){
	return m_hasColorVector;
}

void TriangleMeshRenderStateNode::setMaterial(Material& material){
	m_material = material;
}
Material TriangleMeshRenderStateNode::getMaterial(){
	return m_material;
}




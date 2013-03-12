#include "happah/scene/RenderStateNode.h"
#include <exception>


using namespace std;

RenderStateNode::RenderStateNode(vector<hpvec3>* vertexData, hpcolor& color)
	:m_vertexData(vertexData),m_color(color), m_vertexBufferID(0), m_vertexArrayObjectID(0), m_colorBufferID(0), m_initialized(false), m_hasColorVector(false) {

	Material material;
	material.setAmbientFactor(1.5f);
	material.setDiffuseFactor(1.7f);
	material.setSpecularFactor(1.3f);
	material.setPhongExponent(10.0f);
	m_material = material;
}

RenderStateNode::RenderStateNode(vector<hpvec3>* vertexData, vector<hpcolor>* colorVector)
	:m_vertexData(vertexData),m_color(0.0f,0.0f,0.0f,0.0f),m_colorVector(colorVector), m_vertexBufferID(0), m_vertexArrayObjectID(0), m_colorBufferID(0), m_initialized(false), m_hasColorVector(true) {


	if (colorVector->size() != vertexData->size()/2)
		throw;		// TODO : find proper exception;

	Material material;
	material.setAmbientFactor(1.5f);
	material.setDiffuseFactor(1.7f);
	material.setSpecularFactor(1.3f);
	material.setPhongExponent(10.0f);
	m_material = material;
}

RenderStateNode::~RenderStateNode() {

}

void RenderStateNode::accept(SceneVisitor& sceneVisitor) {
	sceneVisitor.visit(*this);
	Node::accept(sceneVisitor);
}


void RenderStateNode::setVertexBufferID(GLuint id) {
	m_vertexBufferID = id;
}
GLuint RenderStateNode::getVertexBufferID() {
	return m_vertexBufferID;
}

void RenderStateNode::setVertexArrayObjectID(GLuint id) {
	m_vertexArrayObjectID = id;
}
GLuint RenderStateNode::getVertexArrayObjectID() {
	return m_vertexArrayObjectID;
}
void RenderStateNode::setColor(hpcolor color) {
	m_color = color;
}
hpcolor RenderStateNode::getColor() {
	return m_color;
}
void RenderStateNode::setColorVector(vector<hpcolor>* colorVector) {
	if (m_vertexData->size() != colorVector->size()/2)
		throw; // TODO: Find Proper Exception !
	m_colorVector = colorVector;
}

GLuint RenderStateNode::getColorBufferID() {
	return m_colorBufferID;
}

void RenderStateNode::setColorBufferID(GLuint id) {
	m_colorBufferID = id;
}

bool RenderStateNode::isInitialized() {
	return m_initialized;
}

void RenderStateNode::setInitialized(bool isInitialized) {
	m_initialized = isInitialized;
}

bool RenderStateNode::hasColorVector() {
	return m_hasColorVector;
}

void RenderStateNode::setMaterial(Material& material) {
	m_material = material;
}
Material RenderStateNode::getMaterial() {
	return m_material;
}


vector<hpvec3>* RenderStateNode::getVertexData() {
	return m_vertexData;
}

vector<hpvec4>* RenderStateNode::getColorVector(){
	if (m_vertexData->size() != m_colorVector->size()/2)
		throw; // TODO: Find Proper Exception !
	return m_colorVector;
}









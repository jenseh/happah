#include "RenderStateNode.h"
#include <exception>


using namespace std;

RenderStateNode::RenderStateNode(hpuint mode, vector<hpvec3>* vertexData, std::vector<hpuint>* indices, hpcolor& color)
	:m_mode(mode),m_vertexData(vertexData),m_indices(indices),m_color(color), m_vertexBufferID(0), m_indexBufferID(0), m_vertexArrayObjectID(0), m_colorBufferID(0), m_initialized(false), m_hasColorVector(false) {

	Material material;
	material.setAmbientFactor(1.5f);
	material.setDiffuseFactor(1.7f);
	material.setSpecularFactor(1.3f);
	material.setPhongExponent(10.0f);
	m_material = material;
}

RenderStateNode::RenderStateNode(hpuint mode, vector<hpvec3>* vertexData, std::vector<hpuint>* indices, vector<hpcolor>* colorVector)
	:m_mode(mode),m_vertexData(vertexData),m_indices(indices),m_color(0.0f,0.0f,0.0f,0.0f),m_colorVector(colorVector), m_vertexBufferID(0), m_indexBufferID(0), m_vertexArrayObjectID(0), m_colorBufferID(0), m_initialized(false), m_hasColorVector(true) {


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
	// TODO Auto-generated destructor stub
}

void RenderStateNode::accept(SceneVisitor& sceneVisitor) {
	sceneVisitor.visit(*this);
	Node::accept(sceneVisitor);
}

void RenderStateNode::draw(DrawVisitor& drawVisitor, RigidAffineTransformation& rigidAffineTransformation) {
	drawVisitor.draw(*this, rigidAffineTransformation);
}

void RenderStateNode::setVertexBufferID(GLuint id) {
	m_vertexBufferID = id;
}
GLuint RenderStateNode::getVertexBufferID() {
	return m_vertexBufferID;
}
void RenderStateNode::setIndexBufferID(GLuint id) {
	m_indexBufferID = id;
}
GLuint RenderStateNode::getIndexBufferID() {
	return m_indexBufferID;
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

GLuint RenderStateNode::getMode() {
	return m_mode;
}

vector<hpvec3>* RenderStateNode::getVertexData() {
	return m_vertexData;
}

vector<hpuint>* RenderStateNode::getIndices(){
	return m_indices;
}

vector<hpvec4>* RenderStateNode::getColorVector(){
	if (m_vertexData->size() != m_colorVector->size()/2)
		throw; // TODO: Find Proper Exception !
	return m_colorVector;
}


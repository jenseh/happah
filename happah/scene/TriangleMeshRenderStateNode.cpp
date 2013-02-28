/*
 * TriangleMeshRenderStateNode.cpp
 *
 *  Created on: 28.02.2013
 *      Author: msauer
 */

#include "happah/scene/TriangleMeshRenderStateNode.h"

TriangleMeshRenderStateNode::TriangleMeshRenderStateNode() {


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

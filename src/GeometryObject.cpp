/*
 * GeometryObject.cpp
 *
 *  Created on: Oct 24, 2012
 *      Author: matthias
 */

#include "GeometryObject.h"

GeometryObject::GeometryObject(QMatrix4x4 *_projectionMatrix,QMatrix4x4 *_viewMatrix,QVector3D* _camPos) : Component() {
    viewMatrix_ = _viewMatrix;
    projectionMatrix_ = _projectionMatrix;
    camPos_ = _camPos;
}

GeometryObject::~GeometryObject() {
	// TODO Auto-generated destructor stub
}

// Prepare Vertex and Index Buffer to be filled with Data


int GeometryObject::initVertexBuffer(enum QGLBuffer::UsagePattern usagePattern){
    vertexBuffer_.create();
    vertexBuffer_.setUsagePattern(usagePattern);
    if (!vertexBuffer_.bind()) {
			qWarning() << "Could not bind vertex buffer";
			return -1;
	}
	return 0;
}

int GeometryObject::fillVertexBuffer(){
    if (!vertexBuffer_.isCreated()){
		qWarning() << " Vertex Buffer does not exist yet";
		return -1;
	}
    if (!vertexBuffer_.bind()) {
				qWarning() << "Could not bind vertex buffer";
				return -1;
	}
    vertexBuffer_.allocate(&(vertexData_[0]),vertexData_.size()*sizeof(vertexData_[0]));
	return 0;
}

void GeometryObject::init(/*QMatrix4x4 _projectionMatrix, QMatrix4x4 _viewMatrix*/) {
    //viewMatrix = _viewMatrix;
    //projectionMatrix = _projectionMatrix;

    modelMatrix_.setToIdentity();
    normalMatrix_.setToIdentity();

    //Update ModelViewProjection Matrix
    MV_ = *viewMatrix_ * modelMatrix_;
    MVP_ = *projectionMatrix_ * MV_;
}
/*
void GeometryObject::updateProjectionMatrix(QMatrix4x4 _projectionMatrix) {
    projectionMatrix = _projectionMatrix;
    MVP = projectionMatrix * MV;
}
*/
void GeometryObject::updateView(/*QMatrix4x4 _viewMatrix, QVector3D _eye*/) {
   // viewMatrix = _viewMatrix;
   // eye = _eye;
    MV_ = *viewMatrix_ * modelMatrix_;
    MVP_ = *projectionMatrix_ * MV_;
}

void GeometryObject::draw(QGLShaderProgram *shader) {
    bindVBuffer();
    shader->bind();
    shader->setAttributeBuffer("vertex", GL_FLOAT, 0, 4, 2 * 4 * sizeof(float));
    shader->setAttributeBuffer("normal", GL_FLOAT, 2 * 4 * sizeof(float), 4, 2 * 4 * sizeof(float));
    shader->enableAttributeArray("vertex");
    shader->enableAttributeArray("normal");
    shader->setUniformValue("MVP", MVP_);
    shader->setUniformValue("MV", MV_);
    shader->setUniformValue("normalMat", normalMatrix_);
    shader->setUniformValue("eye", *camPos_);

    vertexBuffer_.bind();
    int mode = GL_QUADS;
    int stride = 0;
    glDrawArrays(mode, stride, vertexData_.size());
 //   shader->release();
}

int GeometryObject::bindVBuffer(){
    if (!vertexBuffer_.bind()) {
			qWarning() << "Could not bind vertex buffer";
			return -1;
	}
	return 0;

}

void GeometryObject::createVertexData(){
	// Dummy !! Vertex Data is Created in the inheriting classes
}

void GeometryObject::dataPushback(glm::vec4 data){
    vertexData_.push_back(data);
}

void GeometryObject::rotate(float angle, float x, float y, float z) {
    modelMatrix_.rotate(angle, x, y, z);
   // MV = viewMatrix * modelMatrix;
   // MVP = projectionMatrix * MV;
}

void GeometryObject::translate(float x, float y, float z) {
    modelMatrix_.translate(x, y, z);
  //  MV = viewMatrix * modelMatrix;
  //  MVP = projectionMatrix * MV;
}

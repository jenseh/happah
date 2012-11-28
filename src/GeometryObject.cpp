/*
 * GeometryObject.cpp
 *
 *  Created on: Oct 24, 2012
 *      Author: matthias
 */

#include "GeometryObject.h"

GeometryObject::GeometryObject() :
        Component() {
}

GeometryObject::~GeometryObject() {
	// TODO Auto-generated destructor stub
}

// Prepare Vertex and Index Buffer to be filled with Data

int GeometryObject::initVertexBuffer(
		enum QGLBuffer::UsagePattern usagePattern) {
	vertexBuffer_.create();
	vertexBuffer_.setUsagePattern(usagePattern);
	if (!vertexBuffer_.bind()) {
		qWarning() << "Could not bind vertex buffer";
		return -1;
	}
	return 0;
}

int GeometryObject::fillVertexBuffer() {
	if (!vertexBuffer_.isCreated()) {
		qWarning() << " Vertex Buffer does not exist yet";
		return -1;
	}
	if (!vertexBuffer_.bind()) {
		qWarning() << "Could not bind vertex buffer";
		return -1;
	}
	vertexBuffer_.allocate(&(vertexData_[0]),
			vertexData_.size() * sizeof(vertexData_[0]));
	return 0;
}

void GeometryObject::init() {
    modelMatrix_.setToIdentity();
}

void GeometryObject::draw(QGLShaderProgram *shader, QMatrix4x4* projectionMatrix,
                          QMatrix4x4* viewMatrix, QVector3D* cameraPosition) {
    //Update ModelViewProjection Matrix
    QMatrix4x4 MV = *viewMatrix * modelMatrix_;
    QMatrix4x4 MVP = *projectionMatrix * MV;

    //Update Normal Matrix, put these updates somewhere else
    //Note that this now is and has to be a 3x3 matrix
    QMatrix3x3 normalMatrix = MV.normalMatrix();

	bindVBuffer();
	shader->bind();
	shader->setAttributeBuffer("vertex", GL_FLOAT, 0, 4, 2 * 4 * sizeof(float));
	shader->setAttributeBuffer("normal", GL_FLOAT, 2 * 4 * sizeof(float), 4,
			2 * 4 * sizeof(float));
	shader->enableAttributeArray("vertex");
	shader->enableAttributeArray("normal");
    shader->setUniformValue("MVP", MVP);
    shader->setUniformValue("MV", MV);
    shader->setUniformValue("normalMat", normalMatrix);
    shader->setUniformValue("eye", *cameraPosition);

	vertexBuffer_.bind();
	int mode = GL_QUADS;
	int stride = 0;
	glDrawArrays(mode, stride, vertexData_.size());
	//   shader->release();
}

int GeometryObject::bindVBuffer() {
	if (!vertexBuffer_.bind()) {
		qWarning() << "Could not bind vertex buffer";
		return -1;
	}
	return 0;

}

void GeometryObject::createVertexData() {
	// Dummy !! Vertex Data is Created in the inheriting classes
}

void GeometryObject::dataPushback(glm::vec4 data) {
	vertexData_.push_back(data);
}

void GeometryObject::rotate(float angle, float x, float y, float z) {
	modelMatrix_.rotate(angle, x, y, z);
}

void GeometryObject::translate(float x, float y, float z) {
    modelMatrix_.translate(x, y, z);
}

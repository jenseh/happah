/*
 * GeometryObject.cpp
 *
 *  Created on: Oct 24, 2012
 *      Author: matthias
 */

#include "GeometryObject.h"

GeometryObject::GeometryObject(QMatrix4x4 *_projectionMatrix,
		QMatrix4x4 *_viewMatrix, QVector3D* _camPos) :
		Component() {
	viewMatrix = _viewMatrix;
	projectionMatrix = _projectionMatrix;
	camPos = _camPos;
}

GeometryObject::~GeometryObject() {
	// TODO Auto-generated destructor stub
}

// Prepare Vertex and Index Buffer to be filled with Data

int GeometryObject::initVertexBuffer(
		enum QGLBuffer::UsagePattern usagePattern) {
	vertexBuffer.create();
	vertexBuffer.setUsagePattern(usagePattern);
	if (!vertexBuffer.bind()) {
		qWarning() << "Could not bind vertex buffer";
		return -1;
	}
	return 0;
}

int GeometryObject::fillVertexBuffer() {
	if (!vertexBuffer.isCreated()) {
		qWarning() << " Vertex Buffer does not exist yet";
		return -1;
	}
	if (!vertexBuffer.bind()) {
		qWarning() << "Could not bind vertex buffer";
		return -1;
	}
	vertexBuffer.allocate(&(vertexData[0]),
			vertexData.size() * sizeof(vertexData[0]));
	return 0;
}

void GeometryObject::init() {
	modelMatrix.setToIdentity();
	normalMatrix.setToIdentity();

	//Update ModelViewProjection Matrix
	MV = *viewMatrix * modelMatrix;
	MVP = *projectionMatrix * MV;
}

void GeometryObject::updateProjectionMatrix() {
	MVP = *projectionMatrix * MV;
}

void GeometryObject::updateViewMatrix() {
	MV = *viewMatrix * modelMatrix;
	MVP = *projectionMatrix * MV;
}

void GeometryObject::draw(QGLShaderProgram *shader) {
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
	shader->setUniformValue("eye", *camPos);

	vertexBuffer.bind();
	int mode = GL_QUADS;
	int stride = 0;
	glDrawArrays(mode, stride, vertexData.size());
	//   shader->release();
}

int GeometryObject::bindVBuffer() {
	if (!vertexBuffer.bind()) {
		qWarning() << "Could not bind vertex buffer";
		return -1;
	}
	return 0;

}

void GeometryObject::createVertexData() {
	// Dummy !! Vertex Data is Created in the inheriting classes
}

void GeometryObject::dataPushback(glm::vec4 data) {
	vertexData.push_back(data);
}

void GeometryObject::rotate(float angle, float x, float y, float z) {
	modelMatrix.rotate(angle, x, y, z);
	// MV = viewMatrix * modelMatrix;
	// MVP = projectionMatrix * MV;
}

void GeometryObject::translate(float x, float y, float z) {
	modelMatrix.translate(x, y, z);
	//  MV = viewMatrix * modelMatrix;
	//  MVP = projectionMatrix * MV;
}

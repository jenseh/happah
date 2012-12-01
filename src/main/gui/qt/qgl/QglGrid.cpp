#include "QglGrid.h"

QglGrid::QglGrid() : Grid() {
}

QglGrid::~QglGrid() {
}

void QglGrid::draw(QGLShaderProgram *shader, QMatrix4x4* projectionMatrix, QMatrix4x4* viewMatrix) {
    QMatrix4x4 MV = *viewMatrix * modelMatrix_;
    QMatrix4x4 MVP = *projectionMatrix * MV;

    bindVBuffer();
	shader->bind();
	shader->setAttributeBuffer("vertex", GL_FLOAT, 0, 4, 0);
	shader->enableAttributeArray("vertex");
    shader->setUniformValue("MVP", MVP);

	int mode = GL_LINES;
	int stride = 0;
    glDrawArrays(mode, stride, vertexData_.size());

	shader->release();
}

//The following part is only here due to problems with multiple inheritance
// Prepare Vertex and Index Buffer to be filled with Data

int QglGrid::bindVBuffer() {
    if (!vertexBuffer_.bind()) {
        qWarning() << "Could not bind vertex buffer";
        return -1;
    }
    return 0;
}

int QglGrid::initVertexBuffer(
        enum QGLBuffer::UsagePattern usagePattern) {
    vertexBuffer_.create();
    vertexBuffer_.setUsagePattern(usagePattern);
    if (!vertexBuffer_.bind()) {
        qWarning() << "Could not bind vertex buffer";
        return -1;
    }
    return 0;
}

int QglGrid::fillVertexBuffer() {
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

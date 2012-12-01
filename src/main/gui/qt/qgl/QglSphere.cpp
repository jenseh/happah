#include "QglSphere.h"

QglSphere::QglSphere(float radius) : Sphere(radius){

}

QglSphere::~QglSphere() {
    // TODO Auto-generated destructor stub
}


//The following part is only here due to problems with multiple inheritance
// Prepare Vertex and Index Buffer to be filled with Data
void QglSphere::draw(QGLShaderProgram* shader, QMatrix4x4* projectionMatrix,
                             QMatrix4x4* viewMatrix, QVector3D* cameraPosition) {
    QMatrix4x4 MV = *viewMatrix * modelMatrix_;
    QMatrix4x4 MVP = *projectionMatrix * MV;
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

int QglSphere::bindVBuffer() {
    if (!vertexBuffer_.bind()) {
        qWarning() << "Could not bind vertex buffer";
        return -1;
    }
    return 0;
}

int QglSphere::initVertexBuffer(
        enum QGLBuffer::UsagePattern usagePattern) {
    vertexBuffer_.create();
    vertexBuffer_.setUsagePattern(usagePattern);
    if (!vertexBuffer_.bind()) {
        qWarning() << "Could not bind vertex buffer";
        return -1;
    }
    return 0;
}

int QglSphere::fillVertexBuffer() {
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

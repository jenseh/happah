#ifndef QGLSPHERE_H_
#define QGLSPHERE_H_

#include <glm/glm.hpp>
#include <QGLBuffer>
#include <QGLShaderProgram>
#include "../../../core/geometries/Sphere.h"

class QglSphere: public Sphere {

public:
    QglSphere(float radius = 1.0f);
    ~QglSphere();

    void draw(QGLShaderProgram* shader, QMatrix4x4* projectionMatrix, QMatrix4x4* viewMatrix,
              QVector3D* cameraPosition);
    int initVertexBuffer(enum QGLBuffer::UsagePattern usagePattern);
    int bindVBuffer();
    int fillVertexBuffer();

protected:
    QGLBuffer vertexBuffer_;
};

#endif

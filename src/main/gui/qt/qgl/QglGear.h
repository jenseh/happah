#ifndef QGLGEAR_H
#define QGLGEAR_H

#include <QGLBuffer>
#include <QGLShaderProgram>
#include "../../../core/geometries/Gear.h"

class QglGear: public Gear{
public:
    QglGear(float radius, float length, int toothCount);
    ~QglGear();

    void draw(QGLShaderProgram* shader, QMatrix4x4* projectionMatrix, QMatrix4x4* viewMatrix,
              QVector3D* cameraPosition);
    int initVertexBuffer(enum QGLBuffer::UsagePattern usagePattern);
    int bindVBuffer();
    int fillVertexBuffer();

protected:
    QGLBuffer vertexBuffer_;
};

#endif // QGLGEAR_H

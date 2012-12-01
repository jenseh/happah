#ifndef QGLGRID_H
#define QGLGRID_H

#include <QGLShaderProgram>
#include <QGLBuffer>
#include "../../../core/geometries/Grid.h"

class QglGrid: public Grid {
public:
    QglGrid();
    ~QglGrid();

    void draw(QGLShaderProgram *shader, QMatrix4x4* projectionMatrix = 0, QMatrix4x4* viewMatrix = 0);
    int initVertexBuffer(enum QGLBuffer::UsagePattern usagePattern);
    int bindVBuffer();
    int fillVertexBuffer();

protected:
    QGLBuffer vertexBuffer_;
};

#endif // QGLGRID_H

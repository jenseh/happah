#ifndef GLQUADMESH_H
#define GLQUADMESH_H

#include <QGLShaderProgram>
#include <QMatrix4x4>
#include <QVector3D>
#include <QGLBuffer>

#include "../../../core/models/QuadMesh.h"

class GlQuadMesh : public QuadMesh {
public:
    GlQuadMesh(QuadMesh* quadMesh);

    void draw(QGLShaderProgram* shader, QMatrix4x4* projectionMatrix, QMatrix4x4* viewMatrix,
              QVector3D* cameraPosition);
    int initVertexBuffer(enum QGLBuffer::UsagePattern usagePattern);
    int bindVBuffer();
    int fillVertexBuffer();

protected:
    QGLBuffer vertexBuffer_;
};

#endif // GLQUADMESH_H_

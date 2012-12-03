#ifndef GLQUADLITERALMESH_H
#define GLQUADLITERALMESH_H

#include <QGLShaderProgram>
#include <QMatrix4x4>
#include <QVector3D>
#include <QGLBuffer>

#include "../../../core/models/QuadliteralMesh.h"

class GlQuadliteralMesh : public QuadliteralMesh {
public:
    GlQuadliteralMesh(QuadliteralMesh* quadliteralMesh);

    void draw(QGLShaderProgram* shader, QMatrix4x4* projectionMatrix, QMatrix4x4* viewMatrix,
              QVector3D* cameraPosition);
    int initVertexBuffer(enum QGLBuffer::UsagePattern usagePattern);
    int bindVBuffer();
    int fillVertexBuffer();

protected:
    QGLBuffer vertexBuffer_;
};

#endif // GLQUADLITERALMESH_H_

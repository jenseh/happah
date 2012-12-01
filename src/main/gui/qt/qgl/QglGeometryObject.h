/*
 * QglGeometryObject.h
 *
 *  Created on: Oct 24, 2012
 *      Author: matthias
 */

#ifndef QGLGEOMETRYOBJECT_H_
#define QGLGEOMETRYOBJECT_H_

#include <QGLBuffer>
#include <QGLShaderProgram>
#include "../../../core/geometries/GeometryObject.h"

class QglGeometryObject: public GeometryObject{
public:
    QglGeometryObject();
    virtual ~QglGeometryObject();

    void draw(QGLShaderProgram* shader, QMatrix4x4* projectionMatrix, QMatrix4x4* viewMatrix,
              QVector3D* cameraPosition);
    int initVertexBuffer(enum QGLBuffer::UsagePattern usagePattern);
    int bindVBuffer();
    int fillVertexBuffer();

protected:
    QGLBuffer vertexBuffer_;
};

#endif /* QGLGEOMETRYOBJECT_H_ */

/*
 * GeometryObject.h
 *
 *  Created on: Oct 24, 2012
 *      Author: matthias
 */

#ifndef GEOMETRYOBJECT_H_
#define GEOMETRYOBJECT_H_

#include <QGLWidget>
#include <QGLBuffer>
#include <QGLShaderProgram>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include "Component.h"

class QglGeometryObject: public QObject, public Component {
	Q_OBJECT
public:
    QglGeometryObject(QMatrix4x4* projectionMatrix, QMatrix4x4* viewMatrix,
            QVector3D* camPos);
	virtual ~QglGeometryObject();
	void createGrid();
	int bindVBuffer();
	void dataPushback(glm::vec4 data);

	// For drawing
	void init();
    void draw(QGLShaderProgram* shader);
	// void updateProjectionMatrix();  Please read the comment in GeometryObject.ccp
	void updateViewMatrix();

	void createVertexData();
	int initVertexBuffer(enum QGLBuffer::UsagePattern usagePattern);
	int fillVertexBuffer();

	// Transformations
	void rotate(float angle, float x, float y, float z);
	void translate(float x, float y, float z);

protected:
	QGLBuffer vertexBuffer_;
	std::vector<glm::vec4> vertexData_;

	// For drawing
	QMatrix4x4 *projectionMatrix_, *viewMatrix_, MVP_, MV_; //redundant information to avoid repeated computation
	QMatrix4x4 modelMatrix_,normalMatrix_;

    QVector3D *cameraPosition_;
};

#endif /* GEOMETRYOBJECT_H_ */

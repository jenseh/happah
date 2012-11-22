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

class GeometryObject: public QObject, public Component {
	Q_OBJECT
public:
	GeometryObject(QMatrix4x4 * _projectionMatrix, QMatrix4x4 *_viewMatrix,
			QVector3D * _camPos);
	virtual ~GeometryObject();
	void createGrid();
	int bindVBuffer();
	void dataPushback(glm::vec4 data);

	// For drawing
	void init();
	void draw(QGLShaderProgram *shader);
	void updateProjectionMatrix();
	void updateViewMatrix();

	void createVertexData();
	int initVertexBuffer(enum QGLBuffer::UsagePattern usagePattern);
	int fillVertexBuffer();

	// Transformations
	void rotate(float angle, float x, float y, float z);
	void translate(float x, float y, float z);
protected:
	QGLBuffer vertexBuffer;
	std::vector<glm::vec4> vertexData;

	// For drawing
	QMatrix4x4 *projectionMatrix, *viewMatrix, MVP, MV; //redundant information to avoid repeated computation
	QMatrix4x4 modelMatrix;
	QMatrix3x3 normalMatrix;
	QVector3D *camPos;
};

#endif /* GEOMETRYOBJECT_H_ */

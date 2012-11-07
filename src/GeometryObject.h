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

class GeometryObject: public QObject {
Q_OBJECT
public:
	GeometryObject(QWidget* parent = 0);
	virtual ~GeometryObject();
	int InitVertexBuffer(enum QGLBuffer::UsagePattern usagePattern);
	int FillVertexBuffer();
	void CreateGrid();
	void DrawArrays(int mode,int stride);
	int BindVBuffer();
	void DataPushback(glm::vec4 data);
	void CreateVertexData();


private:

	QGLBuffer 		 vertexBuffer;
	std::vector<glm::vec4> vertexData;
};

#endif /* GEOMETRYOBJECT_H_ */

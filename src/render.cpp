/*
 * render.cpp
 *
 *  Created on: 15.08.2012
 *      Author: msauer
 */

#include <QtGui>
#include "render.h"

	const int count = 360;
	const float pi = 3.14159265;

RenderClass::RenderClass(const QGLFormat& format, QWidget *parent) :
		QGLWidget(format, parent), vertexBuffer(QGLBuffer::VertexBuffer) {
	ProjectionMatrix.setToIdentity();
	ModelMatrix.setToIdentity();
	ViewMatrix.setToIdentity();


}

void RenderClass::initializeGL() {

	QGLFormat glFormat = QGLWidget::format();
	if (!glFormat.sampleBuffers())
		qWarning() << "Could not enable sample buffers";

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);

	if (!initShaderProgram("./src/shader/simpleVert.glsl", "./src/shader/simpleFrag.glsl"))
		return;

	createSphere();

	// Use vertex Buffer as attribute

	shader.setAttributeBuffer("vertex", GL_FLOAT, 0, 4);
	shader.enableAttributeArray("vertex");

}

void RenderClass::resizeGL(int width, int height) {
	glViewport(0, 0, width, qMax(height, 1));
	float ratio = (float) width / (float) height;
	ProjectionMatrix.perspective(45.0f, ratio, 0.1f, 100.0f);

}

void RenderClass::paintGL() {

	update();

	draw();

}

bool RenderClass::initShaderProgram(const QString& vertexShaderPath, const QString& fragmentShaderPath) {
	//load and compile Vertex Shader
	bool result = shader.addShaderFromSourceFile(QGLShader::Vertex, vertexShaderPath);
	if (!result)
		qWarning() << shader.log();

	//load and compile Fragment Shader
	result = shader.addShaderFromSourceFile(QGLShader::Fragment, fragmentShaderPath);
	if (!result)
		qWarning() << shader.log();

	// link shader
	result = shader.link();
	if (!result)
		qWarning() << "Could not link shader program: " << shader.log();
	return result;
}

void RenderClass::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shader.bind();
	shader.setUniformValue("MVP", MVP);
	glDrawArrays(GL_LINE_STRIP, 0, count);

}

void RenderClass::update() {

	//Update ViewMatrix
	QMatrix4x4 tViewMatrix;
	tViewMatrix.setToIdentity();
	tViewMatrix.translate(0.0f, 0.0f, -5.0f);
	tViewMatrix.rotate(0.0f, 1.0f, 0.0f, 0.0f);
	tViewMatrix.rotate(0.0f, 0.0f, 1.0f, 0.0f);

	ViewMatrix = tViewMatrix;

	//QMatrix4x4 LookatMatrix;
	//LookatMatrix.lookAt(QVector3D(0.0f, 0.0f, 5.0f), QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f));
	//ViewMatrix = LookatMatrix;

	//Update ModelMatrix
	QMatrix4x4 tModelMatrix;
	tModelMatrix.setToIdentity();
	tModelMatrix.scale(1.0f, 1.0f, 1.0f);
	ModelMatrix = tModelMatrix;

	//Update ModelViewProjection Matrix

	MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

}

void RenderClass::createSphere() {
	/*


	 */


	int angle = 360 / count;

	typedef struct {
		float x;
		float y;
		float z;
		float w;
	} VERTICES;

	VERTICES points[count];
	int i = 0;

	for (int phi = 0;
			phi < 360;
			phi = phi + angle) {

			float radPhi = phi * (pi / 180);

			points[i].x = cos(radPhi);
			points[i].y = sin(radPhi);
			points[i].z = 0.0f;
			points[i].w = 1.0f;

			qWarning() << "X - Value: " << phi << points[i].x << points[i].y;
			i++;

	}
	vertexBuffer.create();
	vertexBuffer.setUsagePattern(QGLBuffer::StaticDraw);
	if (!vertexBuffer.bind()) {
		qWarning() << "Could not bind vertex buffer";
		return;
	}
	vertexBuffer.allocate(points, count * sizeof(VERTICES));
}


/*
 * render.h
 *
 *  Created on: 15.08.2012
 *      Author: msauer
 */

#ifndef RENDER_H_
#define RENDER_H_

#include <QGLWidget>
#include <QGLBuffer>
#include <QGLShaderProgram>
class RenderClass : public QGLWidget {

Q_OBJECT

public:
	RenderClass(const QGLFormat& format, QWidget *parent = 0);

protected:
	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();

private:
	void draw();
	void update();
	bool initShaderProgram(const QString& vertexShaderPath, const QString& fragmentShaderPath);
	void createSphere();
	QMatrix4x4 ModelMatrix;
	QMatrix4x4 ViewMatrix;
	QMatrix4x4 ProjectionMatrix;
	QMatrix4x4 MVP;

	QGLShaderProgram shader;
	QGLBuffer vertexBuffer;


};

#endif

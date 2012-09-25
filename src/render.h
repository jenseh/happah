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
#include <glm/glm.hpp>
#include "sphere.h"
class RenderClass : public QGLWidget {

Q_OBJECT

public:
	RenderClass(const QGLFormat& format, QWidget *parent = 0);

protected:
	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();

	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
private:
	void draw();
	void update();
	bool initShaderPrograms();
	void createUnitSphere(int dtheta,int dphi);
	void setZoom(float zoom);
	QMatrix4x4 ModelMatrix;
	QMatrix4x4 ViewMatrix;
	QMatrix4x4 ProjectionMatrix;
	QMatrix4x4 MVP;
	QVector3D eye,center,up;


	QGLShaderProgram shader,coordShader;
	QGLBuffer vertexBuffer,coordVBO,triangleVBO;
	std::vector<glm::vec4> coordSystem;
	std::vector<glm::vec4> sphereVP;
	glm::vec4 triangleVP[3];
	QPoint mousePos;

	int pointCount;
	Sphere * sphere;
	// camera parameters
	float zoomRad,theta,phi;
};

#endif

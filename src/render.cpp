/*
 * render.cpp
 *
 *  Created on: 15.08.2012
 *      Author: msauer
 */

#include <QtGui>
#include <QtOpenGL>
#include "render.h"

RenderClass::RenderClass(QWidget *parent) :
		QGLWidget(parent) {
	setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));

}

void RenderClass::initializeGL() {
	glShadeModel (GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable (GL_DEPTH_TEST);

}

void RenderClass::resizeGL(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat) width / (GLfloat) height, 0.1f, 20.0f);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

void RenderClass::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin (GL_QUADS);

	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);




	glVertex3f(-1.0f, 1.0f, 1.0f);

	glVertex3f(1.0f, 1.0f, 1.0f);

	glVertex3f(1.0f,-1.0f,1.0f);
	glEnd();
}


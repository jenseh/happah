/*
 * render.cpp
 *
 *  Created on: 15.08.2012
 *      Author: msauer
 */

#include <QtGui>
#include <QtOpenGL>


#include "render.h"



RenderClass::RenderClass(QWidget *parent) :QGLWidget(parent) {
	setFormat(QGLFormat(
			QGL::DoubleBuffer | QGL::DepthBuffer));

}





void RenderClass::initializeGL()
{

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClearDepth(1.0f);


}

void RenderClass::resizeGL(int width,int height)
{
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void RenderClass::paintGL(){
	draw();
}


void RenderClass::draw(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

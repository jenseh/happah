/*
 * render.h
 *
 *  Created on: 15.08.2012
 *      Author: msauer
 */

#ifndef RENDER_H_
#define RENDER_H_

// TODO : Create a Base Render Class

#include <QGLWidget>
#include <QWidget>

class RenderClass : public QGLWidget {
Q_OBJECT

// TODO: Set private functions

public:
	RenderClass(QWidget *parent = 0);

protected:
	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();
};

#endif

/*
 * render.h
 *
 *  Created on: 15.08.2012
 *      Author: msauer
 */

#ifndef RENDER_H_
#define RENDER_H_

#include <QGLWidget>

class RenderClass : public QGLWidget {

Q_OBJECT

public:
	RenderClass(QWidget *parent = 0);


protected:
	void initializeGL();
	void resizeGL(int width,int height);
	void paintGL();


private:
	void draw();




};

#endif

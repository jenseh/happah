#ifndef GLVIEWPORT3D_H_
#define GLVIEWPORT3D_H_

#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <QGLWidget>
#include <QGLBuffer>
#include <QGLShaderProgram>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <QFlags>
#include <QtGui>
#include <QGLBuffer>
#include <cmath>
#include <iostream>

#include "happah/math/Ray.h"
#include "happah/gui/DrawManager.h"
#include "happah/gui/MainWindow.h"
#include "happah/scene/SceneManager.h"
#include "happah/gui/Viewport3DListener.h"

using namespace std;

class Viewport3D: public QGLWidget {

public:
    Viewport3D(Viewport3DListener& viewport3DListener, DrawManager& drawManager, QWidget* parent = 0);

protected:
	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
	void keyPressEvent(QKeyEvent *event);

private:
	Ray getMouseRay();
	void updateView();
	void setZoom(float zoom);

	QTimer *m_timer;
	DrawManager& m_drawManager;

	uint m_lastSceneState;
	hpmat4x4 m_viewMatrix;
	hpmat4x4 m_projectionMatrix;
	hpvec3 m_camera, m_center, m_up;
	QPoint m_mousePos;
	Viewport3DListener& m_viewport3DListener;
	float m_zoomRad, m_theta, m_phi; //is zoomRad german?

	const static int WAIT_TIME = 40;
};


#endif

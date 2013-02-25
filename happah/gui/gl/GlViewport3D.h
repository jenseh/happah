#ifndef GLVIEWPORT3D_H_
#define GLVIEWPORT3D_H_

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

#include "happah/gui/qt/MainWindow.h"
#include "happah/scene/SceneManager.h"
#include "happah/gui/gl/DrawManager.h"
#include "happah/gui/Picker.h"

using namespace std;

class GlViewport3D: public QGLWidget {

public:
    GlViewport3D(SceneManager* sceneManager, const QGLFormat& format, QWidget* parent = 0, MainWindow* mainWindow = 0);

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
	void updateView();
	bool initShaderPrograms();
	void setZoom(float zoom);

	QTimer *m_timer;
	MainWindow* m_mainWindow;
	SceneManager* m_sceneManager;
	DrawManager* m_drawManager;

	uint m_lastSceneState;
	QMatrix4x4 m_viewMatrix;
	QMatrix4x4 m_projectionMatrix;
	QVector3D m_camera, m_center, m_up;
	QGLBuffer m_vertexBuffer, m_coordVBO, m_triangleVBO;
	glm::vec4 m_triangleVP[3];
	QPoint m_mousePos;
	float m_zoomRad, m_theta, m_phi; //is zoomRad german?

	const static int WAIT_TIME = 40;
};

#endif

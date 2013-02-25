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

	QTimer *timer_;
	MainWindow* mainWindow_;
	SceneManager* m_sceneManager;
	DrawManager* m_drawManager;

	uint m_lastSceneState;
	QMatrix4x4 viewMatrix_;
	QMatrix4x4 projectionMatrix_;
	QVector3D eye_, center_, up_;
	QGLBuffer vertexBuffer_, coordVBO_, triangleVBO_;
	glm::vec4 triangleVP_[3];
	QPoint mousePos_;
	int pointCount_;
	float zoomRad_, theta_, phi_; //is zoomRad german?

	const static int WAIT_TIME = 40;
};

#endif

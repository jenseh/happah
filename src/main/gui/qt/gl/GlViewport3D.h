#ifndef GLVIEWPORT3D_H_
#define GLVIEWPORT3D_H_

#include <QGLWidget>
#include <QGLBuffer>
#include <QGLShaderProgram>
#include <glm/glm.hpp>
#include <vector>
#include <QFlags>
#include <QtGui>
#include <QGLBuffer>
#include <cmath>
#include <iostream>

#include "../../../MainWindow.h"
#include "../../../core/SceneManager.h"
#include "GlQuadMesh.h"
#include "GlTriangleMesh.h"

using namespace std;

class GlViewport3D: public QGLWidget {

public:
    GlViewport3D(SceneManager* sceneManager, const QGLFormat& format, QWidget* parent = 0,
            MainWindow* mainWindow = 0);

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
	QTimer *timer_;
	MainWindow* mainWindow_;
	SceneManager* sceneManager_;
	DrawManager* drawManager_;

	QMatrix4x4 viewMatrix_;
	QMatrix4x4 projectionMatrix_;
	QVector3D eye_, center_, up_;
	QGLShaderProgram shader_, coordShader_;
	QGLBuffer vertexBuffer_, coordVBO_, triangleVBO_;
	std::vector<glm::vec4> coordSystem_; //unused
	std::vector<glm::vec4> sphereVP_; //unused
	glm::vec4 triangleVP_[3];
	QPoint mousePos_;
	int pointCount_;
	float zoomRad_, theta_, phi_; //is zoomRad german?

	const static int WAIT_TIME = 40;

	void draw();
	void updateView();
	bool initShaderPrograms();
	void setZoom(float zoom);
};

#endif

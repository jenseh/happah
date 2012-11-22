#ifndef VpIEWPORT3D_H_
#define VIEWPORT3D_H_

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

#include "MainWindow.h"
#include "Sphere.h"
#include "Gear.h"
#include "Grid.h"
#include "GeometryObject.h"

using namespace std;

class Viewport3D: public QGLWidget {
Q_OBJECT
private:
    MainWindow* _mainWindow;

	QMatrix4x4 ViewMatrix;
	QMatrix4x4 ProjectionMatrix;
	QVector3D eye, center, up;
	QGLShaderProgram shader, coordShader;
	QGLBuffer vertexBuffer, coordVBO, triangleVBO;
	std::vector<glm::vec4> coordSystem;
	std::vector<glm::vec4> sphereVP;
	glm::vec4 triangleVP[3];
	QPoint mousePos;
	int pointCount;
    float zoomRad, theta, phi;

    // GeometryObjects
    vector<GeometryObject> *geometryObjects;
    Grid* grid;
    Sphere* sphere;
    Gear* gear1;
    Gear* gear2;

public:
    Viewport3D(const QGLFormat& format, QWidget* parent = 0, MainWindow* mainWindow = 0);

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
    QTimer *timer;
    const static int WAIT_TIME = 40;

    void draw();
    void updateView();
	bool initShaderPrograms();
	void setZoom(float zoom);

private slots:
    void update();
};

#endif

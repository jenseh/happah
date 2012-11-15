#ifndef VpIEWPORT3D_H_
#define VIEWPORT3D_H_

#include <QGLWidget>
#include <QGLBuffer>
#include <QGLShaderProgram>
#include <glm/glm.hpp>
#include <vector>

#include "sphere.h"
#include "Gear.h"
#include "GeometryObject.h"

using namespace std;

class Viewport3D: public QGLWidget {
Q_OBJECT
private:
	QMatrix4x4 _modelMatrix;
	QMatrix4x4 ViewMatrix;
	QMatrix4x4 ProjectionMatrix;
	QMatrix4x4 MVP,MV,normalMat;
	QVector3D eye, center, up;
	QGLShaderProgram shader, coordShader;
	QGLBuffer vertexBuffer, coordVBO, triangleVBO;
	std::vector<glm::vec4> coordSystem;
	std::vector<glm::vec4> sphereVP;
	glm::vec4 triangleVP[3];
	QPoint mousePos;
	int pointCount;
	Sphere* sphere;
    Gear* gear;
	float zoomRad, theta, phi;
	GeometryObject* gObject;

public:
	Viewport3D(const QGLFormat& format, QWidget* parent = 0);

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
	void setZoom(float zoom);
};

#endif

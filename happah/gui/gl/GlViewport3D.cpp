#include <GL/glew.h>
#include <GL/gl.h>

#include "happah/gui/gl/GlViewport3D.h"

GlViewport3D::GlViewport3D(DrawManager& drawManager, QWidget* parent)
	: QGLWidget(&(drawManager.getGlContext()), parent), m_drawManager(drawManager) {

	setFocusPolicy(Qt::ClickFocus); // for keyPressEvent

	m_projectionMatrix.setToIdentity();
	m_viewMatrix.setToIdentity();
	m_zoomRad = 5.0f;
	m_camera.setX(0.0f);
	m_camera.setY(0.0f);
	m_camera.setZ(m_zoomRad);
	m_center.setX(0.0f);
	m_center.setY(0.0f);
	m_center.setZ(0.0f);
	m_up.setX(0.0f);
	m_up.setY(m_zoomRad);
	m_up.setZ(0.0f);
	m_theta = 0;
	m_phi = 0;

}

void GlViewport3D::initializeGL() {
	// Setup and start a timer
	m_timer = new QTimer(this);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(updateGL()));
	m_timer->start(WAIT_TIME);

}

void GlViewport3D::resizeGL(int width, int height) {
	glViewport(0, 0, width, qMax(height, 1));
	float ratio = (float) width / (float) height;
	m_projectionMatrix.setToIdentity();
	m_projectionMatrix.perspective(45.0f, ratio, 0.1f, 100.0f);
}

void GlViewport3D::paintGL() {
	updateView();
	m_drawManager.draw(&m_projectionMatrix, &m_viewMatrix, &m_camera);
}

void GlViewport3D::updateView() {
	//Update ViewMatrix
	QMatrix4x4 LookatMatrix;
	LookatMatrix.lookAt(m_camera, m_center, m_up);
	m_viewMatrix = LookatMatrix;
}

void GlViewport3D::mouseMoveEvent(QMouseEvent *event) {

	int width = this->width();
	int height = this->height();

	float dx = (float) (event->x() - m_mousePos.x()) / width;
	float dy = (float) (event->y() - m_mousePos.y()) / height;

	QVector3D forward =m_center - m_camera;
	forward.normalize();
	forward *= m_zoomRad;
	QVector3D right = QVector3D::crossProduct(m_up, forward);
	right.normalize();
	right *= m_zoomRad;
	m_up.normalize();
	m_up *= m_zoomRad;

	QVector3D delta;

	if (event->buttons() == Qt::LeftButton) {
		m_theta = dx*M_PI;
		m_phi = dy*M_PI;

		m_camera = m_center - cos(m_theta) * forward + sin(m_theta) * right;
		// Recalc forward
		forward =m_center - m_camera;
		forward.normalize();
		forward *= m_zoomRad;

		m_camera = m_center - cos(m_phi) * forward + sin(m_phi) * m_up;
		// recalc up
		m_up = QVector3D::crossProduct(forward, right);
		m_up.normalize();
		m_up *= m_zoomRad;

		updateGL();
	} else if (event->buttons() == Qt::RightButton) {
		// Movement forward, backwards
		delta = forward * dy + right * dx;
		m_camera += delta;
		m_center += delta;
		updateGL();
	} else if (event->buttons() == Qt::MiddleButton ) {
		delta = m_up * dy;
		m_center += delta;
		m_camera += delta;
		updateGL();
	}
	m_mousePos = event->pos();

}
void GlViewport3D::mousePressEvent(QMouseEvent *event) {
	m_mousePos = event->pos();
}

void GlViewport3D::wheelEvent(QWheelEvent *event) {
	float degrees = event->delta() / 8;
	float steps = degrees / 15;

	m_zoomRad = m_zoomRad - steps;
	m_camera.setZ(m_zoomRad);
	updateGL();

}
// Picking to get Triangle Edges

//TODO: Adapt to new achitecture
void GlViewport3D::mouseDoubleClickEvent(QMouseEvent *event) {
	/*float x = (float) event->pos().x();
	float y = (float) event->pos().y();
	float width = (float) this->width();
	float height = (float) this->height();

	// Create 2World Matrix
	QMatrix4x4 VP = m_projectionMatrix * m_viewMatrix;
	float VPFloats[16];
	const qreal* VPQreals = VP.constData();
	glm::mat4 toWorld = glm::make_mat4(VPFloats);
	Picker* picker = new Picker();
	bool hit = picker->select(x, y, width, height, &toWorld, m_sceneManager);*/

}

void GlViewport3D::keyPressEvent(QKeyEvent* event) {}


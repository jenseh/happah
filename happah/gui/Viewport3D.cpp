#include <GL/glew.h>
#include <GL/gl.h>

#include "happah/gui/Viewport3D.h"

Viewport3D::Viewport3D(Viewport3DListener& viewport3DListener,DrawManager& drawManager, QWidget* parent)
	: QGLWidget(drawManager.getGlContext(), parent), m_viewport3DListener(viewport3DListener), m_drawManager(drawManager) {

	setFocusPolicy(Qt::ClickFocus); // for keyPressEvent

	m_projectionMatrix = hpmat4x4(1.0);
	m_viewMatrix = hpmat4x4(1.0);
	m_zoomRad = 5.0f;

	m_camera.x = 0.0;
	m_camera.y = 0.0;
	m_camera.z = m_zoomRad;

	m_center.x = 0.0;
	m_center.y = 0.0;
	m_center.z = 0.0;
	m_up.x = 0.0;
	m_up.y = m_zoomRad;
	m_up.z = 0.0;

	m_theta = 0;
	m_phi = 0;

}

Ray Viewport3D::getMouseRay() {
	hpvec3 winPos;
	winPos.x = m_mousePos.x();
	winPos.y = height() - m_mousePos.y(); // Because screen coordinates on the top not the bottom
	glReadPixels(m_mousePos.x(), m_mousePos.y(), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winPos.z);
	//winPos.z = 1.0; // Touching the "far plane"
	hpvec4 viewport(0, 0, width(), height());
	hpvec3 point = glm::unProject(winPos, m_viewMatrix, m_projectionMatrix, viewport );
	return Ray(m_camera, point - m_camera);
}

void Viewport3D::initializeGL() {
	// Setup and start a timer
	m_timer = new QTimer(this);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(updateGL()));
	m_timer->start(WAIT_TIME);

}

void Viewport3D::resizeGL(int width, int height) {
	glViewport(0, 0, width, qMax(height, 1));
	float ratio = (float) width / (float) height;
	m_projectionMatrix = glm::perspective(45.0f, ratio, 0.1f, 100.0f);
}

void Viewport3D::paintGL() {
	updateView();

	m_drawManager.draw(m_projectionMatrix, m_viewMatrix, m_camera);
}

void Viewport3D::updateView() {
	m_viewMatrix =glm::lookAt(m_camera, m_center, m_up);
}

void Viewport3D::mouseMoveEvent(QMouseEvent *event) {

	int width = this->width();
	int height = this->height();

	float dx = (float) (event->x() - m_mousePos.x()) / width;
	float dy = (float) (event->y() - m_mousePos.y()) / height;

	hpvec3 forward =m_center - m_camera;
	forward = glm::normalize(forward);
	forward *= m_zoomRad;
	hpvec3 right = glm::cross(m_up, forward);
	right = glm::normalize(right);
	right *= m_zoomRad;
	m_up = glm::normalize(m_up);
	m_up *= m_zoomRad;

	hpvec3 delta;

	if (event->buttons() == Qt::LeftButton) {
		m_theta = dx*M_PI;
		m_phi = dy*M_PI;

		m_camera = m_center - cos(m_theta) * forward + sin(m_theta) * right;
		// Recalc forward
		forward =m_center - m_camera;
		forward = glm::normalize(forward);
		forward *= m_zoomRad;

		m_camera = m_center - cos(m_phi) * forward + sin(m_phi) * m_up;
		// recalc up
		m_up = glm::cross(forward, right);
		m_up = glm::normalize(m_up);
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
void Viewport3D::mousePressEvent(QMouseEvent *event) {
	m_mousePos = event->pos();
	Ray ray(getMouseRay());
	m_viewport3DListener.handleMouseClickEvent(ray);
}

void Viewport3D::wheelEvent(QWheelEvent *event) {
	float degrees = event->delta() / 8;
	float steps = degrees / 15;

	m_zoomRad = m_zoomRad - steps;
	m_camera.z = m_zoomRad;
	updateGL();

}
// Picking to get Triangle Edges

//TODO: Adapt to new achitecture
void Viewport3D::mouseDoubleClickEvent(QMouseEvent *event) {
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

void Viewport3D::keyPressEvent(QKeyEvent* event) {}


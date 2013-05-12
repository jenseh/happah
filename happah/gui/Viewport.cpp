#include <GL/glew.h>
#include <GL/gl.h>

#include "happah/gui/Viewport.h"

Viewport::Viewport(ViewportListener& viewportListener, DrawManager& drawManager, QWidget* parent)
	: QGLWidget(drawManager.getGlContext(), parent),
	  m_viewportListener(viewportListener),
	  m_drawManager(drawManager),
	  m_draggingActive(false),
	  DISTANCE_TO_CENTER(5.0) {

    if(!m_drawManager.isGLInitialized())
    {
        m_drawManager.init(this);
    }

	setFocusPolicy(Qt::ClickFocus); // for keyPressEvent

	m_projectionMatrix = hpmat4x4(1.0);
	m_viewMatrix = hpmat4x4(1.0);

	m_camera.x = 0.0;
	m_camera.y = 0.0;
	m_camera.z = DISTANCE_TO_CENTER;

	m_center.x = 0.0;
	m_center.y = 0.0;
	m_center.z = 0.0;
	m_up.x = 0.0;
	m_up.y = DISTANCE_TO_CENTER;
	m_up.z = 0.0;

	m_theta = 0;
	m_phi = 0;
}

Ray Viewport::getMouseRay() {
	hpvec3 winPos;
	winPos.x = m_mousePos.x();
	winPos.y = height() - m_mousePos.y(); // Because screen coordinates on the top not the bottom
	glReadPixels(m_mousePos.x(), m_mousePos.y(), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winPos.z);
	//winPos.z = 1.0; // Touching the "far plane"
	hpvec4 viewport(0, 0, width(), height());
	hpvec3 point = glm::unProject(winPos, m_viewMatrix, m_projectionMatrix, viewport );
	return Ray(m_camera, point - m_camera);
}

void Viewport::initializeGL() {
	// Setup and start a timer
	m_timer = new QTimer(this);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(updateGL()));
	m_timer->start(WAIT_TIME);

}

void Viewport::resizeGL(int width, int height) {
	glViewport(0, 0, width, qMax(height, 1));
	float ratio = (float) width / (float) height;
	m_projectionMatrix = glm::perspective(45.0f, ratio, 0.1f, 100.0f);
	m_drawManager.resizeSelectorTexture();

}

void Viewport::paintGL() {
	updateView();

	m_drawManager.draw(m_projectionMatrix, m_viewMatrix, m_camera);

}

void Viewport::updateView() {
	m_viewMatrix =glm::lookAt(m_camera, m_center, m_up);
}

void Viewport::mouseMoveEvent(QMouseEvent *event) {

	if(m_draggingActive) {
		qApp->setOverrideCursor( QCursor( Qt::ClosedHandCursor ) );
		Ray ray(getMouseRay());
		m_viewportListener.handleDragEvent(ray);
	} else {

		int width = this->width();
		int height = this->height();

		float dx = (float) (event->x() - m_mousePos.x()) / width;
		float dy = (float) (event->y() - m_mousePos.y()) / height;

		hpvec3 forward =m_center - m_camera;
		forward = glm::normalize(forward);
		forward *= DISTANCE_TO_CENTER;
		hpvec3 right = glm::cross(m_up, forward);
		right = glm::normalize(right);
		right *= DISTANCE_TO_CENTER;
		m_up = glm::normalize(m_up);
		m_up *= DISTANCE_TO_CENTER;

		hpvec3 delta;

		if (event->buttons() == Qt::LeftButton) {
			if(!m_drawManager.isSomethingSelected()){
				// Left turn arround center
				m_theta = dx*M_PI;
				m_phi = dy*M_PI;

				m_camera = m_center - cos(m_theta) * forward + sin(m_theta) * right;
				// Recalc forward
				forward =m_center - m_camera;
				forward = glm::normalize(forward);
				forward *= DISTANCE_TO_CENTER;

				m_camera = m_center - cos(m_phi) * forward + sin(m_phi) * m_up;
				// recalc up
				m_up = glm::cross(forward, right);
				m_up = glm::normalize(m_up);
				m_up *= DISTANCE_TO_CENTER;
			}
			updateGL();
		} else if (event->buttons() == Qt::RightButton) {
			// Move left right up down
			delta = m_up * dy + right * dx;
			m_camera += delta;
			m_center += delta;
			updateGL();
		}
	}
	m_mousePos = event->pos();
}

void Viewport::mousePressEvent(QMouseEvent *event) {
	if(!m_draggingActive) {
		m_mousePos = event->pos();
		Ray ray(getMouseRay());
		if(m_drawManager.select(event->x(), event->y()))
			m_draggingActive = true;
		else
			m_viewportListener.handleMouseClickEvent(ray);
	}
}

void Viewport::mouseReleaseEvent(QMouseEvent *event){
	if(m_draggingActive) {
		m_draggingActive = false;
		qApp->setOverrideCursor( QCursor( Qt::ArrowCursor ) );
	}
}

void Viewport::wheelEvent(QWheelEvent *event) {
	hpvec3 forward =m_center - m_camera;
	forward = glm::normalize(forward);
	forward *= DISTANCE_TO_CENTER * event->delta() * 0.001;
	m_camera += forward;
	m_center += forward;
	updateGL();

}
// Picking to get Triangle Edges

//TODO: Adapt to new achitecture
void Viewport::mouseDoubleClickEvent(QMouseEvent *event) {
	m_mousePos = event->pos();

}

void Viewport::keyPressEvent(QKeyEvent* event) {}


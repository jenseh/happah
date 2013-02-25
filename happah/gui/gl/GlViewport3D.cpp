#include <GL/glew.h>
#include <GL/gl.h>

#include "happah/gui/gl/GlViewport3D.h"

GlViewport3D::GlViewport3D(SceneManager* sceneManager, const QGLFormat& format,
		QWidget *parent, MainWindow* mainWindow) :
		QGLWidget(format, parent), m_vertexBuffer(QGLBuffer::VertexBuffer), m_coordVBO(
				QGLBuffer::VertexBuffer), m_triangleVBO(QGLBuffer::VertexBuffer) {

	setFocusPolicy(Qt::ClickFocus); // for keyPresEvent

	m_mainWindow = mainWindow;
	m_sceneManager = sceneManager;
	m_drawManager = new DrawManager(m_sceneManager);

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
	QGLFormat glFormat = QGLWidget::format();
	if (!glFormat.sampleBuffers())
		qWarning() << "Could not enable sample buffers";
	GLenum err = glewInit();


	if (GLEW_OK != err)
	{
	  /* Problem: glewInit failed, something is seriously wrong. */
	  fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}

	if (!m_drawManager->initGL()) {
		return;
	}

	// Setup and start a timer
	m_timer = new QTimer(this);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(updateGL()));
	m_timer->start(WAIT_TIME);

}

void GlViewport3D::resizeGL(int width, int height) {
	glViewport(0, 0, width, qMax(height, 1));
	float ratio = (float) width / (float) height;
	m_projectionMatrix.perspective(45.0f, ratio, 0.1f, 100.0f);
}

void GlViewport3D::paintGL() {
	updateView();
	m_drawManager->draw(&m_projectionMatrix, &m_viewMatrix, &m_camera);
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
	float x = (float) event->pos().x();
	float y = (float) event->pos().y();
	float width = (float) this->width();
	float height = (float) this->height();

	// Create 2World Matrix
	QMatrix4x4 VP = m_projectionMatrix * m_viewMatrix;
	float VPFloats[16];
	const qreal* VPQreals = VP.constData();
	glm::mat4 toWorld = glm::make_mat4(VPFloats);
	Picker* picker = new Picker();
	bool hit = picker->select(x, y, width, height, &toWorld, m_sceneManager);

}

void GlViewport3D::keyPressEvent(QKeyEvent *event) {
	// Do something
}

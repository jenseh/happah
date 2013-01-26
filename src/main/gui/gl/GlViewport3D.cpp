#define GLEW_STATIC //Very important for Windows users
#include <GL/glew.h>
#include <GL/gl.h>

#include "GlViewport3D.h"

GlViewport3D::GlViewport3D(SceneManager* sceneManager, const QGLFormat& format,
		QWidget *parent, MainWindow* mainWindow) :
		QGLWidget(format, parent), vertexBuffer_(QGLBuffer::VertexBuffer), coordVBO_(
				QGLBuffer::VertexBuffer), triangleVBO_(QGLBuffer::VertexBuffer) {


    setFocusPolicy(Qt::ClickFocus); // for keyPresEvent

	mainWindow_ = mainWindow;
	m_sceneManager = sceneManager;

	projectionMatrix_.setToIdentity();
	viewMatrix_.setToIdentity();
	zoomRad_ = 5.0f;
	eye_.setX(0.0f);
	eye_.setY(0.0f);
	eye_.setZ(zoomRad_);
	center_.setX(0.0f);
	center_.setY(0.0f);
	center_.setZ(0.0f);
	up_.setX(0.0f);
	up_.setY(1.0f);
	up_.setZ(0.0f);
	pointCount_ = 0;
	theta_ = 0;
	phi_ = 0;
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
	//Create DrawManager
	m_drawManager = new DrawManager();

	// Initialize shaders
	if (!m_drawManager->initShaderPrograms()) {
		return;
	}

	// Finalize vertex buffer
//    if (!m_drawManager->createBufferFor() {
//	    return;
//	}
	// Setup and start a timer
	timer_ = new QTimer(this);
	connect(timer_, SIGNAL(timeout()), this, SLOT(updateGL()));
	timer_->start(WAIT_TIME);
}

void GlViewport3D::resizeGL(int width, int height) {
	glViewport(0, 0, width, qMax(height, 1));
	float ratio = (float) width / (float) height;
	projectionMatrix_.perspective(45.0f, ratio, 0.1f, 100.0f);
}

void GlViewport3D::paintGL() {
	updateView();

	vector<Drawable*>* drawables = m_sceneManager->getDrawables();
	m_drawManager->draw(drawables, &projectionMatrix_, &viewMatrix_, &eye_);
}

void GlViewport3D::updateView() {
	//Update ViewMatrix
	QMatrix4x4 LookatMatrix;
	LookatMatrix.lookAt(eye_, center_, up_);
	viewMatrix_ = LookatMatrix;
}

void GlViewport3D::mouseMoveEvent(QMouseEvent *event) {

	int width = this->width();
	int height = this->height();
	float stepSize = 150.0f;

	float dx = (float) (event->x() - mousePos_.x()) / width;
	float dy = (float) (event->y() - mousePos_.y()) / height;

	if (event->buttons() == Qt::RightButton) {

		if (theta_ < 360) {
			theta_ = theta_ + (stepSize * dx);
		} else
			theta_ = 0;
		if (phi_ < 360) {
			phi_ = phi_ + (stepSize * dy);
		} else
			phi_ = 0;
		float thetaRad = theta_ * M_PI / 180;
		float phiRad = phi_ * M_PI / 180;

		eye_.setX(zoomRad_ * (sin(thetaRad) * cos(phiRad))); //- sin(dx)*cos(dy)));
		eye_.setY(zoomRad_ * (sin(thetaRad) * sin(phiRad))); //+ sin(dx)*cos (dy)));
		eye_.setZ(zoomRad_ * (cos(thetaRad))); //*cos(dy)));

		updateView();
		updateGL();
	}

	mousePos_ = event->pos();

}
void GlViewport3D::mousePressEvent(QMouseEvent *event) {
	if (event->buttons() == Qt::LeftButton) {
		// do something
	} else if (event->buttons() == Qt::RightButton) {
		mousePos_ = event->pos();
	}
}

void GlViewport3D::wheelEvent(QWheelEvent *event) {
	float degrees = event->delta() / 8;
	float steps = degrees / 15;

	zoomRad_ = zoomRad_ - steps;
	updateGL();

}
// Picking to get Triangle Edges

//TODO: Adapt to new achitecture
void GlViewport3D::mouseDoubleClickEvent(QMouseEvent *event) {

//	float x = (float) event->pos().x();
//	float y = (float) event->pos().y();
//	float width = (float) this->width();
//	float height = (float) this->height();

//	glm::vec3 lookAt, camPos, camUp, view, h, v;
//	lookAt = glm::vec3(center_.x(), center_.y(), center_.z()); // TODO : Change that when lookat might move later
//	camPos.x = eye_.x();
//	camPos.y = eye_.y();
//	camPos.z = eye_.z();
//	camUp = glm::vec3(up_.x(), up_.y(), up_.z());

//	// Calc Camera Plane
//	view = lookAt - camPos;
//	glm::normalize(view);
//	h = glm::cross(view, camUp);
//	glm::normalize(h);
//	v = glm::cross(h, view);
//	glm::normalize(v);

//	// scale h,v
//	float fovy = 45.0; // TODO : Get this from Global
//	float fovyRad = fovy * M_PI / 180;
//	float vLength = tan(fovyRad / 2) * 0.1f; // TODO 0.1f is near Clipping plane .. get that from Global
//	float hLength = vLength * (width / height);

//	v = v * vLength;
//	h = h * hLength;

//	// translate mouse coordinates to viewport
//	x = x - width / 2;
//	y = y - height / 2;
//	x = x / (width / 2);
//	y = y / (height / 2);

//	glm::vec3 rayPos, rayDir;

//	glm::vec3 hx = (float) x * h;
//	glm::vec3 vy = (float) y * v;

//	// Create Ray
//	// TODO Create RayStruct or even Class
//	rayPos = camPos + (0.1f * view) + hx + vy;

//	//qWarning()<< rayPos.x << "   "<<rayPos.y<<"  "<<rayPos.z;
//	rayDir = rayPos - camPos;

//	if (sphere_->hit(rayPos, rayDir)) {

//		qWarning() << sphere_->getHitpoint().x << " "
//				<< sphere_->getHitpoint().y << " " << sphere_->getHitpoint().z;

//		if (pointCount_ < 3) {
//			triangleVP_[pointCount_] = glm::vec4(sphere_->getHitpoint(), 1.0f);
//			pointCount_++;

//		} else {
//			pointCount_ = 0;
//			triangleVP_[pointCount_] = glm::vec4(sphere_->getHitpoint(), 1.0f);
//			pointCount_++;

//		}
//		//	triangleVBO_.write(0, triangleVP_, 3);
//	}
}

void GlViewport3D::keyPressEvent(QKeyEvent *event) {
	cout << "Key: " << event->key() << endl;
}

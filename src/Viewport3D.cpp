#include "Viewport3D.h"

Viewport3D::Viewport3D(const QGLFormat& format, QWidget *parent,
		MainWindow* mainWindow) :
		QGLWidget(format, parent), vertexBuffer_(QGLBuffer::VertexBuffer), coordVBO_(
				QGLBuffer::VertexBuffer), triangleVBO_(QGLBuffer::VertexBuffer) {

	mainWindow_ = mainWindow;

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

void Viewport3D::initializeGL() {
	QGLFormat glFormat = QGLWidget::format();
	if (!glFormat.sampleBuffers())
		qWarning() << "Could not enable sample buffers";

	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glClearDepth(1.0f);
	glEnable (GL_DEPTH_TEST);

	if (!initShaderPrograms())
		return;

	// Initialize your Geometry Objects here

	// Grid
    grid_ = new Grid();
    sphere_ = new Sphere(1.0f);
    gear1_ = new Gear(1.0f, 1.0f, 20, 0.2f);
    gear2_ = new Gear(0.5f, 1.0f, 10, 0.6f);

    grid_->init();
    sphere_->init();
    gear1_->init();
    gear2_->init();

    gear2_->rotate(40.0f, 0.0f, 0.0f, 1.0f);
	gear2_->translate(1.9f, 0.0f, 0.0f);


	// Grid
	grid_->createVertexData();
	grid_->initVertexBuffer(QGLBuffer::StaticDraw);
	grid_->fillVertexBuffer();

	// Sphere
	sphere_->createVertexData();
	sphere_->initVertexBuffer(QGLBuffer::StaticDraw);
	sphere_->fillVertexBuffer();

	// Gear
	gear1_->createVertexData();
	gear1_->initVertexBuffer(QGLBuffer::StaticDraw);
	gear1_->fillVertexBuffer();

	gear2_->createVertexData();
	gear2_->initVertexBuffer(QGLBuffer::StaticDraw);
	gear2_->fillVertexBuffer();

	// TODO: Why does this not work?Because grids , spheres and gears are not geometry objects they just inherit it
    geometryObjects_ = vector<GeometryObject*>();
    geometryObjects_.push_back(grid_);
    geometryObjects_.push_back(sphere_);
    geometryObjects_.push_back(gear1_);
    geometryObjects_.push_back(gear2_);

    for (unsigned int i = 0; i < geometryObjects_.size(); i++) {
        mainWindow_->getComponentContainer()->addComponent(geometryObjects_[i]);
    }

    sphere_->setText("Sphere");
	grid_->setText("Grid");
    gear1_->setText("Gear 1");
    gear2_->setText("Gear 2");

    // Setup and start a timer for the simulation
	timer_ = new QTimer(this);
    connect(timer_, SIGNAL(timeout()), this, SLOT(act()));
    timer_->start(ACT_WAIT_TIME);

    // Setup and start a timer for the drawing
    connect(timer_, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer_->start(DRAW_WAIT_TIME);
}

void Viewport3D::resizeGL(int width, int height) {
	glViewport(0, 0, width, qMax(height, 1));
	float ratio = (float) width / (float) height;
    projectionMatrix_.perspective(45.0f, ratio, 0.1f, 100.0f);
}

void Viewport3D::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Recompute view matrix
    updateView();

    // Draw grid
    grid_->draw(&coordShader_, &projectionMatrix_, &viewMatrix_, &eye_);

    // Draw sphere
    sphere_->draw(&shader_, &projectionMatrix_, &viewMatrix_, &eye_);

    // Draw gears
    gear1_->draw(&shader_, &projectionMatrix_, &viewMatrix_, &eye_);
    gear2_->draw(&shader_, &projectionMatrix_, &viewMatrix_, &eye_);
}

bool Viewport3D::initShaderPrograms() {
	//load and compile Vertex Shader
	bool result = shader_.addShaderFromSourceFile(QGLShader::Vertex,
			"./src/shader/blinnphongVert.glsl");
	if (!result)
		qWarning() << shader_.log();

	//load and compile Fragment Shader
	result = shader_.addShaderFromSourceFile(QGLShader::Fragment,
			"./src/shader/blinnphongFrag.glsl");
	if (!result)
		qWarning() << shader_.log();

	//coord Shader
	result = coordShader_.addShaderFromSourceFile(QGLShader::Vertex,
			"./src/shader/simpleVert.glsl");
	if (!result)
		qWarning() << coordShader_.log();

	//coord Shader
	result = coordShader_.addShaderFromSourceFile(QGLShader::Fragment,
			"./src/shader/simpleFrag.glsl");
	if (!result)
		qWarning() << coordShader_.log();

	return result;
}

// use this method for animations (model modification + draw updates
void Viewport3D::act() {
	// modify the model
	gear1_->rotate(1.0f, 0.0f, 0.0f, 1.0f);
    gear2_->rotate(-2.0f, 0.0f, 0.0f, 1.0f);
}

void Viewport3D::updateView() {
	//Update ViewMatrix
	QMatrix4x4 LookatMatrix;
	LookatMatrix.lookAt(eye_, center_, up_);
    viewMatrix_ = LookatMatrix;
}

void Viewport3D::mouseMoveEvent(QMouseEvent *event) {

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

		updateGL();
	}

	mousePos_ = event->pos();

}
void Viewport3D::mousePressEvent(QMouseEvent *event) {
	if (event->buttons() == Qt::LeftButton) {
		// do something
	} else if (event->buttons() == Qt::RightButton) {
		mousePos_ = event->pos();
	}
}

void Viewport3D::wheelEvent(QWheelEvent *event) {
	float degrees = event->delta() / 8;
	float steps = degrees / 15;

	zoomRad_ = zoomRad_ - steps;
	updateGL();

}
// Picking to get Triangle Edges
// TODO: Split that whole stuff up;
void Viewport3D::mouseDoubleClickEvent(QMouseEvent *event) {

	float x = (float) event->pos().x();
	float y = (float) event->pos().y();
	float width = (float) this->width();
	float height = (float) this->height();

	glm::vec3 lookAt, camPos, camUp, view, h, v;
	lookAt = glm::vec3(center_.x(), center_.y(), center_.z()); // TODO : Change that when lookat might move later
	camPos.x = eye_.x();
	camPos.y = eye_.y();
	camPos.z = eye_.z();
	camUp = glm::vec3(up_.x(), up_.y(), up_.z());

	// Calc Camera Plane
	view = lookAt - camPos;
	glm::normalize(view);
	h = glm::cross(view, camUp);
	glm::normalize(h);
	v = glm::cross(h, view);
	glm::normalize(v);

	// scale h,v
	float fovy = 45.0; // TODO : Get this from Global
	float fovyRad = fovy * M_PI / 180;
	float vLength = tan(fovyRad / 2) * 0.1f; // TODO 0.1f is near Clipping plane .. get that from Global
	float hLength = vLength * (width / height);

	v = v * vLength;
	h = h * hLength;

	// translate mouse coordinates to viewport
	x = x - width / 2;
	y = y - height / 2;
	x = x / (width / 2);
	y = y / (height / 2);

	glm::vec3 rayPos, rayDir;

	glm::vec3 hx = (float) x * h;
	glm::vec3 vy = (float) y * v;

	// Create Ray
	// TODO Create RayStruct or even Class
	rayPos = camPos + (0.1f * view) + hx + vy;

	//qWarning()<< rayPos.x << "   "<<rayPos.y<<"  "<<rayPos.z;
	rayDir = rayPos - camPos;

	if (sphere_->hit(rayPos, rayDir)) {

		qWarning() << sphere_->getHitpoint().x << " "
				<< sphere_->getHitpoint().y << " " << sphere_->getHitpoint().z;

		if (pointCount_ < 3) {
			triangleVP_[pointCount_] = glm::vec4(sphere_->getHitpoint(), 1.0f);
			pointCount_++;

		} else {
			pointCount_ = 0;
			triangleVP_[pointCount_] = glm::vec4(sphere_->getHitpoint(), 1.0f);
			pointCount_++;

		}
		//	triangleVBO_.write(0, triangleVP_, 3);
	}
}

void Viewport3D::keyPressEvent(QKeyEvent *event) {
	// TODO: Why does this not work?
	cout << "Key: " << event->key() << endl;
}

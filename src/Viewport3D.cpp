#include "Viewport3D.h"

Viewport3D::Viewport3D(const QGLFormat& format, QWidget *parent,
		MainWindow* mainWindow) :
		QGLWidget(format, parent), vertexBuffer(QGLBuffer::VertexBuffer), coordVBO(
				QGLBuffer::VertexBuffer), triangleVBO(QGLBuffer::VertexBuffer) {

	_mainWindow = mainWindow;

	ProjectionMatrix.setToIdentity();
	ViewMatrix.setToIdentity();
	zoomRad = 5.0f;
	eye.setX(0.0f);
	eye.setY(0.0f);
	eye.setZ(zoomRad);
	center.setX(0.0f);
	center.setY(0.0f);
	center.setZ(0.0f);
	up.setX(0.0f);
	up.setY(1.0f);
	up.setZ(0.0f);
	pointCount = 0;
	theta = 0;
	phi = 0;
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
	grid = new Grid(&ProjectionMatrix, &ViewMatrix, &eye);
	sphere = new Sphere(1.0f, &ProjectionMatrix, &ViewMatrix, &eye);
	gear1 = new Gear(1.0f, 1.0f, 20, 0.2f, &ProjectionMatrix, &ViewMatrix,
			&eye); // 1 * 3.14 / 20
	gear2 = new Gear(0.5f, 1.0f, 10, 0.6f, &ProjectionMatrix, &ViewMatrix,
			&eye); // 0.25

	grid->init(/*ProjectionMatrix, ViewMatrix*/);
	sphere->init(/*ProjectionMatrix, ViewMatrix*/);
	gear1->init(/*ProjectionMatrix, ViewMatrix*/);
	gear2->init(/*ProjectionMatrix, ViewMatrix*/);

	gear2->translate(1.9f, 0.0f, 0.0f);
	gear2->rotate(40.0f, 0.0f, 0.0f, 1.0f);

	// Grid
	grid->createVertexData();
	grid->initVertexBuffer(QGLBuffer::StaticDraw);
	grid->fillVertexBuffer();

	// Sphere
	sphere->createVertexData();
	sphere->initVertexBuffer(QGLBuffer::StaticDraw);
	sphere->fillVertexBuffer();

	// Gear
	gear1->createVertexData();
	gear1->initVertexBuffer(QGLBuffer::StaticDraw);
	gear1->fillVertexBuffer();

	gear2->createVertexData();
	gear2->initVertexBuffer(QGLBuffer::StaticDraw);
	gear2->fillVertexBuffer();

	// TODO: Why does this not work?Because grids , spheres and gears are not geometry objects they just inherit it
//    geometryObjects = new vector<GeometryObject>();
//    geometryObjects->push_back((GeometryObject) *grid);
//    geometryObjects->push_back((GeometryObject) *sphere);
//    geometryObjects->push_back((GeometryObject) *gear1);
//    geometryObjects->push_back((GeometryObject) *gear2);

	_mainWindow->getComponentContainer()->addComponent(gear1);
	gear1->setText("Gear 1");
	_mainWindow->getComponentContainer()->addComponent(gear2);
	gear2->setText("Gear 2");
	_mainWindow->getComponentContainer()->addComponent(sphere);
	sphere->setText("Sphere");
	_mainWindow->getComponentContainer()->addComponent(grid);
	grid->setText("Grid");

	// Setup and start a timer
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(WAIT_TIME);
}

void Viewport3D::resizeGL(int width, int height) {
	glViewport(0, 0, width, qMax(height, 1));
	float ratio = (float) width / (float) height;
	ProjectionMatrix.perspective(45.0f, ratio, 0.1f, 100.0f);
	/*
	 grid->updateProjectionMatrix(ProjectionMatrix);
	 sphere->updateProjectionMatrix(ProjectionMatrix);
	 gear1->updateProjectionMatrix(ProjectionMatrix);
	 gear2->updateProjectionMatrix(ProjectionMatrix);
	 */
}

void Viewport3D::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	updateView();

	draw();
}

bool Viewport3D::initShaderPrograms() {
	//load and compile Vertex Shader
	bool result = shader.addShaderFromSourceFile(QGLShader::Vertex,
			"./src/shader/blinnphongVert.glsl");
	if (!result)
		qWarning() << shader.log();

	//load and compile Fragment Shader
	result = shader.addShaderFromSourceFile(QGLShader::Fragment,
			"./src/shader/blinnphongFrag.glsl");
	if (!result)
		qWarning() << shader.log();

	//coord Shader
	result = coordShader.addShaderFromSourceFile(QGLShader::Vertex,
			"./src/shader/simpleVert.glsl");
	if (!result)
		qWarning() << shader.log();

	//coord Shader
	result = coordShader.addShaderFromSourceFile(QGLShader::Fragment,
			"./src/shader/simpleFrag.glsl");
	if (!result)
		qWarning() << shader.log();

	return result;
}

void Viewport3D::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw grid
	grid->draw(&coordShader);

	// Draw sphere
	sphere->draw(&shader);

	// Draw gears
	gear1->draw(&shader);
	gear2->draw(&shader);
}

// use this method for animations (model modification + draw updates
void Viewport3D::update() {
	// modify the model
	gear1->rotate(1.0f, 0.0f, 0.0f, 1.0f);
	gear2->rotate(-2.0f, 0.0f, 0.0f, 1.0f);

	// draw the scene again
	updateGL();
}

void Viewport3D::updateView() {
	//Update ViewMatrix
	QMatrix4x4 LookatMatrix;
	LookatMatrix.lookAt(eye, center, up);
	ViewMatrix = LookatMatrix;

	// Update MV and MVP
//    for (unigned int i = 0; i < geometryObjects->size(); i++)
//    {
//        geometryObjects[i]->updateView(ViewMatrix, eye);
//    }

	gear1->updateViewMatrix();
	gear2->updateViewMatrix();
	sphere->updateViewMatrix();
	grid->updateViewMatrix();
}

void Viewport3D::mouseMoveEvent(QMouseEvent *event) {

	int width = this->width();
	int height = this->height();
	float stepSize = 150.0f;

	float dx = (float) (event->x() - mousePos.x()) / width;
	float dy = (float) (event->y() - mousePos.y()) / height;

	if (event->buttons() == Qt::RightButton) {

		if (theta < 360) {
			theta = theta + (stepSize * dx);
		} else
			theta = 0;
		if (phi < 360) {
			phi = phi + (stepSize * dy);
		} else
			phi = 0;
		float thetaRad = theta * M_PI / 180;
		float phiRad = phi * M_PI / 180;

		eye.setX(zoomRad * (sin(thetaRad) * cos(phiRad))); //- sin(dx)*cos(dy)));
		eye.setY(zoomRad * (sin(thetaRad) * sin(phiRad))); //+ sin(dx)*cos (dy)));
		eye.setZ(zoomRad * (cos(thetaRad))); //*cos(dy)));

		updateView();
		updateGL();
	}

	mousePos = event->pos();

}
void Viewport3D::mousePressEvent(QMouseEvent *event) {
	if (event->buttons() == Qt::LeftButton) {
		// do something
	} else if (event->buttons() == Qt::RightButton) {
		mousePos = event->pos();
	}
}

void Viewport3D::wheelEvent(QWheelEvent *event) {
	float degrees = event->delta() / 8;
	float steps = degrees / 15;

	zoomRad = zoomRad - steps;
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
	lookAt = glm::vec3(center.x(), center.y(), center.z()); // TODO : Change that when lookat might move later
	camPos.x = eye.x();
	camPos.y = eye.y();
	camPos.z = eye.z();
	camUp = glm::vec3(up.x(), up.y(), up.z());

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

	if (sphere->hit(rayPos, rayDir)) {

		qWarning() << sphere->getHitpoint().x << " " << sphere->getHitpoint().y
				<< " " << sphere->getHitpoint().z;

		if (pointCount < 3) {
			triangleVP[pointCount] = glm::vec4(sphere->getHitpoint(), 1.0f);
			pointCount++;

		} else {
			pointCount = 0;
			triangleVP[pointCount] = glm::vec4(sphere->getHitpoint(), 1.0f);
			pointCount++;

		}
		//	triangleVBO.write(0,triangleVP,3);
	}
}

void Viewport3D::keyPressEvent(QKeyEvent *event) {
	// TODO: Why does this not work?
	cout << "Key: " << event->key() << endl;
}

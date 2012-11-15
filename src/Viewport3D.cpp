#include <QFlags>
#include <QtGui>
#include <QGLBuffer>
#include <cmath>

#include "Viewport3D.h"

Viewport3D::Viewport3D(const QGLFormat& format, QWidget *parent) :
		QGLWidget(format, parent), vertexBuffer(QGLBuffer::VertexBuffer), coordVBO(
				QGLBuffer::VertexBuffer),
				triangleVBO(QGLBuffer::VertexBuffer){

	ProjectionMatrix.setToIdentity();
	_modelMatrix.setToIdentity();
	ViewMatrix.setToIdentity();
	MV.setToIdentity();
	MVP.setToIdentity();
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
	sphere = new Sphere(glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
    gear = new Gear(glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 0.2f, 20);
}

void Viewport3D::initializeGL() {
	int result;
	QGLFormat glFormat = QGLWidget::format();
	if (!glFormat.sampleBuffers())
		qWarning() << "Could not enable sample buffers";

	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);

	if (!initShaderPrograms())
		return;

	// Initialize your Geometry Objects here

	// Grid
	gObject = new GeometryObject();
	gObject->CreateGrid();
	result = gObject->InitVertexBuffer(QGLBuffer::StaticDraw);
	result = gObject->FillVertexBuffer();

	// Sphere
	sphere->CreateVertexData();
	result = sphere->InitVertexBuffer(QGLBuffer::StaticDraw);
	result = sphere->FillVertexBuffer();

    // Gear
    gear->CreateVertexData();
    result = gear->InitVertexBuffer(QGLBuffer::StaticDraw);
    result = gear->FillVertexBuffer();
}

void Viewport3D::resizeGL(int width, int height) {
	glViewport(0, 0, width, qMax(height, 1));
	float ratio = (float) width / (float) height;
	ProjectionMatrix.perspective(45.0f, ratio, 0.1f, 100.0f);

}

void Viewport3D::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	update();

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



	gObject->BindVBuffer();
	coordShader.bind();
	coordShader.setAttributeBuffer("vertex", GL_FLOAT, 0, 4, 0);
	coordShader.enableAttributeArray("vertex");
	coordShader.setUniformValue("MVP", MVP);


	gObject->DrawArrays(GL_LINES,0);


	sphere->BindVBuffer();
	shader.bind();
	shader.setAttributeBuffer("vertex", GL_FLOAT, 0, 4, 32);
	shader.setAttributeBuffer("normal",GL_FLOAT,32,4,32);
	shader.enableAttributeArray("vertex");
	shader.enableAttributeArray("normal");
	shader.setUniformValue("MVP", MVP);
	shader.setUniformValue("MV", MV);
	shader.setUniformValue("normalMat",normalMat);
	shader.setUniformValue("eye", eye);


    //sphere->DrawArrays(GL_QUADS,0);


    // Draw gear
    gear->BindVBuffer();
    shader.bind();
    shader.setAttributeBuffer("vertex", GL_FLOAT, 0, 4, 32);
    shader.setAttributeBuffer("normal", GL_FLOAT, 32, 4, 32);
    shader.enableAttributeArray("vertex");
    shader.enableAttributeArray("normal");
    shader.setUniformValue("MVP", MVP);
    shader.setUniformValue("MV", MV);
    shader.setUniformValue("normalMat",normalMat);
    shader.setUniformValue("eye", eye);


    gear->DrawArrays(GL_QUADS, 0);
}

void Viewport3D::update() {

	//Update ViewMatrix
	QMatrix4x4 tViewMatrix;
	tViewMatrix.setToIdentity();
	tViewMatrix.translate(0.0f, 0.0f, -5.0f);
	tViewMatrix.rotate(0.0f, 1.0f, 0.0f, 0.0f);
	tViewMatrix.rotate(0.0f, 0.0f, 1.0f, 0.0f);

	//ViewMatrix = tViewMatrix;

	QMatrix4x4 LookatMatrix;
	LookatMatrix.lookAt(eye, center, up);
	ViewMatrix = LookatMatrix;

	//Update ModelMatrix
	QMatrix4x4 tModelMatrix;
	tModelMatrix.setToIdentity();
	tModelMatrix.scale(1.0f, 1.0f, 1.0f);
	_modelMatrix = tModelMatrix;

	//Update ModelViewProjection Matrix

	MVP = ProjectionMatrix * ViewMatrix * _modelMatrix;
	MV = _modelMatrix;
	normalMat = _modelMatrix;
	normalMat.inverted();
	normalMat.transposed();
}


void Viewport3D::mouseMoveEvent(QMouseEvent *event) {

	int width = this->width();
	int height = this->height();
    float stepSize = 150.0f;

	float dx = (float) (event->x() - mousePos.x()) / width;
	float dy = (float) (event->y() - mousePos.y()) / height;

	if (event->buttons() == 2) {

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
		updateGL();
	}

	mousePos = event->pos();

}

void Viewport3D::mousePressEvent(QMouseEvent *event) {
	mousePos = event->pos();
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
			triangleVP[pointCount] = glm::vec4(sphere->getHitpoint(),1.0f);
			pointCount++;

		}
		else
		{
			pointCount = 0;
			triangleVP[pointCount] = glm::vec4(sphere->getHitpoint(),1.0f);
			pointCount++;

		}
	//	triangleVBO.write(0,triangleVP,3);
	}
}

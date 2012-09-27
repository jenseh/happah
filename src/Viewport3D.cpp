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

	// Load Coordinate System

	for (float x = -2.0; x <= 2.0; x = x + 0.5f) {
		for (float z = -2.0f; z <= 2.0f; z = z + 0.5f) {
			coordSystem.push_back(glm::vec4(x, -1.0f, -2.0, 1.0f));
			coordSystem.push_back(glm::vec4(x, -1.0f, 2.0, 1.0f));
			coordSystem.push_back(glm::vec4(-2.0f, -1.0f, z, 1.0f));
			coordSystem.push_back(glm::vec4(2.0f, -1.0f, z, 1.0f));

		}
	}

	coordVBO.create();
	coordVBO.setUsagePattern(QGLBuffer::StaticDraw);
	if (!coordVBO.bind()) {
		qWarning() << "Could not bind vertex buffer";
		return;
	}
	coordVBO.allocate(&(coordSystem[0]),
			coordSystem.size() * sizeof(coordSystem[0]));
	result = coordShader.link();
	if (!result)
		qWarning() << "Could not link shader program: " << coordShader.log();



	// Load Sphere
	createUnitSphere(5, 5);
	/*
	triangleVBO.create();
	triangleVBO.setUsagePattern(QGLBuffer::DynamicDraw);
	triangleVBO.allocate(triangleVP,3*sizeof(triangleVP[0]));
	*/
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
			"./src/shader/phongVert.glsl");
	if (!result)
		qWarning() << shader.log();

	//load and compile Fragment Shader
	result = shader.addShaderFromSourceFile(QGLShader::Fragment,
			"./src/shader/phongFrag.glsl");
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


	coordVBO.bind();
	coordShader.bind();
	coordShader.setAttributeBuffer("vertex", GL_FLOAT, 0, 4, 0);
	coordShader.enableAttributeArray("vertex");
	coordShader.setUniformValue("MVP", MVP);

	glDrawArrays(GL_LINES, 0, coordSystem.size());

	vertexBuffer.bind();
	shader.bind();
	shader.setAttributeBuffer("vertex", GL_FLOAT, 0, 4, 0);
	shader.enableAttributeArray("vertex");
	shader.setUniformValue("MVP", MVP);
	glm::vec4 eye4 = glm::vec4(eye.x(), eye.y(), eye.z(), 1.0f);
	shader.setUniformValue("eye", eye4.x, eye4.y, eye4.z, eye4.w);

	glDrawArrays(GL_QUADS, 0, sphereVP.size());
/*
	if(pointCount >= 2){
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	triangleVBO.bind();
	coordShader.bind();
	coordShader.setAttributeBuffer("vertex", GL_FLOAT, 0, 4, 0);
	coordShader.enableAttributeArray("vertex");

	glDrawArrays(GL_TRIANGLES,0,3);
	}
*/
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

}

void Viewport3D::createUnitSphere(int dtheta, int dphi) {

	const float toRad = M_PI / 180.0f;
	for (int theta = -90; theta <= 90 - dtheta; theta = theta + dtheta) {
		for (int phi = 0; phi <= 360 - dphi; phi = phi + dphi) {
			glm::vec4 a, b, c, d;
			a.x = cos(theta * toRad) * cos(phi * toRad);
			a.y = cos(theta * toRad) * sin(phi * toRad);
			a.z = sin(theta * toRad);
			a.w = 1.0f;

			b.x = cos((theta + dtheta) * toRad) * cos(phi * toRad);
			b.y = cos((theta + dtheta) * toRad) * sin(phi * toRad);
			b.z = sin((theta + dtheta) * toRad);
			b.w = 1.0f;

			c.x = cos((theta + dtheta) * toRad) * cos((phi + dphi) * toRad);
			c.y = cos((theta + dtheta) * toRad) * sin((phi + dphi) * toRad);
			c.z = sin((theta + dtheta) * toRad);
			c.w = 1.0f;

			d.x = cos(theta * toRad) * cos((phi + dphi) * toRad);
			d.y = cos(theta * toRad) * sin((phi + dphi) * toRad);
			d.z = sin(theta * toRad);
			d.w = 1.0f;

			sphereVP.push_back(a);
			sphereVP.push_back(b);
			sphereVP.push_back(c);
			sphereVP.push_back(d);

		}
	}
	vertexBuffer.create();
	vertexBuffer.setUsagePattern(QGLBuffer::StaticDraw);
	if (!vertexBuffer.bind()) {
		qWarning() << "Could not bind vertex buffer";
		return;
	}
	vertexBuffer.allocate(&sphereVP[0], sphereVP.size() * sizeof(sphereVP[0]));
	int result = shader.link();
	if (!result)
		qWarning() << "Could not link shader program: " << shader.log();

}
void Viewport3D::mouseMoveEvent(QMouseEvent *event) {

	int width = this->width();
	int height = this->height();
	float stepSize = 50;

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

#include "Grid.h"

Grid::Grid() :
        GeometryObject() {
}

void Grid::draw(QGLShaderProgram* shader, QMatrix4x4* projectionMatrix,
                QMatrix4x4* viewMatrix, QVector3D* cameraPosition) {
    //Update ModelViewProjection Matrix
    QMatrix4x4 MV = *viewMatrix * modelMatrix_;
    QMatrix4x4 MVP = *projectionMatrix * MV;

	bindVBuffer();
	shader->bind();
	shader->setAttributeBuffer("vertex", GL_FLOAT, 0, 4, 0);
	shader->enableAttributeArray("vertex");
    shader->setUniformValue("MVP", MVP);

	int mode = GL_LINES;
	int stride = 0;
    glDrawArrays(mode, stride, vertexData_.size());

	shader->release();
}

void Grid::createVertexData() {
	for (float x = -2.0; x <= 2.0; x = x + 0.5f) {
		for (float z = -2.0f; z <= 2.0f; z = z + 0.5f) {
            vertexData_.push_back(glm::vec4(x, -1.0f, -2.0, 1.0f));
            vertexData_.push_back(glm::vec4(x, -1.0f, 2.0, 1.0f));
            vertexData_.push_back(glm::vec4(-2.0f, -1.0f, z, 1.0f));
            vertexData_.push_back(glm::vec4(2.0f, -1.0f, z, 1.0f));
		}
	}
}

// Dummy Function to make things work , im not sure if we should really let our 3D stuff inherit QComponent

QRectF Grid::boundingRect() const
{

	return QRectF(0.0f,0.0f,0.0f,0.0f);
}

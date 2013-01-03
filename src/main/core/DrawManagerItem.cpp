#include "DrawManagerItem.h"

DrawManagerItem::DrawManagerItem(Drawable* drawable, int offset) {
	drawable_ = drawable;
	offset_ = offset;
}

void DrawManagerItem::draw(QGLBuffer* buffer, QGLShaderProgram* shader,
		QMatrix4x4* projectionMatrix, QMatrix4x4* viewMatrix,
		QVector3D* cameraPosition) {
	QMatrix4x4 MV = *viewMatrix * *(drawable_->getModelMatrix());
	QMatrix4x4 MVP = *projectionMatrix * MV;
	QMatrix3x3 normalMatrix = MV.normalMatrix();

//    bindVBuffer();
	shader->bind();
	shader->setAttributeBuffer("vertex", GL_FLOAT, 0, 4, 2 * 4 * sizeof(float));
	shader->setAttributeBuffer("normal", GL_FLOAT, 2 * 4 * sizeof(float), 4,
			2 * 4 * sizeof(float));
	shader->enableAttributeArray("vertex");
	shader->enableAttributeArray("normal");
	shader->setUniformValue("MVP", MVP);
	shader->setUniformValue("MV", MV);
	shader->setUniformValue("normalMat", normalMatrix);
	shader->setUniformValue("eye", *cameraPosition);

	buffer->bind();
	int mode = GL_QUADS;
	int stride = 0;
	glDrawArrays(mode, stride, drawable_->getVertexData()->size());
}

Drawable* DrawManagerItem::getDrawable() {
	return drawable_;
}

int DrawManagerItem::getOffset() {
	return offset_;
}

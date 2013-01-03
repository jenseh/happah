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

//	qreal* data = normalMatrix.data();
//	for (int x=0; x<4; x++) {
//	    for (int y=0; y<4; y++) {
//		std::cout << data[x*4+y] << " ";
//	      }
//	     std::cout << std::endl;
//	  }
//	std::cout << "----------" << std::endl;
	int tupleSize = drawable_->getTupleSize();

	shader->bind();
	shader->setAttributeBuffer("vertex", GL_FLOAT, 0, tupleSize, 2 * 4 * sizeof(float));
	shader->setAttributeBuffer("normal", GL_FLOAT, 4 * sizeof(float), tupleSize,
			2 * 4 * sizeof(float));
	shader->enableAttributeArray("vertex");
	shader->enableAttributeArray("normal");
	shader->setUniformValue("MVP", MVP);
	shader->setUniformValue("MV", MV);
	shader->setUniformValue("normalMat", normalMatrix);
	shader->setUniformValue("eye", *cameraPosition);

//	buffer->bind(); // Not required if only one buffer is used
	int mode = tupleSize == 4 ? GL_QUADS : tupleSize == 3 ? GL_TRIANGLES : -1;
	int stride = 0;
	glDrawArrays(mode, stride, drawable_->getVertexData()->size());
}

Drawable* DrawManagerItem::getDrawable() {
	return drawable_;
}

int DrawManagerItem::getOffset() {
	return offset_;
}

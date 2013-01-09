#include "DrawManagerItem.h"

DrawManagerItem::DrawManagerItem(Drawable* drawable, int offset) {
	drawable_ = drawable;
	offset_ = offset;
	size_t size = drawable->getColorData()->size();
	if( size != 0){
	  if (!colorBuffer_.create()) {
		  std::cerr <<  "Error: Vertex Buffer could not be created!" << std::endl;
		  qWarning() << "Error: Vertex Buffer could not be created!";
		  return;
	  }
	  colorBuffer_.setUsagePattern(QGLBuffer::StaticDraw);

          if (!colorBuffer_.isCreated()) {
                  std::cerr <<  "Error: Vertex Buffer does not exist yet!" << std::endl;
                  qWarning() << "Error: Vertex Buffer does not exist yet!";
                  return;
          }
          if (!colorBuffer_.bind()) {
                  std::cerr <<  "Error: Could not bind vertex buffer!" << std::endl;
                  qWarning() << "Error: Could not bind vertex buffer!";
                  return;
          }
          colorBuffer_.allocate(size*sizeof(Color));
          colorBuffer_.write(0, &drawable->getColorData()[0], size * sizeof(Color));
        }
}

void DrawManagerItem::draw(QGLBuffer* buffer, QGLShaderProgram* shader,
		QMatrix4x4* projectionMatrix, QMatrix4x4* viewMatrix,
		QVector3D* cameraPosition) {
	QMatrix4x4 MV = *viewMatrix * *(drawable_->getModelMatrix());
	QMatrix4x4 MVP = *projectionMatrix * MV;
	QMatrix3x3 normalMatrix = MV.normalMatrix();

//	qreal* data = drawable_->getModelMatrix()->data();
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


	shader->setAttributeBuffer("color", GL_FLOAT, 0, 4, sizeof(Color));
	shader->enableAttributeArray("color");

	shader->setUniformValue("MVP", MVP);
	shader->setUniformValue("MV", MV);
	shader->setUniformValue("normalMat", normalMatrix);
	shader->setUniformValue("eye", *cameraPosition);

	QVector4D ambientColor = QVector4D(0.053f, 0.020f, 0.112f, 1.0f);
	shader->setUniformValue("ambientColor", ambientColor);

	QVector4D diffuseColor = QVector4D(0.75f, 0.75f, 0.75f, 1.0f);
	shader->setUniformValue("diffuseColor", diffuseColor);

	QVector4D specularColor = QVector4D(1.0f, 1.0f, 1.0f, 1.0f);
	shader->setUniformValue("specularColor", specularColor);

	float shininess = 20.0f;
	shader->setUniformValue("shininess", shininess);

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

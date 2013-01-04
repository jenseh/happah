#include "DrawManager.h"

DrawManager::DrawManager() {
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glClearDepth(1.0f);
	glEnable (GL_DEPTH_TEST);

	vertexBuffer_ = new QGLBuffer();
	curBufferOffset = 0;
}

bool DrawManager::initShaderPrograms() {
	shader_ = new QGLShaderProgram();
	coordShader_ = new QGLShaderProgram();

	//load and compile Vertex Shader
	bool result = shader_->addShaderFromSourceFile(QGLShader::Vertex,
			"./src/shader/blinnphongVert.glsl");
	if (!result) {
		qWarning() << shader_->log();
		return result;
	}

	//load and compile Fragment Shader
	result = shader_->addShaderFromSourceFile(QGLShader::Fragment,
			"./src/shader/blinnphongFrag.glsl");
	if (!result) {
		qWarning() << shader_->log();
		return result;
	}

	//coord Shader
	result = coordShader_->addShaderFromSourceFile(QGLShader::Vertex,
			"./src/shader/simpleVert.glsl");
	if (!result) {
		qWarning() << coordShader_->log();
		return result;
	}

	//coord Shader
	result = coordShader_->addShaderFromSourceFile(QGLShader::Fragment,
			"./src/shader/simpleFrag.glsl");
	if (!result) {
		qWarning() << coordShader_->log();
		return result;
	}

	return result;
}

int DrawManager::createBuffer() {
	if (!vertexBuffer_->create()) {
		qWarning() << " Vertex Buffer could not be created!";
		return -1;
	}
	vertexBuffer_->setUsagePattern(QGLBuffer::StaticDraw);

	if (!vertexBuffer_->isCreated()) {
		qWarning() << " Vertex Buffer does not exist yet";
		return -1;
	}
	if (!vertexBuffer_->bind()) {
		qWarning() << "Could not bind vertex buffer";
		return -1;
	}

	if (itemMap_.size() > 0) {
		// Allocate the buffer size that is required for all drawables in itemMap
		vertexBuffer_->allocate(curBufferOffset);

		std::map<int, DrawManagerItem*>::const_iterator iter;
		// Write each drawables data to its offsetted position
		for (iter = itemMap_.begin(); iter != itemMap_.end(); ++iter) {
			std::vector < glm::vec4 > *vertexData = iter->second->getDrawable()->getVertexData();
			int vertexByteSize = vertexData->size() * sizeof(vertexData->at(0));
			int offset = iter->second->getOffset();

			vertexBuffer_->write(offset, &(vertexData->at(0)), vertexByteSize);
		}
	}

	return 0;
}

// Note: as of now this method can only be called before createBuffer!
void DrawManager::addDrawable(Drawable* drawable) {
	// Place drawable in buffer and store the offset
	int offset = curBufferOffset;
	std::vector < glm::vec4 > *vertexData = drawable->getVertexData();
	int vertexByteSize = vertexData->size() * sizeof(vertexData->at(0));
	curBufferOffset += vertexByteSize;

	// Create an entry in the map for the new drawable item
	DrawManagerItem* item = new DrawManagerItem(drawable, offset);
	itemMap_[drawable->getObjectId()] = item;
}

void DrawManager::draw(QMatrix4x4* projectionMatrix, QMatrix4x4* viewMatrix,
		QVector3D* cameraPosition) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw each visual object
	std::map<int, DrawManagerItem*>::iterator iter;
	for (iter = itemMap_.begin(); iter != itemMap_.end(); iter++) {

		// Load matrices and draw object
		iter->second->draw(vertexBuffer_, shader_, projectionMatrix, viewMatrix,
				cameraPosition);
	}
}

#include "DrawManager.h"

DrawManager::DrawManager() {
  glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
  glClearDepth(1.0f);
  glEnable (GL_DEPTH_TEST);
}

bool DrawManager::initShaderPrograms() {
	//load and compile Vertex Shader
	bool result = shader_->addShaderFromSourceFile(QGLShader::Vertex,
			"./src/shader/blinnphongVert.glsl");
	if (!result)
		qWarning() << shader_->log();

	//load and compile Fragment Shader
	result = shader_->addShaderFromSourceFile(QGLShader::Fragment,
			"./src/shader/blinnphongFrag.glsl");
	if (!result)
		qWarning() << shader_->log();

	//coord Shader
	result = coordShader_->addShaderFromSourceFile(QGLShader::Vertex,
			"./src/shader/simpleVert.glsl");
	if (!result)
		qWarning() << coordShader_->log();

	//coord Shader
	result = coordShader_->addShaderFromSourceFile(QGLShader::Fragment,
			"./src/shader/simpleFrag.glsl");
	if (!result)
		qWarning() << coordShader_->log();

	return result;
}

int DrawManager::finalizeBuffer() {
	vertexBuffer_->create();
	vertexBuffer_->setUsagePattern(QGLBuffer::StaticDraw);

	if (!vertexBuffer_->isCreated()) {
		qWarning() << " Vertex Buffer does not exist yet";
		return -1;
	}
	if (!vertexBuffer_->bind()) {
		qWarning() << "Could not bind vertex buffer";
		return -1;
	}

	//TODO: How can we preallocate something we dont know the size of?
//	vertexBuffer_->allocate(&(vertexData_[0]), vertexData_.size() * sizeof(vertexData_[0]));

	return 0;
}

void DrawManager::addDrawable(Drawable* drawable) {
	int offset = 0; //TODO: place drawable in buffer and store the offset
	DrawManagerItem* item = new DrawManagerItem(drawable, offset);

	itemMap_[drawable->getObjectId()] = item;
}

void DrawManager::draw(QMatrix4x4* projectionMatrix, QMatrix4x4* viewMatrix, QVector3D* cameraPosition) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw each visual object
	std::map<int, DrawManagerItem*>::iterator iter;
	for (iter = itemMap_.begin(); iter != itemMap_.end(); iter++) {

	    // Load matrices and draw object
	    std::cout << iter->first << std::endl;
	    iter->second->draw(vertexBuffer_, shader_, projectionMatrix, viewMatrix, cameraPosition);
	}
}

#include "DrawManager.h"

DrawManager::DrawManager() {
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glClearDepth(1.0f);
	glEnable (GL_DEPTH_TEST);

	vertexBuffer_ = new QGLBuffer();
    colorBuffer_ = new QGLBuffer();
    curVertexBufferOffset = 0;
    curColorBufferOffset = 0;

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

int DrawManager::createVertexBuffer() {
	if (!vertexBuffer_->create()) {
		std::cerr <<  "Error: Vertex Buffer could not be created!" << std::endl;
		qWarning() << "Error: Vertex Buffer could not be created!";
		return 0;
	}
	vertexBuffer_->setUsagePattern(QGLBuffer::StaticDraw);

	if (!vertexBuffer_->isCreated()) {
		std::cerr <<  "Error: Vertex Buffer does not exist yet!" << std::endl;
		qWarning() << "Error: Vertex Buffer does not exist yet!";
		return 0;
	}
	if (!vertexBuffer_->bind()) {
		std::cerr <<  "Error: Could not bind vertex buffer!" << std::endl;
		qWarning() << "Error: Could not bind vertex buffer!";
		return 0;
	}

	if (itemMap_.size() > 0) {
		// Allocate the buffer size that is required for all drawables in itemMap
        vertexBuffer_->allocate(curVertexBufferOffset);

		std::map<int, DrawManagerItem*>::const_iterator iter;
		// Write each drawables data to its offsetted position
		for (iter = itemMap_.begin(); iter != itemMap_.end(); ++iter) {
			std::vector < glm::vec4 > *vertexData = iter->second->getDrawable()->getVertexData();
			int vertexByteSize = vertexData->size() * sizeof(vertexData->at(0));
			int offset = iter->second->getOffset();

			vertexBuffer_->write(offset, &(vertexData->at(0)), vertexByteSize);
		}
	}
	return 1;
}

int DrawManager::createColorBuffer() {
    if (!colorBuffer_->create()) {
        std::cerr <<  "Error: Color Buffer could not be created!" << std::endl;
        qWarning() << "Error: Color Buffer could not be created!";
        return 0;
    }
    colorBuffer_->setUsagePattern(QGLBuffer::StaticDraw);

    if (!colorBuffer_->isCreated()) {
        std::cerr <<  "Error: Color Buffer does not exist yet!" << std::endl;
        qWarning() << "Error: Color Buffer does not exist yet!";
        return 0;
    }
    if (!colorBuffer_->bind()) {
        std::cerr <<  "Error: Could not bind Color buffer!" << std::endl;
        qWarning() << "Error: Could not bind Color buffer!";
        return 0;
    }
    if (itemMap_.size() > 0) {
        // Allocate the buffer size that is required for all drawables in itemMap
        colorBuffer_->allocate(curColorBufferOffset);

        std::map<int, DrawManagerItem*>::const_iterator iter;
        // Write each drawables data to its offsetted position
        for (iter = itemMap_.begin(); iter != itemMap_.end(); ++iter) {
            std::vector < Color > *colorData = iter->second->getDrawable()->getColorData();
            if( colorData->size() != 0){ // If object has color
                int colorByteSize = colorData->size() * sizeof(Color);
                int offset = iter->second->getOffset();

                colorBuffer_->write(offset, &(colorData->at(0)), colorByteSize);
            }
        }
    }
    return 1;
}

// Note: as of now this method can only be called before createBuffer!
void DrawManager::addDrawable(Drawable* drawable) {
	// Place drawable in buffer and store the offset
    int vertexOffset = curVertexBufferOffset;
	std::vector < glm::vec4 > *vertexData = drawable->getVertexData();
	int vertexByteSize = vertexData->size() * sizeof(vertexData->at(0));
    curVertexBufferOffset += vertexByteSize;

    int colorOffset = curColorBufferOffset;
    std::vector < Color>* colorData = drawable->getColorData();
    int colorByteSize = colorData->size() * sizeof(Color);
    curColorBufferOffset += colorByteSize;

	// Create an entry in the map for the new drawable item
    DrawManagerItem* item = new DrawManagerItem(drawable, vertexOffset + colorOffset);
	itemMap_[drawable->getObjectId()] = item;
}


void DrawManager::draw(QMatrix4x4* projectionMatrix, QMatrix4x4* viewMatrix,
		QVector3D* cameraPosition) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw each visual object
	std::map<int, DrawManagerItem*>::iterator iter;
	for (iter = itemMap_.begin(); iter != itemMap_.end(); iter++) {

		// Load matrices and draw object
        iter->second->draw(vertexBuffer_, colorBuffer_, shader_, projectionMatrix, viewMatrix,
				cameraPosition);
	}
}

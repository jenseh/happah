#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
# include <GL/glew.h>
# include <GL/gl.h>
#include <glm/gtc/type_ptr.hpp>
#include <QMatrix4x4>

#include "happah/gui/DrawManager.h"
#include "happah/scene/Material.h"

using namespace std;

HappahGlFormat::HappahGlFormat() {
    setVersion(3, 1);
	setProfile(QGLFormat::CompatibilityProfile);
	setSampleBuffers(true);
	setDoubleBuffer(true);
	setDepth(true);
}

const HappahGlFormat DrawManager::GL_FORMAT;

DrawManager::DrawManager(SceneManager_ptr sceneManager)
    : m_glInitialized(false), m_drawVisitor(*this), m_sceneListener(*this), m_sceneManager(sceneManager),m_selectionVisitor(*this), m_glContext(new QGLContext(GL_FORMAT)),m_somethingSelected(false) {
	m_isSkipLightingContributionComputation = false;
	m_sceneManager->registerSceneListener(&m_sceneListener);

}

DrawManager::~DrawManager() {}

void DrawManager::compileShader(GLuint shader, const char* filePath) {
	ifstream sourceFile(filePath);
	if (sourceFile) {
		stringstream temp;
		temp << sourceFile.rdbuf();
		sourceFile.close();
		string sourceString = temp.str();
		const char* source = sourceString.c_str();
		int sourceStringLength = sourceString.length();
		glShaderSource(shader, 1, (const GLchar**) &source, &sourceStringLength);
		glCompileShader(shader);
		GLint compileStatus;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
		if (compileStatus == GL_FALSE) {
			char log[256];
			glGetShaderInfoLog(shader, 256, NULL, log);
			cerr << "Compilation of shader failed." << endl;
			printf(" Infolog: %s\n", log);
		} else
			cout << "Compilation was successful." << endl;
	} else
		cerr << "Failed to open source file." << endl;
}

void DrawManager::doDraw(ElementRenderStateNode_ptr elementRenderStateNode, RigidAffineTransformation& rigidAffineTransformation, bool doSelection) {
	// CHanged for geometry Shader Test ... reverse after successfull test
	glUseProgram(m_program);
	m_modelMatrix = rigidAffineTransformation.toMatrix4x4();
	m_normalMatrix = glm::inverse(glm::transpose(rigidAffineTransformation.getMatrix()));
	hpmat4x4 modelViewProjectionMatrix = m_projectionMatrix * m_viewMatrix * m_modelMatrix;
	glBindVertexArray(elementRenderStateNode->getVertexArrayObjectID());
	glUniformMatrix4fv(m_modelMatrixLocation, 1, GL_FALSE, (GLfloat*) &m_modelMatrix);
	glUniformMatrix4fv(m_modelViewProjectionMatrixLocation, 1, GL_FALSE, (GLfloat*) &modelViewProjectionMatrix);
	glUniformMatrix3fv(m_normalMatrixLocation, 1, GL_FALSE, (GLfloat*) &m_normalMatrix);
	glUniform1f(m_ambientFactorLocation, (GLfloat) elementRenderStateNode->getMaterial().getAmbientFactor());
	glUniform1f(m_diffuseFactorLocation, (GLfloat) elementRenderStateNode->getMaterial().getDiffuseFactor());
	glUniform1f(m_specularFactorLocation, (GLfloat) elementRenderStateNode->getMaterial().getSpecularFactor());
	glUniform1f(m_phongExponentLocation, (GLfloat) elementRenderStateNode->getMaterial().getPhongExponent());
	glUniform3f(m_cameraPositionLocation, m_cameraPosition.x, m_cameraPosition.y, m_cameraPosition.z);
	if (elementRenderStateNode->hasColorVector()) {
		glUniform4f(m_colorComponentLocation, 0.0f, 0.0f, 0.0f, 0.0f);
		glUniform1i(m_isColorPerVertexLocation, 1);
		glUniform1i(m_isSkipLightingContributionComputationLocation, 1);
	} else {
		hpcolor color = elementRenderStateNode->getColor();
		glUniform4f(m_colorComponentLocation, color.x, color.y, color.z, color.w);
		glUniform1i(m_isColorPerVertexLocation, 0);
		glUniform1i(m_isSkipLightingContributionComputationLocation, m_isSkipLightingContributionComputation); //TODO: ask user if he wants to use fragment shading
	}

	int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	if(doSelection){
		float colorIndex = (float)m_selectionVisitor.getCurrentSelectionIndex()/100.0f;
		hpcolor color = hpvec4(colorIndex,0.0f,0.0f,0.0f);
		glUniform1i(m_drawSelectionColors,1);
		glUniform4f(m_colorComponentLocation, color.x, color.y, color.z, color.w);
		glUniform1i(m_isColorPerVertexLocation, 0);
		glBindFramebuffer(GL_FRAMEBUFFER,m_frameBuffer);
		glDrawElements(elementRenderStateNode->getMode(), size / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
		glBindFramebuffer(GL_FRAMEBUFFER,0);
	}
	glUniform1i(m_drawSelectionColors,0);
	glUniform1i(m_selectedLocation,elementRenderStateNode->getSelected());
	glDrawElements(elementRenderStateNode->getMode(), size / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void DrawManager::doDraw(PointCloudRenderStateNode_ptr pointCloudRenderStateNode, RigidAffineTransformation& rigidAffineTransformation, bool doSelection){
	glUseProgram(m_pointCloudProgram);
	m_modelMatrix = rigidAffineTransformation.toMatrix4x4();
	m_normalMatrix = glm::inverse(glm::transpose(rigidAffineTransformation.getMatrix()));
//	hpmat4x4 modelViewProjectionMatrix = m_projectionMatrix * m_viewMatrix * m_modelMatrix;
	hpmat4x4 modelViewMatrix = m_viewMatrix * m_modelMatrix;
	glBindVertexArray(pointCloudRenderStateNode->getVertexArrayObjectID());
	glUniformMatrix4fv(m_pointCloudModelViewMatrixLocation, 1, GL_FALSE, (GLfloat*) &modelViewMatrix);
	glUniformMatrix4fv(m_pointCloudProjectionMatrixLocation, 1, GL_FALSE, (GLfloat*) &m_projectionMatrix);
	glUniform1f(m_pointCloudPointRadiusLocation, (GLfloat)0.06f);
	if(doSelection){
		float colorIndex = (float)m_selectionVisitor.getCurrentSelectionIndex() / 100.0f;
		hpcolor color = hpvec4(colorIndex,0.0f,0.0f,0.0f);
		glUniform4f(m_pointCloudSelectionColorLocation, color.x, color.y, color.z, color.w);
		glUniform1i(m_pointCloudDrawSelectionColors,1);
		glBindFramebuffer(GL_FRAMEBUFFER,m_frameBuffer);
		glDrawArrays(pointCloudRenderStateNode->getMode(), 0, pointCloudRenderStateNode->getVerticesAndNormals()->size());
		glBindFramebuffer(GL_FRAMEBUFFER,0);
	}
	hpvec4 color = pointCloudRenderStateNode->getColor();
	glUniform4f(m_pointCloudColorComponent,color.x,color.y,color.z,color.w);
	glUniform1i(m_pointCloudDrawSelectionColors,0);
	glUniform1i(m_pointCloudSelectedLocation,pointCloudRenderStateNode->getSelected());
	glDrawArrays(pointCloudRenderStateNode->getMode(), 0, pointCloudRenderStateNode->getVerticesAndNormals()->size());
	glBindVertexArray(0);
}

void DrawManager::draw(hpmat4x4& projectionMatrix, hpmat4x4& viewMatrix, hpvec3& cameraPosition) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	m_modelMatrix = hpmat4x4(1.0f);
	m_viewMatrix = viewMatrix;
	m_projectionMatrix = projectionMatrix;
	m_cameraPosition = cameraPosition;

	RigidAffineTransformation identityTransformation;
	m_sceneManager->draw(m_drawVisitor, identityTransformation);
	//TODO: this is just debug output , remove when selection works
	glUseProgram(0);
	int dimensions[4];
	glGetIntegerv(GL_VIEWPORT,&dimensions[0]);
	int width = dimensions[2];
	int height = dimensions[3];
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,m_selectorTexture);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBegin(GL_QUADS);
	//TL
	glTexCoord2f(0,1);
	glColor3f(1.0f,1.0f,1.0f);
	glVertex2f(-1.0f+0.05f,-1.0f+0.35f);
	//TR
	glTexCoord2f(1,1);
	glColor3f(1.0f,1.0f,1.0f);
	glVertex2f(-1.0f+0.35f,-1.0f+0.35f);
	//BR
	glTexCoord2f(1,0);
	glColor3f(1.0f,1.0f,1.0f);
	glVertex2f(-1.0f+0.35f,-1.0f+0.05f);
	//BL
	glTexCoord2f(0,0);
	glColor3f(1.0f,1.0f,1.0f);
	glVertex2f(-1.0f+0.05f,-1.0f+0.05f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	// TODO :: REMOVE DEBUG OUTPUT
}

bool DrawManager::select(int x, int y){
	ElementRenderStateNode_ptr currentElementRenderStateNode = m_selectionVisitor.getCurrentSelectedElementRenderStateNode();
	PointCloudRenderStateNode_ptr currentPointCloudRenderStateNode = m_selectionVisitor.getCurrentSelectedPointCloudRenderStateNode();
	if (currentElementRenderStateNode){
		currentElementRenderStateNode->setSelected(0);
		currentElementRenderStateNode->triggerDeselectEvent();
	}
	if (currentPointCloudRenderStateNode){
		currentPointCloudRenderStateNode->setSelected(0);
		currentPointCloudRenderStateNode->triggerDeselectEvent();
	}
	glBindFramebuffer(GL_FRAMEBUFFER,m_frameBuffer);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
	glBindFramebuffer(GL_FRAMEBUFFER,0);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RigidAffineTransformation identityTransformation;
	m_sceneManager->draw(m_selectionVisitor, identityTransformation);


	hpcolor pixel[1];	int dimensions[4];
	glGetIntegerv(GL_VIEWPORT,&dimensions[0]);
	int width = dimensions[2];
	int height = dimensions[3];
	glBindFramebuffer(GL_FRAMEBUFFER,m_frameBuffer);
	glReadBuffer(GL_COLOR_ATTACHMENT0);
	glReadPixels(x,height-y,1,1,GL_RGBA,GL_FLOAT,&pixel[0]);
	m_somethingSelected = false;
	ElementRenderStateNode_ptr foundNode = m_selectionVisitor.findElementRenderStateNodeOfColor(pixel[0]);
	if(foundNode){
		foundNode->setSelected(1);
		foundNode->triggerSelectEvent();
		m_selectionVisitor.setCurrentSelectedElementRenderStateNode(foundNode);
		m_somethingSelected = true;
	}

	PointCloudRenderStateNode_ptr foundPointCloudNode = m_selectionVisitor.findPointCloudRenderStateNodeOfColor(pixel[0]);
	if(foundPointCloudNode){
		int index = m_selectionVisitor.findPointIndexFromColor(pixel[0]);
		foundPointCloudNode->setSelected(1);
		foundPointCloudNode->triggerSelectEvent(index);
		m_selectionVisitor.setCurrentSelectedPointCloudRenderStateNode(foundPointCloudNode);
		m_somethingSelected = true;
	}

	glBindFramebuffer(GL_FRAMEBUFFER,0);
	m_selectionVisitor.setCurrentSelectionIndex(100);
	m_selectionVisitor.clearColorMaps();
	return m_somethingSelected;
}
QGLContext* DrawManager::getGlContext() {
	return m_glContext;
}
bool DrawManager::init(QPaintDevice* device) {

    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    if(device == NULL)
        return false;
    #endif

    m_glContext = new QGLContext(GL_FORMAT, device);
    if(!m_glContext->create()) {
        fprintf(stderr, "Unable to create QGLContext! \n");
        return false;
    }
    m_glContext->makeCurrent();

    GLenum errorCode = glewInit();
    if (GLEW_OK != errorCode) {
        fprintf(stderr, "Glew initialization failed: %s\n", glewGetErrorString(errorCode));
        return false;
    }

    QGLFormat glFormat = m_glContext->format();
    if (!glFormat.sampleBuffers()) {
        qWarning() << "Could not enable sample buffers";
    }


    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    if (!initShaderPrograms())
        return false;
    if (!enableFrameBuffer())
        return false;

    m_glInitialized = true;

    return true;
}

void DrawManager::initialize(ElementRenderStateNode_ptr elementRenderStateNode) {
	GLuint bufferID;
	GLint size = (elementRenderStateNode->getVerticesAndNormals()->size());
	// Create New VertexArrayObject
	glGenVertexArrays(1, &bufferID);
	elementRenderStateNode->setVertexArrayObjectID(bufferID);
	glBindVertexArray(elementRenderStateNode->getVertexArrayObjectID());

	// Create New Vertex Buffer Object
	glGenBuffers(1, &bufferID);
	elementRenderStateNode->setVertexBufferID(bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, elementRenderStateNode->getVertexBufferID());
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(hpvec3), &(elementRenderStateNode->getVerticesAndNormals()->at(0)), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(m_vertexLocation, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(hpvec3), 0);
	glVertexAttribPointer(m_normalLocation, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(hpvec3), (void*) sizeof(hpvec3));
	glEnableVertexAttribArray(m_vertexLocation);
	glEnableVertexAttribArray(m_normalLocation);

	// Create New Color Buffer Object
	if (elementRenderStateNode->hasColorVector()) {
		glGenBuffers(1, &bufferID);
		elementRenderStateNode->setColorBufferID(bufferID);
		glBindBuffer(GL_ARRAY_BUFFER, elementRenderStateNode->getColorBufferID());
		glBufferData(GL_ARRAY_BUFFER, elementRenderStateNode->getColorVector()->size() * sizeof(hpcolor), &(elementRenderStateNode->getColorVector()->at(0)), GL_DYNAMIC_DRAW);
		glVertexAttribPointer(m_colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(hpcolor), 0);
		glEnableVertexAttribArray(m_colorLocation);
	}

	// Create IndexBuffer;
	size = elementRenderStateNode->getIndices()->size();
	glGenBuffers(1, &bufferID);
	elementRenderStateNode->setIndexBufferID(bufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementRenderStateNode->getIndexBufferID());
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLuint), &(elementRenderStateNode->getIndices()->at(0)), GL_DYNAMIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	elementRenderStateNode->setInitialized(true);
}

void DrawManager::initialize(PointCloudRenderStateNode_ptr pointCloudRenderStateNode) {
	GLuint bufferID;
	GLint size = (pointCloudRenderStateNode->getVerticesAndNormals()->size());
	// Create New VertexArrayObject
	glGenVertexArrays(1, &bufferID);
	pointCloudRenderStateNode->setVertexArrayObjectID(bufferID);
	glBindVertexArray(pointCloudRenderStateNode->getVertexArrayObjectID());

	// Create New Vertex Buffer Object
	glGenBuffers(1, &bufferID);
	pointCloudRenderStateNode->setVertexBufferID(bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, pointCloudRenderStateNode->getVertexBufferID());
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(hpvec3), &(pointCloudRenderStateNode->getVerticesAndNormals()->at(0)), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(m_pointCloudVertexLocation, 3, GL_FLOAT, GL_FALSE,sizeof(hpvec3), 0);
	glEnableVertexAttribArray(m_pointCloudVertexLocation);


	// Create New Color Buffer Object
	glGenBuffers(1, &bufferID);
	pointCloudRenderStateNode->setColorBufferID(bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, pointCloudRenderStateNode->getColorBufferID());
	glBufferData(GL_ARRAY_BUFFER, pointCloudRenderStateNode->getVerticesAndNormals()->size() * sizeof(hpcolor),&(m_selectionVisitor.getPointSelectionColors()->at(0)), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(m_pointCloudSinglePointSelectionColorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(hpcolor), 0);
	glEnableVertexAttribArray(m_pointCloudSinglePointSelectionColorLocation);



	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	pointCloudRenderStateNode->setInitialized(true);
}


bool DrawManager::initShaderPrograms() {
	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	compileShader(m_vertexShader, "shader/simple.vert");

	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	compileShader(m_fragmentShader, "shader/simple.frag");

	m_program = glCreateProgram();
	glAttachShader(m_program, m_vertexShader);
	glAttachShader(m_program, m_fragmentShader);
	glLinkProgram(m_program);
	GLint linkStatus;
	glGetProgramiv(m_program, GL_LINK_STATUS, &linkStatus);
	if (linkStatus == GL_FALSE)
		cerr << "Linking failed." << endl;
	else
		cout << "Linking was successful." << endl;

	// Vertex Attributes
	m_vertexLocation = glGetAttribLocation(m_program, "vertex");
	if (m_vertexLocation < 0)
		cerr << "Failed to find vertexLocation." << endl;
	m_normalLocation = glGetAttribLocation(m_program, "normal");
	if (m_normalLocation < 0)
		cerr << "Failed to find normalLocation." << endl;
	m_colorLocation = glGetAttribLocation(m_program, "color");
	if (m_colorLocation < 0)
		cerr << "Failed to find colorLocation." << endl;

	// Matrix Uniforms
	m_modelMatrixLocation = glGetUniformLocation(m_program, "modelMatrix");
	if (m_modelMatrixLocation < 0)
		cerr << "Failed to find ModelMatrixLocation." << endl;
	m_modelViewProjectionMatrixLocation = glGetUniformLocation(m_program, "modelViewProjectionMatrix");
	if (m_modelViewProjectionMatrixLocation < 0)
		cerr << "Failed to find modelViewProjectionMatrixLocation." << endl;
	m_normalMatrixLocation = glGetUniformLocation(m_program, "normalMatrix");
	if (m_normalMatrixLocation < 0)
		cerr << "Failed to find normalMatrixLocation." << endl;

	// Material uniforms
	m_selectedLocation = glGetUniformLocation(m_program, "isSelected");
	if (m_selectedLocation < 0)
			cerr << "Failed to find selectedLocation." << endl;
	m_ambientFactorLocation = glGetUniformLocation(m_program, "ambientFactor");
	if (m_ambientFactorLocation < 0)
		cerr << "Failed to find ambientFactorLocation." << endl;
	m_diffuseFactorLocation = glGetUniformLocation(m_program, "diffuseFactor");
	if (m_diffuseFactorLocation < 0)
		cerr << "Failed to find diffuseFactorLocation." << endl;
	m_specularFactorLocation = glGetUniformLocation(m_program, "specularFactor");
	if (m_specularFactorLocation < 0)
		cerr << "Failed to find specularFactorLocation." << endl;
	m_phongExponentLocation = glGetUniformLocation(m_program, "phongExponent");
	if (m_phongExponentLocation < 0)
		cerr << "Failed to find phongLocation." << endl;
	m_colorComponentLocation = glGetUniformLocation(m_program, "colorComponent");
	if (m_colorComponentLocation < 0)
		cerr << "Failed to find color Component." << endl;
	m_isColorPerVertexLocation = glGetUniformLocation(m_program, "isColorPerVertex");
	if (m_isColorPerVertexLocation < 0)
		cerr << "Failed to find isColorPerVertex." << endl;
	m_isSkipLightingContributionComputationLocation = glGetUniformLocation(m_program, "isSkipLightingContributionComputation");
	if (m_isSkipLightingContributionComputationLocation < 0)
		cerr << "Failed to find isSkipLightingContributionComputation." << endl;
	//Camera and Light uniforms
	m_cameraPositionLocation = glGetUniformLocation(m_program, "cameraPosition");
	if (m_cameraPositionLocation < 0)
		cerr << "Failed to find cameraPositionLocation." << endl;
	m_drawSelectionColors = glGetUniformLocation(m_program, "drawSelectionColors");
	if (m_drawSelectionColors < 0)
		cerr << "Failed to find drawSelectionColorsLocation" << endl;
	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	compileShader(m_vertexShader,"shader/pointCloudShader.vert");
	m_geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
	compileShader(m_geometryShader,"shader/pointCloudShader.geom");
	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	compileShader(m_fragmentShader,"shader/pointCloudShader.frag");

	m_pointCloudProgram = glCreateProgram();
	glAttachShader(m_pointCloudProgram, m_vertexShader);
	glAttachShader(m_pointCloudProgram, m_geometryShader);
	glAttachShader(m_pointCloudProgram, m_fragmentShader);
	glLinkProgram(m_pointCloudProgram);

	glGetProgramiv(m_pointCloudProgram, GL_LINK_STATUS, &linkStatus);
	if (linkStatus == GL_FALSE)
		cerr << "Linking failed." << endl;
	else
		cout << "Linking was successful." << endl;

	m_pointCloudVertexLocation = glGetAttribLocation(m_pointCloudProgram, "vertex");
	if (m_pointCloudVertexLocation < 0)
		cerr << "Failed to find pcvertexLocation." << endl;
    m_pointCloudColorLocation = m_colorLocation;//glGetAttribLocation(m_pointCloudProgram, "color");
	if (m_pointCloudColorLocation < 0)
		cerr << "Failed to find PointCloudColorLocation." << endl;
    m_pointCloudSinglePointSelectionColorLocation= glGetAttribLocation(m_pointCloudProgram, "pointSelectionColor");
	if (m_pointCloudSinglePointSelectionColorLocation < 0)
		cerr << "Failed to find m_pointCloudSinglePointSelectionColorLocation." << endl;
	m_pointCloudModelViewMatrixLocation = glGetUniformLocation(m_pointCloudProgram, "modelViewMatrix");
	if (m_pointCloudModelViewMatrixLocation< 0)
		cerr << "Failed to find ModelViewMatrixLocation." << endl;
	m_pointCloudProjectionMatrixLocation = glGetUniformLocation(m_pointCloudProgram, "projectionMatrix");
	if (m_pointCloudProjectionMatrixLocation < 0)
		cerr << "Failed to find PointCloudProjectionMatrixLocation." << endl;
	m_pointCloudPointRadiusLocation = glGetUniformLocation(m_pointCloudProgram, "pointRadius");
	if (m_pointCloudPointRadiusLocation < 0)
		cerr << "Failed to find PointCloudProjectionMatrixLocation." << endl;
	m_pointCloudDrawSelectionColors = glGetUniformLocation(m_pointCloudProgram, "drawSelectionColors");
	if (m_pointCloudDrawSelectionColors < 0)
			cerr << "Failed to find m_pointCloudDrawSelectionColors." << endl;
	m_pointCloudSelectionColorLocation = glGetUniformLocation(m_pointCloudProgram,"selectionColor");
	if (m_pointCloudSelectionColorLocation < 0)
				cerr << "Failed to find m_pointCloudSelectionColorLocation." << endl;
	m_pointCloudSelectedLocation = glGetUniformLocation(m_pointCloudProgram,"selected");
	if (m_pointCloudSelectedLocation < 0)
				cerr << "Failed to find m_pointCloudSelectedLocation." << endl;
	m_pointCloudColorComponent = glGetUniformLocation(m_pointCloudProgram,"colorComponent");
	if (m_pointCloudColorComponent < 0)
		cerr << "Failed to find m_pointCloudColorComponent." << endl;	
	return true;
}

bool DrawManager::enableFrameBuffer(){
	int dimensions[4];
	glGetIntegerv(GL_VIEWPORT,&dimensions[0]);
	int width = dimensions[2];
	int height = dimensions[3];

	glGenFramebuffers(1, &m_frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);

	glGenTextures(1,&m_selectorTexture);
	glBindTexture(GL_TEXTURE_2D,m_selectorTexture);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glGenRenderbuffers(1,&m_depthRenderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER,m_depthRenderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT,width,height); //TODO: adjust to viewport size
	glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER,m_depthRenderBuffer);

    //glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,m_selectorTexture,0);
    glFramebufferTexture(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,m_selectorTexture,0);
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE )
		return false;
	glBindFramebuffer(GL_FRAMEBUFFER,0);
	return true;
}

void DrawManager::resizeSelectorTexture(){
	int dimensions[4];
		glGetIntegerv(GL_VIEWPORT,&dimensions[0]);
		int width = dimensions[2];
		int height = dimensions[3];
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
	glBindTexture(GL_TEXTURE_2D,m_selectorTexture);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,0);
	glBindRenderbuffer(GL_RENDERBUFFER,m_depthRenderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT,width,height);
	glBindRenderbuffer(GL_RENDERBUFFER,0);
	glBindTexture(GL_TEXTURE_2D,0);
	glBindFramebuffer(GL_FRAMEBUFFER,0);

}

DrawManager::DefaultDrawVisitor::DefaultDrawVisitor(DrawManager& drawManager)
	: m_drawManager(drawManager) {}

DrawManager::DefaultDrawVisitor::~DefaultDrawVisitor() {}

void DrawManager::DefaultDrawVisitor::draw(ElementRenderStateNode_ptr elementRenderStateNode, RigidAffineTransformation& rigidAffineTransformation) {
	// If no Buffer has been assigned, assign one, and write Data into it
	if (!elementRenderStateNode->isInitialized())
		m_drawManager.initialize(elementRenderStateNode);
	m_drawManager.doDraw(elementRenderStateNode, rigidAffineTransformation,false);
}

void DrawManager::DefaultDrawVisitor::draw(PointCloudRenderStateNode_ptr pointCloudRenderStateNode, RigidAffineTransformation& rigidAffineTransformation){
	if (!pointCloudRenderStateNode->isInitialized())
		m_drawManager.initialize(pointCloudRenderStateNode);
	m_drawManager.doDraw(pointCloudRenderStateNode, rigidAffineTransformation,false);
}

DrawManager::SelectionVisitor::SelectionVisitor(DrawManager& drawManager)
	: m_drawManager(drawManager),m_currentSelectionIndex(100) {
	m_pointSelectionColors = new vector<hpcolor>;
    for (int g=99; g >= 0 ;g--){
		float gComponent = (float)g/100.0f;
        for(int b=99;b >= 0; b--){
			float bComponent = (float)b/100.0f;
			m_pointSelectionColors->push_back(hpcolor(0.0f,gComponent,bComponent,0.0f));
		}
	}
}

DrawManager::SelectionVisitor::~SelectionVisitor() {}

void DrawManager::SelectionVisitor::draw(ElementRenderStateNode_ptr elementRenderStateNode, RigidAffineTransformation& rigidAffineTransformation) {
	// If no Buffer has been assigned, assign one, and write Data into it
	if (!elementRenderStateNode->isInitialized())
		m_drawManager.initialize(elementRenderStateNode);
	m_currentSelectionIndex = m_currentSelectionIndex-1;
	if (m_currentSelectionIndex < 0 ){
		cerr << "Too many objects! ";
		return;
	}

	m_colorMap.insert(ValuePair((int)(m_currentSelectionIndex),elementRenderStateNode));
	m_drawManager.doDraw(elementRenderStateNode, rigidAffineTransformation,true);
}
void DrawManager::SelectionVisitor::draw(PointCloudRenderStateNode_ptr pointCloudRenderStateNode, RigidAffineTransformation& rigidAffineTransformation){
	if (!pointCloudRenderStateNode->isInitialized())
		m_drawManager.initialize(pointCloudRenderStateNode);
	m_currentSelectionIndex=m_currentSelectionIndex-1;
	if (m_currentSelectionIndex < 0 ){
		cerr << "Too many objects! ";
		return;
	}

	m_pointCloudColorMap.insert(PCValuePair(m_currentSelectionIndex,pointCloudRenderStateNode));
	m_drawManager.doDraw(pointCloudRenderStateNode, rigidAffineTransformation,true);
}


int DrawManager::SelectionVisitor::getCurrentSelectionIndex(){
	return m_currentSelectionIndex;
}

void DrawManager::SelectionVisitor::setCurrentSelectionIndex(int index){
	m_currentSelectionIndex = index;
}

ElementRenderStateNode_ptr DrawManager::SelectionVisitor::findElementRenderStateNodeOfColor(hpcolor color){
	ElementsColorMap::const_iterator iter = m_colorMap.begin();
	int index = (int)(color.r*100+0.5f);
	   iter = m_colorMap.find(index);
	if(iter != m_colorMap.end()){
       return (*iter).second;
	}
    else{
       return NULL;
    }
}

ElementRenderStateNode_ptr DrawManager::SelectionVisitor::getCurrentSelectedElementRenderStateNode(){
	return m_currentSelectedElementRenderStateNode;
}

void DrawManager::SelectionVisitor::setCurrentSelectedElementRenderStateNode(ElementRenderStateNode_ptr elementRenderStateNode){
	m_currentSelectedElementRenderStateNode = elementRenderStateNode;
}

PointCloudRenderStateNode_ptr DrawManager::SelectionVisitor::getCurrentSelectedPointCloudRenderStateNode(){
	return m_currentSelectedPointCloudRenderStateNode;
}

void DrawManager::SelectionVisitor::setCurrentSelectedPointCloudRenderStateNode(PointCloudRenderStateNode_ptr pointCloudRenderStateNode){
	m_currentSelectedPointCloudRenderStateNode = pointCloudRenderStateNode;
}

PointCloudRenderStateNode_ptr DrawManager::SelectionVisitor::findPointCloudRenderStateNodeOfColor(hpcolor color){
	PointCloudColorMap::const_iterator iter = m_pointCloudColorMap.begin();
	int index = (int)(color.r*100+0.5f);
	   iter = m_pointCloudColorMap.find(index);
	if(iter != m_pointCloudColorMap.end()){
       return (*iter).second;
	}
    else{
      return NULL;
    }
}
vector<hpcolor>* DrawManager::SelectionVisitor::getPointSelectionColors(){
	return m_pointSelectionColors;
}

void DrawManager::SelectionVisitor::clearColorMaps(){
	m_colorMap.clear();
    m_pointCloudColorMap.clear();
}
int DrawManager::SelectionVisitor::findPointIndexFromColor(hpcolor color){
    int gIndex = (int)(color.g*100.5f);
    int bIndex = (int)(color.b*100.5f);
    int index = 9999-((gIndex*100)+bIndex);
    return index;
}


DrawManager::DefaultSceneListener::DefaultSceneListener(DrawManager& drawManager)
	: m_drawManager(drawManager) {}

DrawManager::DefaultSceneListener::~DefaultSceneListener() {}

void DrawManager::DefaultSceneListener::handleSubtreeInsertedEvent(Node_ptr root) {}

void DrawManager::DefaultSceneListener::handleSubtreesInsertedEvent(vector<Node_ptr>& roots) {}

void DrawManager::DefaultSceneListener::handleSubtreeRemovedEvent(Node_ptr root) {
	//TODO
}

void DrawManager::DefaultSceneListener::handleSubtreesRemovedEvent(vector<Node_ptr>& roots) {
	//TODO
}

void DrawManager::DefaultSceneListener::handleSubtreeUpdatedEvent(Node_ptr root) {}

void DrawManager::DefaultSceneListener::handleSubtreesUpdatedEvent(vector<Node_ptr>& roots) {}

GLenum DrawManager::m_drawBuffers[] = {GL_FRONT,GL_COLOR_ATTACHMENT0};

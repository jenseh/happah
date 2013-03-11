#define GLEW_STATIC //Very important for Windows users
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/gtc/type_ptr.hpp>
#include <QMatrix4x4>

#include "happah/gui/DrawManager.h"
#include "happah/scene/Material.h"

using namespace std;

HappahGlFormat::HappahGlFormat() {
	setVersion(3, 3);
	setProfile(QGLFormat::CompatibilityProfile);
	setSampleBuffers(true);
	setDoubleBuffer(true);
	setDepth(true);
}

const HappahGlFormat DrawManager::GL_FORMAT;

DrawManager::DrawManager(SceneManager_ptr sceneManager) 
	: m_drawVisitor(*this), m_sceneListener(*this), m_sceneManager(sceneManager), m_glContext(new QGLContext(GL_FORMAT)) {
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

void DrawManager::doDraw(RenderStateNode& renderStateNode, RigidAffineTransformation& rigidAffineTransformation) {
	m_modelMatrix = rigidAffineTransformation.toMatrix4x4();
	m_normalMatrix = glm::inverse(glm::transpose(rigidAffineTransformation.getMatrix()));
	hpmat4x4 modelViewProjectionMatrix = m_projectionMatrix * m_viewMatrix * m_modelMatrix;

	glBindVertexArray(renderStateNode.getVertexArrayObjectID());
	glUniformMatrix4fv(m_modelMatrixLocation, 1, GL_FALSE, (GLfloat*) &m_modelMatrix);
	glUniformMatrix4fv(m_modelViewProjectionMatrixLocation, 1, GL_FALSE, (GLfloat*) &modelViewProjectionMatrix);
	glUniformMatrix3fv(m_normalMatrixLocation, 1, GL_FALSE, (GLfloat*) &m_normalMatrix);
	glUniform1f(m_ambientFactorLocation, (GLfloat) renderStateNode.getMaterial().getAmbientFactor());
	glUniform1f(m_diffuseFactorLocation, (GLfloat) renderStateNode.getMaterial().getDiffuseFactor());
	glUniform1f(m_specularFactorLocation, (GLfloat) renderStateNode.getMaterial().getSpecularFactor());
	glUniform1f(m_phongExponentLocation, (GLfloat) renderStateNode.getMaterial().getPhongExponent());
	glUniform3f(m_cameraPositionLocation, m_cameraPosition.x, m_cameraPosition.y, m_cameraPosition.z);
	if (renderStateNode.hasColorVector()) {
		glUniform4f(m_colorComponentLocation, 0.0f, 0.0f, 0.0f, 0.0f);
		glUniform1i(m_isColoredLocation, 1);
	} else {
		hpcolor color = renderStateNode.getColor();
		glUniform4f(m_colorComponentLocation, color.x, color.y, color.z, color.w);
		glUniform1i(m_isColoredLocation, 0);
	}
	int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(GL_TRIANGLES, size / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void DrawManager::draw(hpmat4x4& projectionMatrix, hpmat4x4& viewMatrix, hpvec3& cameraPosition) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(m_program);

	m_modelMatrix = hpmat4x4(1.0f);
	m_viewMatrix = viewMatrix;
	m_projectionMatrix = projectionMatrix;
	m_cameraPosition = cameraPosition;

	RigidAffineTransformation identityTransformation;
	m_sceneManager->draw(m_drawVisitor, identityTransformation);
}

QGLContext* DrawManager::getGlContext() {
	return m_glContext;
}

bool DrawManager::init() {
	m_glContext->create();
	m_glContext->makeCurrent();

	GLenum errorCode = glewInit();
	if (GLEW_OK != errorCode) {
		fprintf(stderr, "Glew initialization failed: %s\n", glewGetErrorString(errorCode));
		return false;
	}

	QGLFormat glFormat = m_glContext->format();
	if (!glFormat.sampleBuffers())
		qWarning() << "Could not enable sample buffers";

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	if (!initShaderPrograms())
		return false;
	return true;
}

void DrawManager::initialize(RenderStateNode& renderStateNode) {
	GLuint bufferID;
	GLint size = (renderStateNode.getVertexData()->size());
	// Create New VertexArrayObject
	glGenVertexArrays(1, &bufferID);
	renderStateNode.setVertexArrayObjectID(bufferID);
	glBindVertexArray(renderStateNode.getVertexArrayObjectID());

	// Create New Vertex Buffer Object
	glGenBuffers(1, &bufferID);
	renderStateNode.setVertexBufferID(bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, renderStateNode.getVertexBufferID());
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(hpvec3), &(renderStateNode.getVertexData()->at(0)), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(m_vertexLocation, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(hpvec3), 0);
	glVertexAttribPointer(m_normalLocation, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(hpvec3), (void*) sizeof(hpvec3));
	glEnableVertexAttribArray(m_vertexLocation);
	glEnableVertexAttribArray(m_normalLocation);

	// Create New Color Buffer Object
	if (renderStateNode.hasColorVector()) {
		glGenBuffers(1, &bufferID);
		renderStateNode.setColorBufferID(bufferID);
		glBindBuffer(GL_ARRAY_BUFFER, renderStateNode.getColorBufferID());
		glBufferData(GL_ARRAY_BUFFER, renderStateNode.getColorVector()->size() * sizeof(glm::vec4), renderStateNode.getColorVector(), GL_DYNAMIC_DRAW);
		glVertexAttribPointer(m_colorLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(m_colorLocation);

	}
	// Create IndexBuffer;
	size= renderStateNode.getIndices()->size();
	glGenBuffers(1, &bufferID);
	renderStateNode.setIndexBufferID(bufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderStateNode.getIndexBufferID());
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLuint), &(renderStateNode.getIndices()->at(0)), GL_DYNAMIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	renderStateNode.setInitialized(true);
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
	m_isColoredLocation = glGetUniformLocation(m_program, "isColored");
	if (m_isColoredLocation < 0)
		cerr << "Failed to find isColored." << endl;
	//Camera and Light uniforms
	m_cameraPositionLocation = glGetUniformLocation(m_program, "cameraPosition");
	if (m_cameraPositionLocation < 0)
		cerr << "Failed to find cameraPositionLocation." << endl;

	return true;
}

DrawManager::DefaultDrawVisitor::DefaultDrawVisitor(DrawManager& drawManager)
	: m_drawManager(drawManager) {}

DrawManager::DefaultDrawVisitor::~DefaultDrawVisitor() {}

void DrawManager::DefaultDrawVisitor::draw(RenderStateNode& renderStateNode, RigidAffineTransformation& rigidAffineTransformation) {
	// If no Buffer has been assigned, assign one, and write Data into it
	if (!renderStateNode.isInitialized())
		m_drawManager.initialize(renderStateNode);
	m_drawManager.doDraw(renderStateNode, rigidAffineTransformation);
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


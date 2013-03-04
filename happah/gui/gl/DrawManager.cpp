#define GLEW_STATIC //Very important for Windows users
#include <GL/glew.h>
#include <GL/gl.h>
#include "happah/scene/Material.h"
#include "happah/gui/gl/DrawManager.h"


#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
HappahGlFormat::HappahGlFormat() {
	setVersion(3, 3);
	setProfile(QGLFormat::CompatibilityProfile);
	setSampleBuffers(true);
	setDoubleBuffer(true);
	setDepth(true);
}

const HappahGlFormat DrawManager::GL_FORMAT;

DrawManager::DrawManager(SceneManager& sceneManager) 
	: m_sceneManager(sceneManager), m_glContext(GL_FORMAT) {
	m_sceneManager.registerListener(this);
}

QGLContext& DrawManager::getGlContext() {
	return m_glContext;
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
	if(linkStatus == GL_FALSE) cerr << "Linking failed." << endl;
	else cout << "Linking was successful." << endl;

	// Vertex Attributes
	m_vertexLocation = glGetAttribLocation(m_program, "vertex");
	if(m_vertexLocation < 0) cerr << "Failed to find vertexLocation." << endl;
	m_normalLocation = glGetAttribLocation(m_program, "normal");
	if(m_normalLocation < 0) cerr << "Failed to find normalLocation." << endl;
	m_colorLocation = glGetAttribLocation(m_program, "color");
	if( m_colorLocation < 0 ) cerr << "Failed to find colorLocation." <<endl;

	// Matrix Uniforms
	m_modelMatrixLocation = glGetUniformLocation(m_program, "modelMatrix");
	if(m_modelMatrixLocation < 0) cerr << "Failed to find ModelMatrixLocation." << endl;
	m_modelViewProjectionMatrixLocation = glGetUniformLocation(m_program, "modelViewProjectionMatrix");
	if(m_modelViewProjectionMatrixLocation < 0) cerr << "Failed to find modelViewProjectionMatrixLocation." << endl;
	m_normalMatrixLocation = glGetUniformLocation(m_program, "normalMatrix");
	if(m_normalMatrixLocation < 0) cerr << "Failed to find normalMatrixLocation." << endl;

	// Material uniforms
	m_ambientFactorLocation = glGetUniformLocation(m_program, "ambientFactor");
		if(m_ambientFactorLocation < 0) cerr << "Failed to find ambientFactorLocation." << endl;
	m_diffuseFactorLocation = glGetUniformLocation(m_program, "diffuseFactor");
	if(m_diffuseFactorLocation < 0) cerr << "Failed to find diffuseFactorLocation." << endl;
	m_specularFactorLocation = glGetUniformLocation(m_program, "specularFactor");
	if(m_specularFactorLocation < 0) cerr << "Failed to find specularFactorLocation." << endl;
	m_phongExponentLocation = glGetUniformLocation(m_program, "phongExponent");
	if(m_phongExponentLocation < 0) cerr << "Failed to find phongLocation." << endl;
	m_colorComponentLocation = glGetUniformLocation(m_program, "colorComponent");
	if(m_colorComponentLocation < 0) cerr << "Failed to find color Component." << endl;
	m_isColoredLocation = glGetUniformLocation(m_program, "isColored");
	if(m_isColoredLocation < 0) cerr << "Failed to find isColored." << endl;
	//Camera and Light uniforms
	m_cameraPositionLocation = glGetUniformLocation(m_program, "cameraPosition");
	if(m_cameraPositionLocation < 0) cerr << "Failed to find cameraPositionLocation." << endl;


	return true;
}

void DrawManager::compileShader(GLuint shader, const char* filePath) {
	ifstream sourceFile(filePath);
	if(sourceFile) {
		stringstream temp;
		temp << sourceFile.rdbuf();
		sourceFile.close();
		string sourceString = temp.str();
		const char* source = sourceString.c_str();
		int sourceStringLength = sourceString.length();
		glShaderSource(shader, 1, (const GLchar**)&source, &sourceStringLength);
		glCompileShader(shader);
		GLint compileStatus;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
		if(compileStatus == GL_FALSE){
		    char log[256];
		    glGetShaderInfoLog(shader, 256, NULL, log);
		    cerr << "Compilation of shader failed." << endl;
		    printf(" Infolog: %s\n", log);
		}
		else cout << "Compilation was successful." << endl;
	} else cerr << "Failed to open source file." << endl;
}

bool DrawManager::createBuffers() {

	glGenVertexArrays(1, &m_coloredVertexArrayObject);
	glBindVertexArray(m_coloredVertexArrayObject);
    glGenVertexArrays(1, &m_unColoredVertexArrayObject);
    glBindVertexArray(m_unColoredVertexArrayObject);
    glBindVertexArray(0);

   return true;
}

void DrawManager::draw(QMatrix4x4* projectionMatrix, QMatrix4x4* viewMatrix, QVector3D* cameraPosition) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(m_program);




		QMatrix4x4 vMatrix = *viewMatrix;
		QMatrix4x4 pMatrix = *projectionMatrix;
		GLfloat viewMatrixFloats[16];
		GLfloat projectionMatrixFloats[16];



		const qreal* viewMatrixQreals = vMatrix.constData();
		const qreal* projectionMatrixQreals = pMatrix.constData();



		for (int j = 0; j < 16; ++j) {
	            viewMatrixFloats[j] = viewMatrixQreals[j];
	            projectionMatrixFloats[j] = projectionMatrixQreals[j];

		}
		

		m_modelMatrix = glm::mat4(1.0f);
		m_viewMatrix = glm::make_mat4(viewMatrixFloats);
		m_projectionMatrix = glm::make_mat4(projectionMatrixFloats);
		m_cameraPosition.x = cameraPosition->x();
		m_cameraPosition.y =cameraPosition->y();
		m_cameraPosition.z =cameraPosition->z();

		RigidAffineTransformation identityTransformation;
		m_sceneManager.draw(*this, identityTransformation);


}

void DrawManager::sceneChanged(){

}

void DrawManager::draw(TriangleMeshRenderStateNode& triangleMeshRenderStateNode, RigidAffineTransformation& rigidAffineTransformation) {
	// If no Buffer has been assigned, assign one, and write Data into it
	if (!triangleMeshRenderStateNode.isInitialized())
		initialize(triangleMeshRenderStateNode);

	drawObject(triangleMeshRenderStateNode,rigidAffineTransformation);
}

bool DrawManager::initGL(){
	m_glContext.create();
	m_glContext.makeCurrent();

	GLenum errorCode = glewInit();
	if (GLEW_OK != errorCode) {
		fprintf(stderr, "Glew initialization failed: %s\n", glewGetErrorString(errorCode));
		return false;
	}

	QGLFormat glFormat = m_glContext.format();
	if (!glFormat.sampleBuffers())
		qWarning() << "Could not enable sample buffers";

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable (GL_DEPTH_TEST);
	if(!initShaderPrograms())
		return false;
	if(!createBuffers())
		return false;
	return true;
}



void DrawManager::initialize(TriangleMeshRenderStateNode& triangleMeshRenderStateNode){
	// Bind Proper  VERTEX ARRAY OBJECT therefore
	//Check if Color Vector exists
	if(triangleMeshRenderStateNode.hasColorVector()){
		// exists!
		triangleMeshRenderStateNode.setVertexArrayObjectID(m_coloredVertexArrayObject);
		glBindVertexArray(triangleMeshRenderStateNode.getVertexArrayObjectID());
	}
	else {
		triangleMeshRenderStateNode.setVertexArrayObjectID(m_unColoredVertexArrayObject);
		glBindVertexArray(triangleMeshRenderStateNode.getVertexArrayObjectID());
	}

	// Create New Vertex Buffer Object
	GLuint bufferID;
	GLint size = (triangleMeshRenderStateNode.getTriangleMesh()->getVertexData()->size());
	glGenBuffers(1, &bufferID);
	triangleMeshRenderStateNode.setVertexBufferID(bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, triangleMeshRenderStateNode.getVertexBufferID());
	glBufferData(GL_ARRAY_BUFFER, size*sizeof(glm::vec4), &(triangleMeshRenderStateNode.getTriangleMesh()->getVertexData()->at(0)), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(m_vertexLocation, 4, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec4), 0);
	glVertexAttribPointer(m_normalLocation, 4, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec4), (void*)sizeof(glm::vec4));
    glEnableVertexAttribArray(m_vertexLocation);
    glEnableVertexAttribArray(m_normalLocation);

    // Create New Color Buffer Object
    if(triangleMeshRenderStateNode.getVertexArrayObjectID() == m_coloredVertexArrayObject){
        glGenBuffers(1, &bufferID);
        triangleMeshRenderStateNode.setColorBufferID(bufferID);
        glBindBuffer(GL_ARRAY_BUFFER, triangleMeshRenderStateNode.getColorBufferID());
       glBufferData(GL_ARRAY_BUFFER,triangleMeshRenderStateNode.getColorVector()->size()*sizeof(glm::vec4), triangleMeshRenderStateNode.getColorVector(), GL_DYNAMIC_DRAW);
       glVertexAttribPointer(m_colorLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);
       glEnableVertexAttribArray(m_colorLocation);

    }
    // CREATE NEW INDEX BUFFER OBJECT
    // TODO : GET INDICES FROM RENDERSTATE OBJECT
    // TODO : THEN REMOVE THIS
    std::vector<unsigned int> indices;
    for(int j=0 ;j < triangleMeshRenderStateNode.getTriangleMesh()->getVertexData()->size() ; j++)
    	indices.push_back(j);
    // TODO : UNTIL HERE
    glGenBuffers(1,&bufferID);
    triangleMeshRenderStateNode.setIndexBufferID(bufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,triangleMeshRenderStateNode.getIndexBufferID());
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,size*sizeof(GLuint),&indices[0],GL_DYNAMIC_DRAW);
   glBindVertexArray(0);
   glBindBuffer(GL_ARRAY_BUFFER,0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
   triangleMeshRenderStateNode.setInitialized(true);
}

void DrawManager::drawObject(TriangleMeshRenderStateNode& triangleMeshRenderStateNode,RigidAffineTransformation& rigidAffineTransformation){
	GLuint colorState = triangleMeshRenderStateNode.getVertexArrayObjectID();
	m_modelMatrix = rigidAffineTransformation.toMatrix4x4();
	m_normalMatrix = glm::inverse(glm::transpose(rigidAffineTransformation.getMatrix()));
	hpmat4x4 modelViewProjectionMatrix = m_projectionMatrix * m_viewMatrix * m_modelMatrix;
		if (colorState == m_coloredVertexArrayObject){
			// DRAW WITH COLOR BUFFER
			glBindVertexArray(colorState);
			glBindBuffer(GL_ARRAY_BUFFER, triangleMeshRenderStateNode.getVertexBufferID());
			glBindBuffer(GL_ARRAY_BUFFER, triangleMeshRenderStateNode.getColorBufferID());
			glVertexAttribPointer(m_vertexLocation, 4, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec4), 0);
			glVertexAttribPointer(m_normalLocation, 4, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec4), (void*)sizeof(glm::vec4));
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleMeshRenderStateNode.getIndexBufferID());
		    glVertexAttribPointer(m_colorLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);
			glUniformMatrix4fv(m_modelMatrixLocation, 1, GL_FALSE, (GLfloat*)&m_modelMatrix);
			glUniformMatrix4fv(m_modelViewProjectionMatrixLocation, 1, GL_FALSE, (GLfloat*)&modelViewProjectionMatrix);
			glUniformMatrix3fv(m_normalMatrixLocation, 1, GL_FALSE,(GLfloat*) &m_normalMatrix);
			glUniform1f(m_ambientFactorLocation,(GLfloat)triangleMeshRenderStateNode.getMaterial().getAmbientFactor());
			glUniform1f(m_diffuseFactorLocation,(GLfloat)triangleMeshRenderStateNode.getMaterial().getDiffuseFactor());
			glUniform1f(m_specularFactorLocation,(GLfloat)triangleMeshRenderStateNode.getMaterial().getSpecularFactor());
			glUniform1f(m_phongExponentLocation,(GLfloat)triangleMeshRenderStateNode.getMaterial().getPhongExponent());
			glUniform3f(m_cameraPositionLocation,m_cameraPosition.x,m_cameraPosition.y,m_cameraPosition.z );
			glUniform4f(m_colorComponentLocation,1.0f,0.0f,0.0f,0.0f); // TODO : REMOVE OR SET TO ZERO
			glUniform1i(m_isColoredLocation,1);
			int size;
			glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER,GL_BUFFER_SIZE,&size);
			glDrawElements(GL_TRIANGLES,size/sizeof(unsigned int),GL_UNSIGNED_INT,0);
			//std::cout << "Object drawn" << std::endl;
			glBindVertexArray(0);
		}
		if (colorState == m_unColoredVertexArrayObject){
			// DRAW WITH SINGLE COLOR
			glBindVertexArray(colorState);
			hpcolor color = triangleMeshRenderStateNode.getColor();
			glBindBuffer(GL_ARRAY_BUFFER, triangleMeshRenderStateNode.getVertexBufferID());
			glVertexAttribPointer(m_vertexLocation, 4, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec4), 0);
			glVertexAttribPointer(m_normalLocation, 4, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec4), (void*)sizeof(glm::vec4));
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleMeshRenderStateNode.getIndexBufferID());
			glUniformMatrix4fv(m_modelMatrixLocation, 1, GL_FALSE, (GLfloat*)&m_modelMatrix);
			glUniformMatrix4fv(m_modelViewProjectionMatrixLocation, 1, GL_FALSE, (GLfloat*)&modelViewProjectionMatrix);
			glUniformMatrix3fv(m_normalMatrixLocation, 1, GL_FALSE,(GLfloat*) &m_normalMatrix);
			glUniform1f(m_ambientFactorLocation,(GLfloat)triangleMeshRenderStateNode.getMaterial().getAmbientFactor());
			glUniform1f(m_diffuseFactorLocation,(GLfloat)triangleMeshRenderStateNode.getMaterial().getDiffuseFactor());
			glUniform1f(m_specularFactorLocation,(GLfloat)triangleMeshRenderStateNode.getMaterial().getSpecularFactor());
			glUniform1f(m_phongExponentLocation,(GLfloat)triangleMeshRenderStateNode.getMaterial().getPhongExponent());
			glUniform3f(m_cameraPositionLocation,m_cameraPosition.x,m_cameraPosition.y,m_cameraPosition.z );
			glUniform4f(m_colorComponentLocation,color.x,color.y,color.z,color.w);
			glUniform1i(m_isColoredLocation,0);
			int size;

			glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER,GL_BUFFER_SIZE,&size);
			glDrawElements(GL_TRIANGLES,size/sizeof(unsigned int),GL_UNSIGNED_INT,0);

			glBindVertexArray(0);
		}
		if (colorState != m_coloredVertexArrayObject && colorState != m_unColoredVertexArrayObject)
		{
			// DRAW NOTHING YET
			std::cout << "Nothing to Draw" << endl;
		}

}


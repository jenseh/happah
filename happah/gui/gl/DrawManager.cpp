#define GLEW_STATIC //Very important for Windows users
#include <GL/glew.h>
#include <GL/gl.h>
#include "happah/models/Material.h"
#include "happah/gui/gl/DrawManager.h"


#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

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

	//Vertex Buffer
	std::vector<Drawable*> *drawables = m_sceneManager.getDrawables();
	int nBytes = 0;

		for (vector<Drawable*>::iterator i = drawables->begin(), end = drawables->end(); i != end; ++i) {
			nBytes += (*i)->getVertexData()->size() * sizeof(glm::vec4);
		}

	glGenVertexArrays(1, &m_coloredVertexArrayObject);
	glBindVertexArray(m_coloredVertexArrayObject);

	glGenBuffers(1, &m_vertexDataBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexDataBuffer);
	glBufferData(GL_ARRAY_BUFFER, nBytes, NULL, GL_STATIC_DRAW);
	
	int offset = 0;
	for (vector<Drawable*>::iterator i = drawables->begin(), endi = drawables->end(); i != endi; ++i) {
	    vector<glm::vec4>* vertexData = (*i)->getVertexData();

	    int vertexDataSize = vertexData->size() * sizeof(glm::vec4);
	    glBufferSubData(GL_ARRAY_BUFFER, offset, vertexDataSize, &(vertexData->at(0)));
	    offset += vertexDataSize;
	}
	glVertexAttribPointer(m_vertexLocation, 4, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec4), 0);
	glVertexAttribPointer(m_normalLocation, 4, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec4), (void*)sizeof(glm::vec4));
    
    glEnableVertexAttribArray(m_vertexLocation);
    glEnableVertexAttribArray(m_normalLocation);


    //INDEX BUFFER
    nBytes= 0;
    for (vector<Drawable*>::iterator i = drawables->begin(), end = drawables->end(); i != end; ++i) {
    			nBytes += (*i)->getVertexData()->size() * sizeof(unsigned int);
    		}
    glGenBuffers(1,&m_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,nBytes,NULL,GL_STATIC_DRAW);
    
    //Fill index Buffer :
    unsigned int indexOffset = 0;
    for (vector<Drawable*>::iterator i = drawables->begin(), endi = drawables->end(); i != endi; ++i) {
    	std::vector<unsigned int> indices;
    	for (unsigned int j=0; j < (*i)->getVertexData()->size();j++){
    		indices.push_back(indexOffset+j);

    	}
    	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,indexOffset*sizeof(unsigned int),indices.size()*sizeof(unsigned int),&indices[0]);
    	indexOffset += (*i)->getVertexData()->size();
    	std::cout << "IndexOffset = " << indexOffset << std::endl;
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    // COLOR BUFFER
    nBytes = 0;
    for (vector<Drawable*>::iterator i = drawables->begin(), end = drawables->end(); i != end; ++i) {
      nBytes += (*i)->getColorData()->size() * sizeof(Color);
    }
    if (nBytes > 0) {
        glGenBuffers(1, &m_colorDataBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_colorDataBuffer);
        glBufferData(GL_ARRAY_BUFFER, nBytes, NULL, GL_STATIC_DRAW);
        
    offset = 0;
    for (vector<Drawable*>::iterator i = drawables->begin(), endi = drawables->end(); i != endi; ++i) {
          vector<Color>* colorData = (*i)->getColorData();
          if( !colorData->empty() ){
                int colorDataSize = colorData->size()*sizeof(Color);
                std::cout << "size of Color: " << sizeof(Color) << endl;
                std::cout << " ColorDataSize for buffer: " << colorDataSize << endl;
                glBufferSubData(GL_ARRAY_BUFFER, offset, colorDataSize, &(colorData->at(0)));
                offset += colorDataSize;
            }
        }
    glVertexAttribPointer(m_colorLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(m_colorLocation);
    glBindVertexArray(0);
    
    }
   return true;
}

void DrawManager::draw(QMatrix4x4* projectionMatrix, QMatrix4x4* viewMatrix, QVector3D* cameraPosition) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(m_program);
	glBindVertexArray(m_coloredVertexArrayObject);
	int offset = 0;
	std::vector<Drawable*> *drawables = m_sceneManager.getDrawables();
	for (vector<Drawable*>::iterator i = drawables->begin(), end = drawables->end(); i != end; ++i) {
		QMatrix4x4 modelMatrix = *((*i)->getModelMatrix());
		QMatrix4x4 MVP = *projectionMatrix * *viewMatrix * modelMatrix;
		QMatrix3x3 normalMatrix = modelMatrix.normalMatrix(); //Do not change this to "inverted" again!
		GLfloat modelMatrixFloats[16];
		GLfloat MVPFloats[16];
		GLfloat normalMatrixFloats[9];


		const qreal* modelMatrixQreals = modelMatrix.constData();
		const qreal* MVPQreals = MVP.constData();
		const qreal* normalMatrixQreals = normalMatrix.constData();


		for (int j = 0; j < 16; ++j) {
	            modelMatrixFloats[j] = modelMatrixQreals[j];
	            MVPFloats[j] = MVPQreals[j];

		}
		
		for (int j = 0; j < 9; ++j) {
		    normalMatrixFloats[j] = normalMatrixQreals[j];

		}



		Material material = (*i)->getMaterial();

		glUniformMatrix4fv(m_modelMatrixLocation, 1, GL_FALSE, modelMatrixFloats);
		glUniformMatrix4fv(m_modelViewProjectionMatrixLocation, 1, GL_FALSE, MVPFloats);
		glUniformMatrix3fv(m_normalMatrixLocation, 1, GL_FALSE, normalMatrixFloats);
		glUniform1f(m_ambientFactorLocation,material.getKa());
		glUniform1f(m_diffuseFactorLocation,material.getKd());
		glUniform1f(m_specularFactorLocation,material.getKs());
		glUniform1f(m_phongExponentLocation,material.getShininess());
		glUniform3f(m_cameraPositionLocation, cameraPosition->x(), cameraPosition->y(), cameraPosition->z());

		int vertexDataSize = (*i)->getVertexData()->size();

		int tupleSize = (*i)->getTupleSize();
		int mode = tupleSize == 4 ? GL_QUADS : tupleSize == 3 ? GL_TRIANGLES : -1;
		if (mode == -1) {
		    std::cerr << "Error: Invalid tupleSize in DrawManager!" << std::endl;
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
		int size;
		glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER,GL_BUFFER_SIZE,&size);
		glDrawElements(mode,size/sizeof(unsigned int),GL_UNSIGNED_INT,0);
		//glDrawArrays(mode, offset, vertexDataSize);

		offset += vertexDataSize;
	}
	glBindVertexArray(0);
}

void DrawManager::sceneChanged(){
	createBuffers();
}

void DrawManager::visit(InvoluteGearNode& involuteGearNode){}

void DrawManager::visit(TriangleMeshNode& triangleMeshNode){}

void DrawManager::visit(TriangleMeshRenderStateNode& triangleMeshRenderStateNode){



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

#define GLEW_STATIC //Very important for Windows users
#include <GL/glew.h>
#include <GL/gl.h>
#include "happah/models/Material.h"
#include "happah/gui/gl/DrawManager.h"

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

DrawManager::DrawManager(SceneManager* sceneManager) : m_sceneManager(sceneManager) {
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glClearDepth(1.0f);
	glEnable (GL_DEPTH_TEST);
	m_sceneManager->registerListener(this);
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
	m_MMatrixLocation = glGetUniformLocation(m_program, "MMatrix");
	if(m_MMatrixLocation < 0) cerr << "Failed to find MMatrixLocation." << endl;
	m_MVPMatrixLocation = glGetUniformLocation(m_program, "MVPMatrix");
	if(m_MVPMatrixLocation < 0) cerr << "Failed to find MVPMatrixLocation." << endl;
	m_NMatrixLocation = glGetUniformLocation(m_program, "NMatrix");
	if(m_NMatrixLocation < 0) cerr << "Failed to find NMatrixLocation." << endl;

	// Material uniforms
	m_kaLocation = glGetUniformLocation(m_program, "ka");
		if(m_kaLocation < 0) cerr << "Failed to find kaLocation." << endl;
	m_kdLocation = glGetUniformLocation(m_program, "kd");
	if(m_kdLocation < 0) cerr << "Failed to find kdLocation." << endl;
	m_ksLocation = glGetUniformLocation(m_program, "ks");
	if(m_ksLocation < 0) cerr << "Failed to find ksLocation." << endl;
	m_phongLocation = glGetUniformLocation(m_program, "phong");
	if(m_phongLocation < 0) cerr << "Failed to find phongLocation." << endl;

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

void DrawManager::sceneChanged() {
	glEnable(GL_DEPTH_TEST);
	std::vector<Drawable*> *drawables = m_sceneManager->getDrawables();
	glGenVertexArrays(1, &m_coloredVertexArrayObject);
	glBindVertexArray(m_coloredVertexArrayObject);

        // Vertex Data
        //GLuint m_vertexDataBuffer;
	glGenBuffers(1, &m_vertexDataBuffer);

	int nBytes = 0;
	for (vector<Drawable*>::iterator i = drawables->begin(), end = drawables->end(); i != end; ++i) {
		nBytes += (*i)->getVertexData()->size() * sizeof(glm::vec4);
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexDataBuffer);
	glBufferData(GL_ARRAY_BUFFER, nBytes, NULL, GL_STATIC_DRAW);
	
	int offset = 0;
	for (vector<Drawable*>::iterator i = drawables->begin(), endi = drawables->end(); i != endi; ++i) {
	    vector<glm::vec4>* vertexData = (*i)->getVertexData();
	    	//TODO: remove debug part
//		{
//		  printf("Size: %d", vertexData->size());
//		  std::cout << (*i)->getName() << std::endl;
//		  for (vector<glm::vec4>::iterator it = vertexData->begin(), endit = vertexData->end(); it != endit; ++i) {
//		    glm::vec4 vec  = *it;
//		    printf("%4.2f\t%4.2f\t%4.2f\t%4.2f\n", vec.x, vec.y, vec.z, vec.w);
//		  }
//		}
		//TODO: until here
	    int vertexDataSize = vertexData->size() * sizeof(glm::vec4);
	    glBufferSubData(GL_ARRAY_BUFFER, offset, vertexDataSize, &(vertexData->at(0)));
	    offset += vertexDataSize;
	}
	glVertexAttribPointer(m_vertexLocation, 4, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec4), 0);
	glVertexAttribPointer(m_normalLocation, 4, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec4), (void*)sizeof(glm::vec4));
    
        glEnableVertexAttribArray(m_vertexLocation);
        glEnableVertexAttribArray(m_normalLocation);
    
    
    // Color Data
    nBytes = 0;
    for (vector<Drawable*>::iterator i = drawables->begin(), end = drawables->end(); i != end; ++i) {
      nBytes += (*i)->getColorData()->size() * sizeof(Color);
    }
    if (nBytes > 0) {
        glGenBuffers(2, &m_colorDataBuffer);
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
}

void DrawManager::draw(QMatrix4x4* projectionMatrix, QMatrix4x4* viewMatrix, QVector3D* cameraPosition) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(m_program);
	glBindVertexArray(m_coloredVertexArrayObject);
	int offset = 0;
	std::vector<Drawable*> *drawables = m_sceneManager->getDrawables();
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

		int hasVertexColor = (*i)->hasColorData();
		

		Material material = (*i)->getMaterial();

		glUniformMatrix4fv(m_MMatrixLocation, 1, GL_FALSE, modelMatrixFloats);
		glUniformMatrix4fv(m_MVPMatrixLocation, 1, GL_FALSE, MVPFloats);
		glUniformMatrix3fv(m_NMatrixLocation, 1, GL_FALSE, normalMatrixFloats);
		glUniform1f(m_kaLocation,material.getKa());
		glUniform1f(m_kdLocation,material.getKd());
		glUniform1f(m_ksLocation,material.getKs());
		glUniform1f(m_phongLocation,material.getShininess());
		glUniform3f(m_cameraPositionLocation, cameraPosition->x(), cameraPosition->y(), cameraPosition->z());

		int vertexDataSize = (*i)->getVertexData()->size();

		int tupleSize = (*i)->getTupleSize();
		int mode = tupleSize == 4 ? GL_QUADS : tupleSize == 3 ? GL_TRIANGLES : -1;
		if (mode == -1) {
		    std::cerr << "Error: Invalid tupleSize in DrawManager!" << std::endl;
		}
		glDrawArrays(mode, offset, vertexDataSize);

		offset += vertexDataSize;
	}
	glBindVertexArray(0);
}

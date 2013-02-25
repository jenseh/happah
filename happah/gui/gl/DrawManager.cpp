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
	compileShader(m_vertexShader, "./src/shader/phong410Vert.glsl");

	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	compileShader(m_fragmentShader, "./src/shader/phong410Frag.glsl");

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
	if(m_vertexLocation < 0) cerr << "Failed to find vertex." << endl;

	m_normalLocation = glGetAttribLocation(m_program, "normal");
	if(m_normalLocation < 0) cerr << "Failed to find normal." << endl;

	m_vertexColor = glGetAttribLocation(m_program, "color");
	if( m_vertexColor < 0 ) cerr << "Failed to find color." <<endl;

	// Matrix Uniforms
	m_eyeLocation = glGetUniformLocation(m_program, "eye");
	if(m_eyeLocation < 0) cerr << "Failed to find eye." << endl;

	m_modelMatrixLocation = glGetUniformLocation(m_program, "modelMatrix");
	if(m_modelMatrixLocation < 0) cerr << "Failed to find model matrix." << endl;

	m_MVPLocation = glGetUniformLocation(m_program, "MVP");
	if(m_MVPLocation < 0) cerr << "Failed to find MVP." << endl;



	m_normalMatLocation = glGetUniformLocation(m_program, "normalMat");
	if(m_normalMatLocation < 0) cerr << "Failed to find normal matrix." << endl;


	m_phong = glGetUniformLocation(m_program, "phong");
	if(m_phong < 0) cerr << "Failed to find phong exponent." << endl;



	// Material uniforms

	m_diffuseColorLocation = glGetUniformLocation(m_program, "kd");
	if(m_diffuseColorLocation < 0) cerr << "Failed to find diffuse color component." << endl;

	std::cout << "kd Location: " << m_diffuseColorLocation << std::endl;

	m_ambientColorLocation = glGetUniformLocation(m_program, "ka");
	if(m_ambientColorLocation < 0) cerr << "Failed to find ambient color component." << endl;

	std::cout << "ka Location: " << m_ambientColorLocation << std::endl;

	m_specularColorLocation = glGetUniformLocation(m_program, "ks");
	if(m_specularColorLocation < 0) cerr << "Failed to find specular color component." << endl;

	std::cout << "ks Location: " << m_specularColorLocation << std::endl;

	m_shininessLocation = glGetUniformLocation(m_program, "shininess");
	if(m_shininessLocation < 0) cerr << "Failed to find shininess." << endl;

	std::cout << "Shininess Location: " << m_shininessLocation << std::endl;

	//m_hasVertexColorLocation =  glGetUniformLocation(m_program, "hasVertexColor");
	//if(m_hasVertexColorLocation < 0) cerr << "Failed to check for color component." << endl;


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
        glVertexAttribPointer(m_vertexColor, 4, GL_FLOAT, GL_FALSE, 0, 0);
    
        glEnableVertexAttribArray(m_vertexColor);
    
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
		
		//TODO: Remove debug part
//		std::cout << (*i)->getName() << ", offset: " <<  offset << std::endl;
//		printf("Camera: %4.1f\t %4.1f\t %4.1f\t\n", cameraPosition->x(), cameraPosition->y(), cameraPosition->z());
		
		
//		for (int k = 0; k < 4; k++) {
//		  for (int j = 0; j < 4; j++) {
//		      printf("%4.1f\t\t", MVPQreals[j*4+k]);
//		  }
//		  std::cout << std::endl;
//		}
//		std::cout << "##########" << std::endl;
		
//		for (int k = 0; k < 3; k++) {
//		  for (int j = 0; j < 3; j++) {
//		      printf("%4.1f\t\t", normalMatrixFloats[j*3+k]);
//		  }
//		  std::cout << std::endl;
//		}
//		std::cout << "----------------" << std::endl;
		//TODO: until here
		Material material = (*i)->getMaterial();

		glUniformMatrix4fv(m_modelMatrixLocation, 1, GL_FALSE, modelMatrixFloats);
		glUniformMatrix4fv(m_MVPLocation, 1, GL_FALSE, MVPFloats);
		glUniform1f(m_phong,material.getShininess());
		glUniformMatrix3fv(m_normalMatLocation, 1, GL_FALSE, normalMatrixFloats);
		glUniform3f(m_eyeLocation, cameraPosition->x(), cameraPosition->y(), cameraPosition->z());
		glUniform1f(m_ambientColorLocation,material.getKa());
		glUniform1f(m_diffuseColorLocation,material.getKd());
		glUniform1f(m_specularColorLocation,material.getKs());
		glUniform1i(m_hasVertexColorLocation, hasVertexColor);

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

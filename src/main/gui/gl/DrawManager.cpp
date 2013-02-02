#define GLEW_STATIC //Very important for Windows users
#include <GL/glew.h>
#include <GL/gl.h>
#include "DrawManager.h"

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

DrawManager::DrawManager() {
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glClearDepth(1.0f);
	glEnable (GL_DEPTH_TEST);
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
	if(linkStatus == GL_FALSE)
		cerr << "Linking failed." << endl;
	else
		cout << "Linking was successful." << endl;
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

	m_MVLocation = glGetUniformLocation(m_program, "MV");
	if(m_MVLocation < 0) cerr << "Failed to find MV." << endl;

	m_MVPLocation = glGetUniformLocation(m_program, "MVP");
	if(m_MVPLocation < 0) cerr << "Failed to find MVP." << endl;

	m_normalMatLocation = glGetUniformLocation(m_program, "normalMat");
	if(m_normalMatLocation < 0) cerr << "Failed to find normal matrix." << endl;

	// Material uniforms
	m_shininessLocation = glGetUniformLocation(m_program, "shininess");
	if(m_shininessLocation < 0) cerr << "Failed to find shininess." << endl;
	else glUniform1f(m_shininessLocation, 20.0f);

	m_diffuseColorLocation = glGetUniformLocation(m_program, "kd");
	if(m_diffuseColorLocation < 0) cerr << "Failed to find diffuse color komponent." << endl;
	else glUniform1f(m_diffuseColorLocation, 1.0f);

	m_ambientColorLocation = glGetUniformLocation(m_program, "ka");
	if(m_ambientColorLocation < 0) cerr << "Failed to find ambient color komponent." << endl;
	else glUniform1f(m_ambientColorLocation, 1.0f);

	m_specularColorLocation = glGetUniformLocation(m_program, "ks");
	if(m_specularColorLocation < 0) cerr << "Failed to find specular color komponent." << endl;
	else glUniform1f(m_specularColorLocation, 1.0f);

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
		    glGetShaderInfoLog( shader, 256, NULL, log);
		    cerr << "Compilation of shader failed." << endl;
		    printf(" Infolog: %s\n", log);
		}
		else
			cout << "Compilation was successful." << endl;
	} else
		cerr << "Failed to open source file." << endl;
}

void DrawManager::createBufferFor(std::vector<Drawable*> *drawables) {
	glGenVertexArrays(1, &m_coloredVertexArrayObject);
	glBindVertexArray(m_coloredVertexArrayObject);

    // Vertex Data
    //GLuint m_vertexDataBuffer;
	glGenBuffers(1, &m_vertexDataBuffer);

	int nBytes = 0;
	for (vector<Drawable*>::iterator i = drawables->begin(), end = drawables->end(); i != end; ++i)
		nBytes += (*i)->getVertexData()->size() * sizeof(glm::vec4);

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



    // Color Data
    glGenBuffers(2, &m_colorDataBuffer);
    nBytes = 0;
    for (vector<Drawable*>::iterator i = drawables->begin(), end = drawables->end(); i != end; ++i)
        nBytes += (*i)->getColorData()->size() * sizeof(Color);

    glBindBuffer(GL_ARRAY_BUFFER, m_colorDataBuffer);
    glBufferData(GL_ARRAY_BUFFER, nBytes, NULL, GL_STATIC_DRAW);

    offset = 0;
    for (vector<Drawable*>::iterator i = drawables->begin(), endi = drawables->end(); i != endi; ++i) {
        vector<Color>* colorData = (*i)->getColorData();
        if( colorData->size() != 0 ){
            int colorDataSize = colorData->size()*sizeof(Color) ;
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

void DrawManager::draw(std::vector<Drawable*> *drawables, QMatrix4x4* projectionMatrix, QMatrix4x4* viewMatrix, QVector3D* cameraPosition) {
	updateBuffer(drawables);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(m_program);
	glBindVertexArray(m_coloredVertexArrayObject);
	int offset = 0;
	for (vector<Drawable*>::iterator i = drawables->begin(), end = drawables->end(); i != end; ++i) {
		QMatrix4x4 MV = *viewMatrix * *((*i)->getModelMatrix());
		QMatrix4x4 MVP = *projectionMatrix * MV;
		QMatrix4x4 normalMatrix = MV.inverted();

		GLfloat MVFloats[16];
		GLfloat MVPFloats[16];
		GLfloat normalMatrixFloats[16];

		const qreal* MVQreals = MV.constData();
		const qreal* MVPQreals = MVP.constData();
		const qreal* normalMatrixQreals = normalMatrix.constData();

		for (int i = 0; i < 16; ++i) {
	            MVFloats[i] = MVQreals[i];
	            MVPFloats[i] = MVPQreals[i];
		    normalMatrixFloats[i] = normalMatrixQreals[i];
		}



		glUniformMatrix4fv(m_MVLocation, 1, GL_FALSE, MVFloats);
		glUniformMatrix4fv(m_MVPLocation, 1, GL_FALSE, MVPFloats);
		glUniformMatrix4fv(m_normalMatLocation, 1, GL_FALSE, normalMatrixFloats);
		glUniform3f(m_eyeLocation, cameraPosition->x(), cameraPosition->y(), cameraPosition->z());
		glUniform1f(m_ambientColorLocation,(*i)->getMaterial().m_ka);
		glUniform1f(m_diffuseColorLocation,(*i)->getMaterial().m_kd);
		glUniform1f(m_specularColorLocation,(*i)->getMaterial().m_ks);
		glUniform1f(m_shininessLocation,(*i)->getMaterial().m_shininess);
		int vertexDataSize = (*i)->getVertexData()->size();

		int tupleSize = (*i)->getTupleSize();
		int mode = tupleSize == 4 ? GL_QUADS : tupleSize == 3 ? GL_TRIANGLES : -1;
		glDrawArrays(mode, offset, vertexDataSize);

		offset += vertexDataSize;
	}
	glBindVertexArray(0);
}

void DrawManager::updateBuffer(std::vector<Drawable *> *drawables){
  // TODO : Find something thats perfoming Better Here :
  createBufferFor(drawables);
}

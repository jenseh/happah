#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H

#include <GL/glew.h>
#include <vector>
#include "../../core/models/Drawable.h"

using namespace std;

class DrawManager {
public:
	DrawManager();

	void draw(std::vector<Drawable*> *drawables, QMatrix4x4* projectionMatrix, QMatrix4x4* viewMatrix, QVector3D* cameraPosition);
	bool initShaderPrograms();
	void createBufferFor(std::vector<Drawable*> *drawables);
	void updateBuffer(std::vector<Drawable*> *drawables);

private:

	void compileShader(GLuint shader, const char* filePath);
	GLuint m_fragmentShader;
	GLuint m_program;
	GLuint m_vertexShader;
	
	GLint m_eyeLocation;
	GLint m_MVLocation;
	GLint m_MVPLocation;
	GLint m_normalMatLocation;
	GLint m_normalLocation;
	GLint m_vertexLocation;
	GLint m_vertexColor;

	GLuint m_coloredVertexArrayObject;
	GLuint m_vertexDataBuffer;
	GLuint m_colorDataBuffer;

	GLint m_shininessLocation;
	GLint m_diffuseColorLocation;
	GLint m_ambientColorLocation;
	GLint m_specularColorLocation;

	GLint m_useColorLocation; // Wether the color buffer is used (1) or not (0)
};

#endif // DRAWMANAGER_H

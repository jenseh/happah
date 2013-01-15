#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H

#include <GL/gl.h>
#include "../../core/models/Drawable.h"

using namespace std;

class DrawManager {
public:
	DrawManager();

	void draw(QMatrix4x4* projectionMatrix, QMatrix4x4* viewMatrix, QVector3D* cameraPosition);
	void addDrawable(Drawable* drawable);
	bool initShaderPrograms();
	int createBuffer();

private:
	void compileShader(GLuint shader, const char* filePath);
	list<Drawable*> m_drawables;
	GLuint m_fragmentShader;
	GLuint m_program;
	GLuint m_vertexShader;
	
	GLint m_eyeLocation;
	GLint m_MVLocation;
	GLint m_MVPLocation;
	GLint m_normalMatLocation;
	GLint m_normalLocation;
	GLint m_vertexLocation;

	GLuint m_coloredVertexArrayObject;
	GLuint m_vertexDataBuffer;
};

#endif // DRAWMANAGER_H

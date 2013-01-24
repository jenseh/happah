#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H

#include <GL/glew.h>
#include <vector>
#include "../../core/SceneManager.h"
#include "../../core/models/Drawable.h"

using namespace std;

class DrawManager {
public:
	DrawManager(SceneManager* sceneManager);

	void draw(QMatrix4x4* projectionMatrix, QMatrix4x4* viewMatrix, QVector3D* cameraPosition);
	bool initShaderPrograms();
	void createBufferFor(std::vector<Drawable*> *drawables);

private:
	void compileShader(GLuint shader, const char* filePath);
	SceneManager *m_sceneManager;
	unsigned int m_sceneState;
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

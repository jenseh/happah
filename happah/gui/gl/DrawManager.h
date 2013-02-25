#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H

#include <GL/glew.h>
#include <vector>
#include "happah/models/Drawable.h"
#include "happah/scene/SceneManager.h"
#include "happah/gui/SceneListener.h"

class DrawManager : public SceneListener {
public:
	DrawManager(SceneManager* sceneManager);

	void draw(QMatrix4x4* projectionMatrix, QMatrix4x4* viewMatrix, QVector3D* cameraPosition);
	bool initGL();
	void sceneChanged();
private:

	void compileShader(GLuint shader, const char* filePath);
	bool createBuffers();
	bool initShaderPrograms();
	SceneManager* m_sceneManager;
	GLuint m_fragmentShader;
	GLuint m_program;
	GLuint m_vertexShader;

	GLuint m_vertexArrayObject;
	GLuint m_vertexDataBuffer;
	GLuint m_colorDataBuffer;

	//attribute locations
	GLint m_vertexLocation;
	GLint m_normalLocation;
	GLint m_colorLocation;

	//uniform locations
	GLint m_modelMatrixLocation;
	GLint m_modelViewProjectionMatrixLocation;
	GLint m_normalMatrixLocation;
	GLint m_ambientFactorLocation;
	GLint m_diffuseFactorLocation;
	GLint m_specularFactorLocation;
	GLint m_phongExponentLocation;
	GLint m_cameraPositionLocation;


};

#endif // DRAWMANAGER_H

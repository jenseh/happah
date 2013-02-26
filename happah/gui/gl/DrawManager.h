#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H

#include <GL/glew.h>
#include <QGLContext>
#include <QGLFormat>
#include <vector>

#include "happah/gui/SceneListener.h"
#include "happah/models/Drawable.h"
#include "happah/scene/SceneManager.h"

class HappahGlFormat : public QGLFormat {
public:
	HappahGlFormat();
};

class DrawManager : public SceneListener {
public:
	DrawManager(SceneManager& sceneManager);

	void draw(QMatrix4x4* projectionMatrix, QMatrix4x4* viewMatrix, QVector3D* cameraPosition);
	QGLContext& getGlContext();
	bool initGL();
	void sceneChanged();
private:

	void compileShader(GLuint shader, const char* filePath);
	bool createBuffers();
	bool initShaderPrograms();
	SceneManager& m_sceneManager;
	QGLContext m_glContext;

	GLuint m_fragmentShader;
	GLuint m_program;
	GLuint m_vertexShader;

	GLuint m_vertexArrayObject;
	GLuint m_vertexDataBuffer;
	GLuint m_indexBuffer;
	GLuint m_colorDataBuffer;
	GLuint m_coloredVertexArrayObject;

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

	const static HappahGlFormat GL_FORMAT;
};

#endif // DRAWMANAGER_H

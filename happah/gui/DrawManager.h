#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H

#include <GL/glew.h>
#include <QGLContext>
#include <QGLFormat>
#include <vector>

#include "happah/scene/DrawVisitor.h"
#include "happah/scene/RenderStateNode.h"

class HappahGlFormat : public QGLFormat {
public:
	HappahGlFormat();
};

class SceneManager;
class DrawManager : public DrawVisitor {
public:
	DrawManager(SceneManager& sceneManager);
	~DrawManager();
	void draw(QMatrix4x4* projectionMatrix, QMatrix4x4* viewMatrix, QVector3D* cameraPosition);
	void draw(RenderStateNode& renderStateNode, RigidAffineTransformation& rigidAffineTransformation);
	QGLContext* getGlContext();
	bool init();

private:
	void compileShader(GLuint shader, const char* filePath);
	void drawObject(RenderStateNode& triangleMeshRenderStateNode, RigidAffineTransformation& rigidAffineTransformation);
	void initialize(RenderStateNode& triangleMeshRenderStateNode);
	bool initShaderPrograms();

	SceneManager& m_sceneManager;
	QGLContext* m_glContext;

	GLuint m_fragmentShader;
	GLuint m_program;
	GLuint m_vertexShader;

	GLint m_vertexLocation;
	GLint m_normalLocation;
	GLint m_colorLocation;

	GLint m_modelMatrixLocation;
	GLint m_modelViewProjectionMatrixLocation;
	GLint m_normalMatrixLocation;
	GLint m_ambientFactorLocation;
	GLint m_diffuseFactorLocation;
	GLint m_specularFactorLocation;
	GLint m_colorComponentLocation;
	GLint m_isColoredLocation;
	GLint m_phongExponentLocation;
	GLint m_cameraPositionLocation;

	const static HappahGlFormat GL_FORMAT;

	hpmat4x4 m_modelMatrix;
	hpmat4x4 m_viewMatrix;
	hpmat4x4 m_projectionMatrix;
	hpmat3x3 m_normalMatrix;
	hpvec3   m_cameraPosition;


};

#include "happah/scene/SceneManager.h"

#endif // DRAWMANAGER_H

#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H

#include <GL/glew.h>
#include <QGLContext>
#include <QGLFormat>
#include <vector>

#include "happah/gui/SceneListener.h"
#include "happah/models/Drawable.h"
#include "happah/scene/SceneManager.h"
#include "happah/scene/SceneVisitor.h"

class HappahGlFormat : public QGLFormat {
public:
	HappahGlFormat();
};

class DrawManager : public SceneListener, public SceneVisitor {
public:
	DrawManager(SceneManager& sceneManager);

	void draw(QMatrix4x4* projectionMatrix, QMatrix4x4* viewMatrix, QVector3D* cameraPosition);
	QGLContext& getGlContext();
	bool initGL();
	void sceneChanged();

	void visit(InvoluteGearNode& involuteGearNode);
	void visit(TriangleMeshNode& triangleMeshNode);
	void visit(TriangleMeshRenderStateNode& triangleMeshRenderStateNode);


private:


	void compileShader(GLuint shader, const char* filePath);
	bool createBuffers();
	bool initShaderPrograms();
	void initialize(TriangleMeshRenderStateNode& triangleMeshRenderStateNode);
	void drawObject(TriangleMeshRenderStateNode& triangleMeshRenderStateNode);
	SceneManager& m_sceneManager;
	QGLContext m_glContext;

	GLuint m_fragmentShader;
	GLuint m_program;
	GLuint m_vertexShader;

	GLuint m_unColoredVertexArrayObject;
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
	GLint m_colorComponentLocation;
	GLint m_isColoredLocation;
	GLint m_phongExponentLocation;
	GLint m_cameraPositionLocation;

	const static HappahGlFormat GL_FORMAT;
	//TODO: Change these matrices to Projection Matrix , viewMatrix as soon as QMatrices are removed
	hpmat4x4 m_modelMatrix;
	hpmat4x4 m_modelViewProjectionMatrix;
	hpmat3x3 m_normalMatrix;
	glm::vec3   m_cameraPosition;


};

#endif // DRAWMANAGER_H

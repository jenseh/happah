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
	bool initShaderPrograms();
	void sceneChanged();

private:

	void compileShader(GLuint shader, const char* filePath);
	SceneManager* m_sceneManager;
	GLuint m_fragmentShader;
	GLuint m_program;
	GLuint m_vertexShader;

	GLuint m_coloredVertexArrayObject;
	GLuint m_vertexDataBuffer;
	GLuint m_colorDataBuffer;

	//attribute locations
	GLint m_vertexLocation;
	GLint m_normalLocation;
	GLint m_colorLocation;

	//uniform locations
	GLint m_MMatrixLocation;     	//model matrix
	GLint m_MVPMatrixLocation;		//model view projection matrix
	GLint m_NMatrixLocation;		//normal matrix
	GLint m_kaLocation;				// MATERIAL ambient part
	GLint m_kdLocation;				// MATERIAL diffuse part
	GLint m_ksLocation;				// MATERIAL specular part
	GLint m_phongLocation;			// MATERIAL phong exponent
	GLint m_cameraPositionLocation; // camera position


};

#endif // DRAWMANAGER_H

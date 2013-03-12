#ifndef DRAW_MANAGER_H
#define DRAW_MANAGER_H

#include <GL/glew.h>
#include <QGLContext>
#include <QGLFormat>
#include <vector>

#include "happah/scene/DrawVisitor.h"
#include "happah/scene/ElementRenderStateNode.h"

class HappahGlFormat : public QGLFormat {
public:
	HappahGlFormat();
};

#include "happah/scene/SceneManager.h"

class DrawManager {
public:
	DrawManager(SceneManager_ptr sceneManager);
	~DrawManager();

	void draw(hpmat4x4& projectionMatrix, hpmat4x4& viewMatrix, hpvec3& cameraPosition);
	QGLContext* getGlContext();
	bool init();

private:
	class DefaultDrawVisitor : public DrawVisitor {
	public:
		DefaultDrawVisitor(DrawManager& drawManager);
		~DefaultDrawVisitor();
		
		void draw(ElementRenderStateNode& elementRenderStateNode, RigidAffineTransformation& rigidAffineTransformation);
		
	private:
		DrawManager& m_drawManager;

	};

	class DefaultSceneListener : public SceneListener {
	public:
		DefaultSceneListener(DrawManager& drawManager);
		~DefaultSceneListener();

		void handleSubtreeInsertedEvent(Node_ptr root);
		void handleSubtreesInsertedEvent(vector<Node_ptr>& roots);
		void handleSubtreeRemovedEvent(Node_ptr root);
		void handleSubtreesRemovedEvent(vector<Node_ptr>& roots);
		void handleSubtreeUpdatedEvent(Node_ptr root);
		void handleSubtreesUpdatedEvent(vector<Node_ptr>& roots);

	private:
		DrawManager& m_drawManager;
	};

	const static HappahGlFormat GL_FORMAT;

	DefaultDrawVisitor m_drawVisitor;
	DefaultSceneListener m_sceneListener;
	SceneManager_ptr m_sceneManager;
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

	hpmat4x4 m_modelMatrix;
	hpmat4x4 m_viewMatrix;
	hpmat4x4 m_projectionMatrix;
	hpmat3x3 m_normalMatrix;
	hpvec3   m_cameraPosition;

	void compileShader(GLuint shader, const char* filePath);
	void doDraw(ElementRenderStateNode& elementRenderStateNode, RigidAffineTransformation& rigidAffineTransformation);
	void initialize(ElementRenderStateNode& elementRenderStateNode);
	bool initShaderPrograms();

};

#endif // DRAW_MANAGER_H


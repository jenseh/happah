#ifndef DRAW_MANAGER_H
#define DRAW_MANAGER_H

#include <GL/glew.h>
#include <QGLContext>
#include <QGLFormat>
#include <vector>
#include <unordered_map>
#include <happah/HappahTypes.h>
#include "happah/scene/DrawVisitor.h"
#include "happah/scene/ElementRenderStateNode.h"
#include "happah/scene/PointCloudRenderStateNode.h"

using namespace std;
class HappahGlFormat : public QGLFormat {
public:
	HappahGlFormat();
};

#include "happah/scene/SceneManager.h"

//typedef unordered_map<hpcolor,ElementRenderStateNode&,hpcolorRedHash,hpcolorEqual> ElementsColorMap;
typedef unordered_map<int,ElementRenderStateNode_ptr>ElementsColorMap;
typedef unordered_map<int,PointCloudRenderStateNode_ptr>PointCloudColorMap;
typedef ElementsColorMap::value_type ValuePair;
typedef PointCloudColorMap::value_type PCValuePair;

class DrawManager {
public:
	DrawManager(SceneManager_ptr sceneManager);
	~DrawManager();

	void draw(hpmat4x4& projectionMatrix, hpmat4x4& viewMatrix, hpvec3& cameraPosition);
	QGLContext* getGlContext();
    bool init(QPaintDevice* paintDevice = NULL);
	void resizeSelectorTexture();
	bool select(int x,int y);
	bool isSomethingSelected(){return m_somethingSelected;}
    bool isGLInitialized() { return m_glInitialized; }

private:
	class DefaultDrawVisitor : public DrawVisitor {
	public:
		DefaultDrawVisitor(DrawManager& drawManager);
		~DefaultDrawVisitor();
		
		void draw(ElementRenderStateNode_ptr elementRenderStateNode, RigidAffineTransformation& rigidAffineTransformation);
		void draw(PointCloudRenderStateNode_ptr pointCloudRenderStateNode, RigidAffineTransformation& rigidAffineTransformation);
		

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

	class SelectionVisitor : public DrawVisitor{
	public:
		SelectionVisitor(DrawManager& drawManager);
		~SelectionVisitor();

		void draw(ElementRenderStateNode_ptr elementRenderStateNode, RigidAffineTransformation& rigidAffineTransformation);
		void draw(PointCloudRenderStateNode_ptr pointCloudRenderStateNode, RigidAffineTransformation& rigidAffinaTransformation);
		ElementRenderStateNode_ptr findElementRenderStateNodeOfColor(hpcolor color);
		PointCloudRenderStateNode_ptr findPointCloudRenderStateNodeOfColor(hpcolor color);
		int getCurrentSelectionIndex();
		void setCurrentSelectionIndex(int index);
		ElementRenderStateNode_ptr getCurrentSelectedElementRenderStateNode();
		void setCurrentSelectedElementRenderStateNode(ElementRenderStateNode_ptr elementRenderStateNode);
		PointCloudRenderStateNode_ptr getCurrentSelectedPointCloudRenderStateNode();
		void setCurrentSelectedPointCloudRenderStateNode(PointCloudRenderStateNode_ptr pointCloudRenderStateNode);
        void clearColorMaps();
		vector<hpcolor>* getPointSelectionColors();
		int findPointIndexFromColor(hpcolor color);
	private:
		vector<hpcolor>* m_pointSelectionColors;
		DrawManager& m_drawManager;
		ElementsColorMap m_colorMap;
		PointCloudColorMap m_pointCloudColorMap;
		int m_currentSelectionIndex;
		ElementRenderStateNode_ptr m_currentSelectedElementRenderStateNode;
		PointCloudRenderStateNode_ptr m_currentSelectedPointCloudRenderStateNode;

	};

	const static HappahGlFormat GL_FORMAT;

	DefaultDrawVisitor m_drawVisitor;
	DefaultSceneListener m_sceneListener;
	SceneManager_ptr m_sceneManager;
	SelectionVisitor m_selectionVisitor;
	QGLContext* m_glContext;
	QWidget* m_parentWidget;

	GLuint m_fragmentShader;
	GLuint m_program;
	GLuint m_pointCloudProgram;
	GLuint m_vertexShader;
	GLuint m_geometryShader;
	GLuint m_frameBuffer;
	GLuint m_depthRenderBuffer;
	GLuint m_selectorTexture;
	static GLenum m_drawBuffers[];
	bool m_somethingSelected;

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
	GLint m_isColorPerVertexLocation;
	GLint m_isSkipLightingContributionComputationLocation;
	GLint m_phongExponentLocation;
	GLint m_cameraPositionLocation;
	GLint m_drawSelectionColors;
	GLint m_selectedLocation;
	hpmat4x4 m_modelMatrix;
	hpmat4x4 m_viewMatrix;
	hpmat4x4 m_projectionMatrix;
	hpmat3x3 m_normalMatrix;
	hpvec3   m_cameraPosition;
	bool m_isSkipLightingContributionComputation;


	GLint m_pointCloudVertexLocation;
	GLint m_pointCloudColorLocation;
	GLint m_pointCloudSinglePointSelectionColorLocation;
	GLint m_pointCloudModelViewMatrixLocation;
	GLint m_pointCloudProjectionMatrixLocation;
	GLint m_pointCloudPointRadiusLocation;
	GLint m_pointCloudDrawSelectionColors;
	GLint m_pointCloudSelectionColorLocation;
	GLint m_pointCloudSelectedLocation;
	GLint m_pointCloudColorComponent;

    bool m_glInitialized;

	void compileShader(GLuint shader, const char* filePath);
	void doDraw(ElementRenderStateNode_ptr elementRenderStateNode, RigidAffineTransformation& rigidAffineTransformation,bool doSelection);
	void doDraw(PointCloudRenderStateNode_ptr pointCloudRenderStateNode, RigidAffineTransformation& rigidAffineTransformation,bool doSelection);
	bool enableFrameBuffer();
	void initialize(ElementRenderStateNode_ptr elementRenderStateNode);
	void initialize(PointCloudRenderStateNode_ptr elementRenderStateNode);
	bool initShaderPrograms();

};

#endif // DRAW_MANAGER_H


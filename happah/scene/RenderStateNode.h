#ifndef RENDER_STATE_NODE_H_
#define RENDER_STATE_NODE_H_


#include <GL/glew.h>
#include <memory>
#include <vector>
#include "happah/scene/Node.h"
#include "happah/scene/Material.h"

class RenderStateNode;
typedef shared_ptr<RenderStateNode> RenderStateNode_ptr;

using namespace std;

class RenderStateNode : public Node {
public:
	RenderStateNode(hpuint mode, vector<hpvec3>* vertexData, std::vector<hpuint>* indices, hpcolor& color);
	RenderStateNode(hpuint mode, vector<hpvec3>* vertexData, std::vector<hpuint>* indices, vector<hpcolor>* colorVector);
	virtual ~RenderStateNode();

	virtual void accept(SceneVisitor& sceneVisitor);
	virtual void draw(DrawVisitor& drawVisitor, RigidAffineTransformation& rigidAffineTransformation);

	void 	setIndexBufferID(GLuint id);
	void 	setVertexArrayObjectID(GLuint id);
	void 	setVertexBufferID(GLuint id);
	void 	setColorBufferID(GLuint id); //TODO: REMOVE AS SOON AS USING NEW TRIANGLE MESH !!!
	void 	setColor(hpcolor color);
	void 	setMaterial(Material& material);
	void 	setInitialized(bool isInitialized);

	virtual void setColorVector(std::vector<hpcolor>* colorVector);

	GLuint 					getIndexBufferID();
	GLuint 					getVertexArrayObjectID();
	GLuint 					getVertexBufferID();
	GLuint					getColorBufferID(void);
	GLuint 					getMode();
	hpcolor 				getColor();
	std::vector<hpcolor>* 	getColorVector();

	Material 				getMaterial();

	bool isInitialized();
	bool hasColorVector();

	vector<hpvec3>* getVertexData();
	vector<hpvec4>* getColorData();
	vector<hpuint>* getIndices();




private:
	GLuint 					m_indexBufferID;
	GLuint 					m_vertexArrayObjectID;
	GLuint					m_vertexBufferID;
	GLuint 					m_colorBufferID;
	GLuint 					m_mode;
	hpcolor 				m_color;
	vector<hpvec3>*			m_vertexData;
	vector<hpuint>*			m_indices;
	vector<hpcolor>* 		m_colorVector;
	Material 				m_material;
	bool 					m_initialized;
	bool 					m_hasColorVector;

};

class TriangleMeshRenderStateNode;
typedef shared_ptr<TriangleMeshRenderStateNode> TriangleMeshRenderStateNode_ptr;

#include "happah/scene/Material.h"
#include "happah/scene/RenderStateNode.h"
#include "happah/scene/TriangleMeshNode.h"

class TriangleMeshRenderStateNode : public RenderStateNode {

public:
	TriangleMeshRenderStateNode(TriangleMesh_ptr triangleMesh,hpcolor& color);
	TriangleMeshRenderStateNode(TriangleMesh_ptr triangleMesh,std::vector<hpcolor>* colorVector);
	virtual ~TriangleMeshRenderStateNode();

};



class LineMeshRenderStateNode;
typedef shared_ptr<LineMeshRenderStateNode> LineMeshRenderStateNode_ptr;

#include "happah/scene/Material.h"
#include "happah/scene/RenderStateNode.h"
#include "happah/scene/LineMeshNode.h"

class LineMeshRenderStateNode : public RenderStateNode {

public:
	LineMeshRenderStateNode(LineMesh_ptr lineMesh,hpcolor& color);
	LineMeshRenderStateNode(LineMesh_ptr lineMesh,std::vector<hpcolor>* colorVector);
	virtual ~LineMeshRenderStateNode();

};

class PointCloudRenderStateNode;
typedef shared_ptr<PointCloudRenderStateNode> PointCloudRenderStateNode_ptr;

#include "happah/scene/Material.h"
#include "happah/scene/RenderStateNode.h"
#include "happah/scene/PointCloudNode.h"

class PointCloudRenderStateNode : public RenderStateNode {

public:
	PointCloudRenderStateNode(PointCloud_ptr pointCloud,hpcolor& color);
	PointCloudRenderStateNode(PointCloud_ptr pointCloud,std::vector<hpcolor>* colorVector);
	virtual ~PointCloudRenderStateNode();

};

#endif /* RENDER_STATE_NODE_H_ */

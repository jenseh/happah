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
	RenderStateNode(vector<hpvec3>* vertexData, hpcolor& color);
	RenderStateNode(vector<hpvec3>* vertexData, vector<hpcolor>* colorVector);
	virtual ~RenderStateNode();

	virtual void accept(SceneVisitor& sceneVisitor);


	void 	setVertexArrayObjectID(GLuint id);
	void 	setVertexBufferID(GLuint id);
	void 	setColorBufferID(GLuint id);
	void 	setColor(hpcolor color);
	void 	setMaterial(Material& material);
	void 	setInitialized(bool isInitialized);

	virtual void setColorVector(std::vector<hpcolor>* colorVector);


	GLuint 					getVertexArrayObjectID();
	GLuint 					getVertexBufferID();
	GLuint					getColorBufferID(void);
	hpcolor 				getColor();
	std::vector<hpcolor>* 	getColorVector();

	Material 				getMaterial();

	bool isInitialized();
	bool hasColorVector();

	vector<hpvec3>* getVertexData();
	vector<hpvec4>* getColorData();





private:

	GLuint 					m_vertexArrayObjectID;
	GLuint					m_vertexBufferID;
	GLuint 					m_colorBufferID;
	hpcolor 				m_color;
	vector<hpvec3>*			m_vertexData;
	vector<hpcolor>* 		m_colorVector;
	Material 				m_material;
	bool 					m_initialized;
	bool 					m_hasColorVector;

};

/*
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
*/
#endif /* RENDER_STATE_NODE_H_ */

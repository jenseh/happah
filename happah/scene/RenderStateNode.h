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

#endif /* RENDER_STATE_NODE_H_ */

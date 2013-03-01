#ifndef TRIANGLE_MESH_RENDER_STATE_NODE_H_
#define TRIANGLE_MESH_RENDER_STATE_NODE_H_

#include <GL/glew.h>
#include <memory>

using namespace std;

class TriangleMeshRenderStateNode;
typedef shared_ptr<TriangleMeshRenderStateNode> TriangleMeshRenderStateNode_ptr;

#include "happah/scene/Node.h"
#include "happah/scene/TriangleMeshNode.h"

class TriangleMeshRenderStateNode : public Node {

public:
	TriangleMeshRenderStateNode(TriangleMesh_ptr triangleMesh,hpcolor &color);
	TriangleMeshRenderStateNode(TriangleMesh_ptr triangleMesh,std::vector<hpcolor>* colorVector);
	virtual ~TriangleMeshRenderStateNode();

	virtual void accept(SceneVisitor& sceneVisitor);
	virtual void draw(DrawVisitor& drawVisitor, RigidAffineTransformation& rigidAffineTransformation);

	void 	setIndexBufferID(GLuint id);
	void 	setVertexArrayObjectID(GLuint id);
	void 	setVertexBufferID(GLuint id);
	void 	setColorBufferID(GLuint id); //TODO: REMOVE AS SOON AS USING NEW TRIANGLE MESH !!!
	void 	setColor(hpcolor color);
	void 	setColorVector(std::vector<hpcolor>* colorVector);
	void 	setMaterial(Material& material);
	void 	setInitialized(bool isInitialized);

	GLuint 					getIndexBufferID();
	GLuint 					getVertexArrayObjectID();
	GLuint 					getVertexBufferID();
	GLuint					getColorBufferID(void); //TODO: REMOVE AS SOON AS USING NEW TRIANGLE MESH !!!
	hpcolor 				getColor();
	std::vector<hpcolor>* 	getColorVector();
	TriangleMesh_ptr 		getTriangleMesh();
	Material 				getMaterial();

	bool isInitialized();
	bool hasColorVector();


private:
	GLuint 					m_indexBufferID;
	GLuint 					m_vertexArrayObjectID;
	GLuint					m_vertexBufferID;
	GLuint 					m_colorBufferID; // TODO: REMOVE AS SOON AS USING NEW TRIANGLE MESH !!!
	hpcolor 				m_color;
	std::vector<hpcolor>* 	m_colorVector;
	TriangleMesh_ptr 		m_triangleMesh;
	Material 				m_material;
	bool 					m_initialized;
	bool 					m_hasColorVector;
};


#endif /* TRIANGLE_MESH_RENDER_STATE_NODE_H_ */


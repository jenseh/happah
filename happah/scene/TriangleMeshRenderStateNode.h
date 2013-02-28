#ifndef TRIANGLE_MESH_RENDER_STATE_NODE_H_
#define TRIANGLE_MESH_RENDER_STATE_NODE_H_

#include <memory>
#include <GL/glew.h>


using namespace std;

class TriangleMeshRenderStateNode;
typedef shared_ptr<TriangleMeshRenderStateNode> TriangleMeshRenderStateNode_ptr;

#include "happah/HappahTypes.h"
#include "happah/scene/Node.h"
#include "happah/scene/SceneVisitor.h"

class TriangleMeshRenderStateNode : public Node {

public:
	TriangleMeshRenderStateNode(TriangleMesh_ptr triangleMesh,hpcolor &color);
	TriangleMeshRenderStateNode(TriangleMesh_ptr triangleMesh,std::vector<hpcolor>* colorVector);
	virtual ~TriangleMeshRenderStateNode();

	virtual void accept(SceneVisitor& sceneVisitor);

	hpcolor getColor();
	std::vector<hpcolor>* getColorVector();
	GLuint getIndexBufferID();
	GLuint getVertexArrayObjectID();
	GLuint getVertexBufferID();
	TriangleMesh_ptr getTriangleMesh();
	void setColor(hpcolor color);
	void setColorVector(std::vector<hpcolor>* colorVector);
	void setIndexBufferID(GLuint id);
	void setVertexArrayObjectID(GLuint id);
	void setVertexBufferID(GLuint id);
	GLuint getColorBufferID(void); //TODO: REMOVE AS SOON AS USING NEW TRIANGLE MESH !!!
	void   setColorBufferID(GLuint id); //TODO: REMOVE AS SOON AS USING NEW TRIANGLE MESH !!!
private:
	hpcolor m_color;
	std::vector<hpcolor>* m_colorVector;
	GLuint m_indexBufferID;
	TriangleMesh_ptr m_triangleMesh;
	GLuint m_vertexArrayObjectID;
	GLuint m_vertexBufferID;
	GLuint m_colorBufferID; // TODO: REMOVE AS SOON AS USING NEW TRIANGLE MESH !!!
};

#endif /* TRIANGLE_MESH_RENDER_STATE_NODE_H_ */

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
	TriangleMeshRenderStateNode();
	virtual ~TriangleMeshRenderStateNode();

	virtual void accept(SceneVisitor& sceneVisitor);

	hpcolor getColor();
	GLuint getIndexBufferID();
	GLuint getVertexArrayObjectID();
	GLuint getVertexBufferID();
	void setColor(hpcolor color);
	void setIndexBufferID(GLuint id);
	void setVertexArrayObjectID(GLuint id);
	void setVertexBufferID(GLuint id);

private:
	hpcolor m_color;
	GLuint m_indexBufferID;
	GLuint m_vertexArrayObjectID;
	GLuint m_vertexBufferID;
	TriangleMesh_ptr triangleMesh_ptr;
};

#endif /* TRIANGLE_MESH_RENDER_STATE_NODE_H_ */

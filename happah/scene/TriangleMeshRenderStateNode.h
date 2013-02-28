/*
 * TriangleMeshRenderStateNode.h
 *
 *  Created on: 28.02.2013
 *      Author: msauer
 */

#ifndef TRIANGLE_MESH_RENDER_STATE_NODE_H_
#define TRIANGLE_MESH_RENDER_STATE_NODE_H_

#include <memory>
#include <GL/glew.h>

using namespace std;

class TriangleMeshRenderStateNode;
typedef shared_ptr<TriangleMeshRenderStateNode> TriangleRenderStateMeshNode_ptr;

#include "happah/scene/SceneVisitor.h"
#include "happah/scene/Node.h"
#include "happah/HappahTypes.h"


class TriangleMeshRenderStateNode : public Node {

public:
	TriangleMeshRenderStateNode();
	virtual ~TriangleMeshRenderStateNode();

	virtual void accept(SceneVisitor& sceneVisitor);

	void setVertexBufferID(GLuint id);
	GLuint getVertexBufferID();
	void setIndexBufferID(GLuint id);
	GLuint getIndexBufferID();
	void setVertexArrayObjectID(GLuint id);
	GLuint getVertexArrayObjectID();
	void setColor(hpcolor color);
	hpcolor getColor();

private:
	GLuint m_vertexBufferID;
	GLuint m_indexBufferID;
	GLuint m_vertexArrayObjectID;
	hpcolor m_color;
};

#endif /* TRIANGLE_MESH_RENDER_STATE_NODE_H_ */

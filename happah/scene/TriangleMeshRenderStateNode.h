#ifndef TRIANGLE_MESH_RENDER_STATE_NODE_H_
#define TRIANGLE_MESH_RENDER_STATE_NODE_H_

#include <GL/glew.h>
#include <memory>

using namespace std;

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


#endif /* TRIANGLE_MESH_RENDER_STATE_NODE_H_ */


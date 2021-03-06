#ifndef ELEMENT_RENDER_STATE_NODE_H_
#define ELEMENT_RENDER_STATE_NODE_H_

#include <GL/glew.h>
#include <memory>
#include <vector>
#include "happah/scene/Node.h"
#include "happah/scene/Material.h"
#include "happah/scene/RenderStateNode.h"
#include "happah/scene/DrawVisitor.h"

using namespace std;

class ElementRenderStateNode : public RenderStateNode{
public:
	ElementRenderStateNode(hpuint mode, vector<hpvec3>* verticesAndNormals, std::vector<hpuint>* indices, hpcolor& color);
	ElementRenderStateNode(hpuint mode, vector<hpvec3>* verticesAndNormals, std::vector<hpuint>* indices, vector<hpcolor>* colorVector);
	virtual ~ElementRenderStateNode();

	virtual void draw(DrawVisitor& drawVisitor, RigidAffineTransformation& rigidAffineTransformation);


	void					setIndexBufferID(GLuint id);
	void 					setSelected(int selected);
	int						getSelected();
	GLuint 					getIndexBufferID();
	GLuint 					getMode();
	vector<hpuint>* 		getIndices();
	ElementRenderStateNode_ptr getPtr(){return dynamic_pointer_cast<ElementRenderStateNode>(shared_from_this());}
private:
	vector<hpuint>*			m_indices;
	GLuint 					m_indexBufferID;
	GLuint 					m_mode;
	int						m_selected;
};

class TriangleMeshRenderStateNode;
typedef shared_ptr<TriangleMeshRenderStateNode> TriangleMeshRenderStateNode_ptr;


#include "happah/scene/TriangleMeshNode.h"

class TriangleMeshRenderStateNode : public ElementRenderStateNode {

public:
	TriangleMeshRenderStateNode(TriangleMesh3D_ptr triangleMesh,hpcolor& color);
	TriangleMeshRenderStateNode(TriangleMesh3D_ptr triangleMesh,std::vector<hpcolor>* colorVector);
	virtual ~TriangleMeshRenderStateNode();

};

class LineMeshRenderStateNode;
typedef shared_ptr<LineMeshRenderStateNode> LineMeshRenderStateNode_ptr;


#include "happah/scene/LineMeshNode.h"

class LineMeshRenderStateNode : public ElementRenderStateNode {

public:
	LineMeshRenderStateNode(LineMesh3D_ptr lineMesh,hpcolor& color);
	LineMeshRenderStateNode(LineMesh3D_ptr lineMesh, std::vector<hpcolor>* colorVector);
	virtual ~LineMeshRenderStateNode();

};


#endif /* ELEMENTRENDERSTATENODE_H_ */

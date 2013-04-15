#ifndef RENDER_STATE_NODE_H_
#define RENDER_STATE_NODE_H_

#include <iostream>
#include <GL/glew.h>
#include <memory>
#include <vector>
#include <list>
#include "happah/scene/Node.h"
#include "happah/scene/Material.h"
#include "happah/scene/SelectListener.h"

class RenderStateNode;
typedef shared_ptr<RenderStateNode> RenderStateNode_ptr;

using namespace std;

class RenderStateNode : public Node {
public:
	RenderStateNode(vector<hpvec3>* verticesAndNormals, hpcolor& color);
	RenderStateNode(vector<hpvec3>* verticesAndNormals, vector<hpcolor>* colorVector);
	virtual ~RenderStateNode();

	virtual void accept(SceneVisitor& sceneVisitor);


	void 	setVertexArrayObjectID(GLuint id);
	void 	setVertexBufferID(GLuint id);
	void 	setColorBufferID(GLuint id);
	void 	setColor(hpcolor color);
	void 	setColorVector(std::vector<hpcolor>* colorVector);
	void 	setMaterial(Material& material);
	void 	setInitialized(bool isInitialized);
	void 	triggerSelectEvent();
    void    triggerSelectEvent(int pointIndex);
	void	triggerDeselectEvent();
	void 	registerSelectListener(SelectListener* selectListener);
	void	removeSelectListener(SelectListener* selectListener);

	GLuint 					getVertexArrayObjectID();
	GLuint 					getVertexBufferID();
	GLuint					getColorBufferID(void);
	hpcolor 				getColor();
	std::vector<hpcolor>* 	getColorVector();

	Material 				getMaterial();

	bool isInitialized();
	bool hasColorVector();

	vector<hpvec3>* getVerticesAndNormals();
	vector<hpvec4>* getColorData();





private:

	GLuint 					m_vertexArrayObjectID;
	GLuint					m_vertexBufferID;
	GLuint 					m_colorBufferID;
	hpcolor 				m_color;
	vector<hpvec3>*			m_verticesAndNormals;
	vector<hpcolor>* 		m_colorVector;
	Material 				m_material;
	bool 					m_initialized;
	bool 					m_hasColorVector;
	list<SelectListener*>	m_selectListeners;
};


#endif /*RENDER_STATE_NODE_H_ */

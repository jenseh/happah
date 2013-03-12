#ifndef WORMNODE_H_
#define WORMNODE_H_

#include "happah/geometries/Worm.h"
#include "happah/scene/GUIStateNode.h"
#include "happah/scene/SimpleGeometryNode.h"
#include "happah/scene/TriangleMeshNode.h"

class WormNode : public SimpleGeometryNode<Worm> {

public:
	WormNode(Worm_ptr worm);
	virtual ~WormNode();

	virtual void accept(SceneVisitor& sceneVisitor);
	void insertChild(WormGUIStateNode_ptr wormGUIStateNode);
	void insertChild(TriangleMeshNode_ptr triangleMeshNode);

};
typedef shared_ptr<WormNode> WormNode_ptr;

#endif /* WORMNODE_H_ */

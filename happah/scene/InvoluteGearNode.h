#ifndef INVOLUTE_GEAR_NODE_H
#define INVOLUTE_GEAR_NODE_H

#include "happah/geometries/InvoluteGear.h"
#include "happah/scene/GUIStateNode.h"
#include "happah/scene/SimpleGeometryNode.h"
#include "happah/scene/TriangleMeshNode.h"

class InvoluteGearNode : public SimpleGeometryNode<InvoluteGear> {

public:
	InvoluteGearNode(InvoluteGear_ptr involuteGear);
	virtual ~InvoluteGearNode();

	virtual void accept(SceneVisitor& sceneVisitor);
	void addChild(InvoluteGearGUIStateNode_ptr involuteGearGUIStateNode);
	void addChild(TriangleMeshNode_ptr triangleMeshNode);
	bool hasChild(InvoluteGearGUIStateNode_ptr involuteGearGUIStateNode);
	void removeChild(InvoluteGearGUIStateNode_ptr involuteGearGUIStateNode);
	void removeChildContaining(TriangleMesh_ptr triangleMesh);
	void removeChild(TriangleMeshNode_ptr triangleMeshNode);

};
typedef shared_ptr<InvoluteGearNode> InvoluteGearNode_ptr;


#endif // INVOLUTE_GEAR_NODE_H

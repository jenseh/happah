#ifndef SIMPLE_GEAR_NODE_H
#define SIMPLE_GEAR_NODE_H

#include "happah/geometries/SimpleGear.h"
#include "happah/scene/GUIStateNode.h"
#include "happah/scene/SimpleGeometryNode.h"
#include "happah/scene/TriangleMeshNode.h"

class SimpleGearNode : public SimpleGeometryNode<SimpleGear> {

public:
	SimpleGearNode(SimpleGear_ptr simpleGear);
	virtual ~SimpleGearNode();

	virtual void accept(SceneVisitor& sceneVisitor);
	void insertChild(SimpleGearGUIStateNode_ptr simpleGearGUIStateNode);
	void insertChild(TriangleMeshNode_ptr triangleMeshNode);

};
typedef shared_ptr<SimpleGearNode> SimpleGearNode_ptr;


#endif

#ifndef INVOLUTE_SPUR_GEAR_NODE_H
#define INVOLUTE_SPUR_GEAR_NODE_H

#include <memory>

using namespace std;

class InvoluteSpurGearNode;
typedef shared_ptr<InvoluteSpurGearNode> InvoluteSpurGearNode_ptr;

#include "happah/geometries/InvoluteSpurGear.h"
#include "happah/scene/SceneVisitor.h"
#include "happah/scene/SimpleGeometryNode.h"
#include "happah/scene/TriangleMeshNode.h"

class InvoluteSpurGearNode : public SimpleGeometryNode<InvoluteSpurGear> {

public:
	InvoluteSpurGearNode(InvoluteSpurGear_ptr involuteSpurGear);
	virtual ~InvoluteSpurGearNode();

	virtual void accept(SceneVisitor& sceneVisitor);
	void addChild(TriangleMeshNode_ptr triangleMeshNode);
};

#endif // INVOLUTE_SPUR_GEAR_NODE_H

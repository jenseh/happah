#ifndef INVOLUTE_GEAR_NODE_H
#define INVOLUTE_GEAR_NODE_H

#include <memory>

using namespace std;

class InvoluteGearNode;
typedef shared_ptr<InvoluteGearNode> InvoluteGearNode_ptr;

#include "happah/geometries/InvoluteSpurGear.h"
#include "happah/scene/SceneVisitor.h"
#include "happah/scene/SimpleGeometryNode.h"
#include "happah/scene/TriangleMeshNode.h"

class InvoluteGearNode : public SimpleGeometryNode<InvoluteSpurGear> {

public:
	InvoluteGearNode(InvoluteGear_ptr involuteGear);
	virtual ~InvoluteGearNode();

	virtual void accept(SceneVisitor& sceneVisitor);
	void addChild(TriangleMeshNode_ptr triangleMeshNode);
	void removeChild(TriangleMeshNode_ptr triangleMeshNode);
};

#endif // INVOLUTE_GEAR_NODE_H

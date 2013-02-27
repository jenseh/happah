#ifndef INVOLUTE_SPUR_GEAR_NODE_H
#define INVOLUTE_SPUR_GEAR_NODE_H

#include <memory>

#include "happah/geometries/InvoluteSpurGear.h"
#include "happah/scene/SceneVisitor.h"
#include "happah/scene/SimpleGeometryNode.h"

using namespace std;

class InvoluteSpurGearNode : public SimpleGeometryNode<InvoluteSpurGear> {

public:
	InvoluteSpurGearNode(InvoluteSpurGear_ptr involuteSpurGear);
	virtual ~InvoluteSpurGearNode();

	virtual void accept(SceneVisitor& sceneVisitor);
};
typedef shared_ptr<InvoluteSpurGearNode> InvoluteSpurGearNode_ptr;

#endif // INVOLUTE_SPUR_GEAR_NODE_H

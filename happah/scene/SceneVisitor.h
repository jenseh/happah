#ifndef SCENE_VISITOR_H
#define SCENE_VISITOR_H

#include "happah/scene/InvoluteSpurGearNode.h"

class InvoluteSpurGearNode;
class SceneVisitor {

public:
	virtual void visit(InvoluteSpurGearNode& involuteSpurGearNode) = 0;

};

#endif // SCENE_VISITOR_H

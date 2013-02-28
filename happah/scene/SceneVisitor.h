#ifndef SCENE_VISITOR_H
#define SCENE_VISITOR_H

#include "happah/scene/InvoluteSpurGearNode.h"
#include "happah/scene/TriangleMeshNode.h"
#include "happah/scene/TriangleMeshRenderStateNode.h"

class InvoluteSpurGearNode;
class TriangleMeshNode;
class TriangleMeshRenderStateNode;

class SceneVisitor {

public:
	virtual void visit(InvoluteSpurGearNode& involuteSpurGearNode) = 0;
	virtual void visit(TriangleMeshNode& triangleMeshNode) = 0;
	virtual void visit(TriangleMeshRenderStateNode& triangleMeshRenderStateNode) = 0;
};

#endif // SCENE_VISITOR_H

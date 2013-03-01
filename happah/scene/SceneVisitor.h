#ifndef SCENE_VISITOR_H
#define SCENE_VISITOR_H

class InvoluteGearNode;
class TriangleMeshNode;
class TriangleMeshRenderStateNode;

class SceneVisitor {

public:
	virtual void visit(InvoluteGearNode& involuteGearNode) = 0;
	virtual void visit(TriangleMeshNode& triangleMeshNode) = 0;
	virtual void visit(TriangleMeshRenderStateNode& triangleMeshRenderStateNode) = 0;
};

#endif // SCENE_VISITOR_H

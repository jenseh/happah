#ifndef SCENE_VISITOR_H
#define SCENE_VISITOR_H

class InvoluteGearNode;
class TriangleMeshNode;
class LineMeshNode;
class RenderStateNode;

class SceneVisitor {

public:
	virtual void visit(InvoluteGearNode& involuteGearNode) = 0;
	virtual void visit(TriangleMeshNode& triangleMeshNode) = 0;
	virtual void visit(LineMeshNode& lineMeshNode)=0;
	virtual void visit(RenderStateNode& renderStateNode) = 0;

};

#endif // SCENE_VISITOR_H

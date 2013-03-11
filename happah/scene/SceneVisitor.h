#ifndef SCENE_VISITOR_H
#define SCENE_VISITOR_H

class InvoluteGearNode;
class PlaneNode;
class TriangleMeshNode;
class LineMeshNode;
class PointCloudNode;
class RenderStateNode;
class SimpleGearNode;
class DiscNode;

class SceneVisitor {

public:
	virtual void visit(InvoluteGearNode& involuteGearNode) = 0;
	virtual void visit(PlaneNode& planeNode) = 0;
	virtual void visit(TriangleMeshNode& triangleMeshNode) = 0;
	virtual void visit(LineMeshNode& lineMeshNode) = 0;
	virtual void visit(PointCloudNode& pointCloudNode) = 0;
	virtual void visit(RenderStateNode& renderStateNode) = 0;
	virtual void visit(SimpleGearNode& simpleGearNode) = 0;
	virtual void visit(DiscNode& discNode) = 0;
};

#endif // SCENE_VISITOR_H

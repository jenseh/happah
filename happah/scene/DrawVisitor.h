#ifndef DRAW_VISITOR_H
#define DRAW_VISITOR_H

class RigidAffineTransformation;
class TriangleMeshRenderStateNode;

class DrawVisitor {

public:
	virtual void draw(TriangleMeshRenderStateNode& triangleMeshRenderStateNode, RigidAffineTransformation& rigidAffineTransformation) = 0;

};

#endif //DRAW_VISITOR_H

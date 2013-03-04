#ifndef DRAW_VISITOR_H
#define DRAW_VISITOR_H

class RigidAffineTransformation;
class RenderStateNode;

class DrawVisitor {

public:
	virtual void draw(RenderStateNode& renderStateNode, RigidAffineTransformation& rigidAffineTransformation) = 0;

};

#endif //DRAW_VISITOR_H

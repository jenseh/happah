#ifndef DRAW_VISITOR_H
#define DRAW_VISITOR_H

class RigidAffineTransformation;
class ElementRenderStateNode;

class DrawVisitor {

public:
	virtual void draw(ElementRenderStateNode& elementRenderStateNode, RigidAffineTransformation& rigidAffineTransformation) = 0;

};

#endif //DRAW_VISITOR_H

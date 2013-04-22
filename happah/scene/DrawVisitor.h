#ifndef DRAW_VISITOR_H
#define DRAW_VISITOR_H
#include <happah/HappahTypes.h>
class RigidAffineTransformation;
class ElementRenderStateNode;
class PointCloudRenderStateNode;

class DrawVisitor {

public:
	virtual ~DrawVisitor() {};

	virtual void draw(ElementRenderStateNode_ptr elementRenderStateNode, RigidAffineTransformation& rigidAffineTransformation) = 0;
	virtual void draw(PointCloudRenderStateNode_ptr pointCloudRenderStateNode, RigidAffineTransformation& rigidAffineTransformation)= 0;

};
#endif //DRAW_VISITOR_H

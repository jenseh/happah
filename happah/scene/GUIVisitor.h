#ifndef GUI_VISITOR_H
#define GUI_VISITOR_H

class GUIVisitor;

#include "happah/scene/GUIStateNode.h"

class GUIVisitor {

public:
	virtual void visit(InvoluteGearGUIStateNode_ptr involuteGearGUIStateNode) = 0;
	virtual void visit(PlaneGUIStateNode_ptr planeGUIStateNode) = 0;

};

#endif //GUI_VISITOR_H

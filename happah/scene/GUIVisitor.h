#ifndef GUI_VISITOR_H
#define GUI_VISITOR_H

class GUIVisitor;

#include "happah/scene/GUIStateNode.h"

class GUIVisitor {

public:
	virtual void visit(GUIStateNode_ptr guiStateNode) = 0;

};

#endif //GUI_VISITOR_H

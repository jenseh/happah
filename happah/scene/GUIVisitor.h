#ifndef GUI_VISITOR_H
#define GUI_VISITOR_H

class GUIStateNode;
typedef std::shared_ptr<GUIStateNode> GUIStateNode_ptr;

class GUIVisitor {

public:
	virtual void visit(GUIStateNode_ptr guiStateNode) = 0;

};

#endif //GUI_VISITOR_H

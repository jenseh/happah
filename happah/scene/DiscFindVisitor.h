#ifndef DISCFINDVISITOR_H_
#define DISCFINDVISITOR_H_
#include "happah/scene/SceneVisitor.h"
#include "happah/scene/DiscNode.h"

class DiscFindVisitor: public SceneVisitor {

	bool foundDisc;
	Disc_ptr result;
	DiscFindVisitor():SceneVisitor(){
		foundDisc = false;
	}
	void visit(DiscNode& discNode) {
		foundDisc = true;
		result = discNode->getGeometry();
	}
};
#endif /* DISCFINDVISITOR_H_ */

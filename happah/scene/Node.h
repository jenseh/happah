#ifndef NODE_H
#define NODE_H

#include <memory>
#include <set>

using namespace std;

#include "happah/scene/DrawVisitor.h"
#include "happah/scene/SceneVisitor.h"
#include "happah/transformations/RigidAffineTransformation.h"

class Node;
typedef shared_ptr<Node> Node_ptr;

class GUIVisitor;
class Node {

public:
	Node();
	virtual ~Node();

	virtual void accept(GUIVisitor& guiVisitor);
	virtual void accept(SceneVisitor& sceneVisitor);
	virtual bool contains(shared_ptr<void> data) const;
	virtual void draw(DrawVisitor& drawVisitor, RigidAffineTransformation& rigidAffineTransformation);
	Node_ptr findContaining(shared_ptr<void> data) const;
	Node_ptr findChildContaining(shared_ptr<void> data) const;
	bool hasChild(Node_ptr child) const;

protected:
	set<Node_ptr> m_children;

	void addChild(Node_ptr child);
	void removeChildContaining(shared_ptr<void> data);
	void removeChild(Node_ptr child);

};

#include "happah/scene/GUIVisitor.h"

#endif // NODE_H

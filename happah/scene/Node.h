#ifndef NODE_H
#define NODE_H

#include <memory>
#include <set>
#include <vector>

using namespace std;

#include "happah/scene/DrawVisitor.h"
#include "happah/scene/SceneVisitor.h"
#include "happah/transformations/RigidAffineTransformation.h"

class Node;
typedef shared_ptr<Node> Node_ptr;

class GUIVisitor;
class Node : public enable_shared_from_this<Node> {

public:
	Node();
	virtual ~Node();

	virtual void accept(GUIVisitor& guiVisitor);
	virtual void accept(SceneVisitor& sceneVisitor);
	virtual bool contains(shared_ptr<void> data) const;
	virtual void draw(DrawVisitor& drawVisitor, RigidAffineTransformation& rigidAffineTransformation);
	Node_ptr findChildContaining(shared_ptr<void> data) const;
	Node_ptr findContaining(shared_ptr<void> data) const;
	Node_ptr getParent();
	Node_ptr getptr();
	bool hasChild(Node_ptr child) const;
	virtual bool remove(Node_ptr node);
	virtual bool remove(vector<Node_ptr>& nodes);
	virtual bool removeChildContaining(shared_ptr<void> data);
	virtual bool removeContaining(shared_ptr<void> parentData, shared_ptr<void> childData);

protected:
	set<Node_ptr> m_children;
	weak_ptr<Node> m_parent;

	void insertChild(Node_ptr child);
	bool removeChild(Node_ptr child);
	void setParent(Node_ptr parent);

private:
	bool doRemove(Node_ptr node);

};

#include "happah/scene/GUIVisitor.h"

#endif // NODE_H

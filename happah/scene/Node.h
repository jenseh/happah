#ifndef NODE_H
#define NODE_H

#include <memory>
#include <set>

using namespace std;

class Node;
typedef shared_ptr<Node> Node_ptr;

class SceneVisitor;
class Node {

public:
	Node();
	virtual ~Node();

	virtual void accept(SceneVisitor& sceneVisitor);

protected:
	set<Node_ptr> m_children;
	Node_ptr m_parent;

	void addChild(Node_ptr child);
	virtual bool contains(shared_ptr<void> data);
	virtual Node_ptr find(shared_ptr<void> data);
	void removeChild(Node_ptr child);

private:
	const static Node_ptr NULL_NODE;
	void setParent(Node_ptr parent);

};

#include "happah/scene/SceneVisitor.h"

#endif // NODE_H

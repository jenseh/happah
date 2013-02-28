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
	virtual bool const contains(shared_ptr<void> data);
	Node_ptr const find(shared_ptr<void> data);

protected:
	void addChild(Node_ptr child);
	void removeChild(Node_ptr child);

private:
	const static Node_ptr NULL_NODE;
	set<Node_ptr> m_children;

};

#include "happah/scene/SceneVisitor.h"

#endif // NODE_H

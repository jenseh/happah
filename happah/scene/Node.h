#ifndef NODE_H
#define NODE_H

#include <memory>
#include <set>

using namespace std;

class DrawManager;

//#include "happah/gui/gl/DrawManager.h"
#include "happah/scene/SceneVisitor.h"
#include "happah/transformations/RigidAffineTransformation.h"

class Node;
typedef shared_ptr<Node> Node_ptr;

class Node {

public:
	Node();
	virtual ~Node();

	virtual void accept(SceneVisitor& sceneVisitor);
	virtual bool const contains(shared_ptr<void> data);
	virtual void draw(DrawManager& drawManager, RigidAffineTransformation& rigidAffineTransformation);
	Node_ptr const find(shared_ptr<void> data);

protected:
	set<Node_ptr> m_children;

	void addChild(Node_ptr child);
	void removeChild(Node_ptr child);

private:
	const static Node_ptr NULL_NODE;

};


#endif // NODE_H

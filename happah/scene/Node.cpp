#include "happah/scene/Node.h"

Node::Node() {}

Node::~Node() {}

void Node::accept(SceneVisitor& sceneVisitor) {
	for(set<Node_ptr>::iterator i = m_children.begin(), end = m_children.end(); i != end; ++i)
		(*i)->accept(sceneVisitor);
}

void Node::addChild(Node_ptr child) {
	m_children.insert(child);
	child->setParent(shared_ptr<Node>(this));
}

void Node::removeChild(Node_ptr child) {
	m_children.erase(child);
	child->setParent(0);
}

void Node::setParent(Node_ptr parent) {
	m_parent = parent;
}

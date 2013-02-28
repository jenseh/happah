#include "happah/scene/Node.h"

const Node_ptr Node::NULL_NODE;

Node::Node() {}

Node::~Node() {}

void Node::accept(SceneVisitor& sceneVisitor) {
	for(set<Node_ptr>::iterator i = m_children.begin(), end = m_children.end(); i != end; ++i)
		(*i)->accept(sceneVisitor);
}

void Node::addChild(Node_ptr child) {
	if(child) 
		m_children.insert(child);
}

bool const Node::contains(shared_ptr<void> data) {
	return false;
}

Node_ptr const Node::find(shared_ptr<void> data) {
	for(set<Node_ptr>::iterator i = m_children.begin(), end = m_children.end(); i != end; ++i) {
		Node_ptr child = *i;
		if(child->contains(data)) return child;
		Node_ptr node = child->find(data);
		if(node) return node;
	}

	return NULL_NODE;
}

void Node::removeChild(Node_ptr child) {
	if(child)
		m_children.erase(child);
}


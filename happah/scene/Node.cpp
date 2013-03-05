#include "happah/scene/Node.h"

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

bool Node::contains(shared_ptr<void> data) const {
	return false;
}

void Node::draw(DrawVisitor& drawVisitor, RigidAffineTransformation& rigidAffineTransformation) {
	for(set<Node_ptr>::iterator i = m_children.begin(), end = m_children.end(); i != end; ++i)
		(*i)->draw(drawVisitor, rigidAffineTransformation);
}

Node_ptr Node::findContaining(shared_ptr<void> data) const {
	for(set<Node_ptr>::iterator i = m_children.begin(), end = m_children.end(); i != end; ++i) {
		Node_ptr child = *i;
		if(child->contains(data)) return child;
		Node_ptr node = child->findContaining(data);
		if(node) return node;
	}

	return Node_ptr();
}

Node_ptr Node::findChildContaining(shared_ptr<void> data) const {
	for(set<Node_ptr>::iterator i = m_children.begin(), end = m_children.end(); i != end; ++i) {
		Node_ptr child = *i;
		if(child->contains(data)) return child;
	}

	return Node_ptr();
}

bool Node::hasChild(Node_ptr child) const {
	for(set<Node_ptr>::iterator i = m_children.begin(), end = m_children.end(); i != end; ++i)
		if(*i == child) return true;
	return false;
}

void Node::removeChildContaining(shared_ptr<void> data) {
	Node_ptr child;
	for(set<Node_ptr>::iterator i = m_children.begin(), end = m_children.end(); i != end; ++i) {
		child = *i;
		if(child->contains(data)) break;
	}
	if(child)
		m_children.erase(child);
}

void Node::removeChild(Node_ptr child) {
	if(child)
		m_children.erase(child);
}


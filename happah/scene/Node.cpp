#include "happah/scene/Node.h"

Node::Node() {}

Node::~Node() {}

void Node::accept(GUIVisitor& guiVisitor) {
	for(set<Node_ptr>::iterator i = m_children.begin(), end = m_children.end(); i != end; ++i)
		(*i)->accept(guiVisitor);
}

void Node::accept(SceneVisitor& sceneVisitor) {
	for(set<Node_ptr>::iterator i = m_children.begin(), end = m_children.end(); i != end; ++i)
		(*i)->accept(sceneVisitor);
}

bool Node::contains(shared_ptr<void> data) const {
	return false;
}

bool Node::doRemove(Node_ptr node) {
	for(set<Node_ptr>::iterator i = m_children.begin(), end = m_children.end(); i != end; ++i) {
		Node_ptr child = *i;
		if(child == node) {
			m_children.erase(i);
			return true;
		} else if(child->doRemove(node))
			return true;
	}
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

Node_ptr Node::getParent() {
	return m_parent.lock();
}

Node_ptr Node::getptr() {
	return shared_from_this();
}

bool Node::hasChild(Node_ptr child) const {
	for(set<Node_ptr>::iterator i = m_children.begin(), end = m_children.end(); i != end; ++i)
		if(*i == child) return true;
	return false;
}

void Node::insertChild(Node_ptr child) {
	if(child) {
		child->setParent(getptr());
		m_children.insert(child);
	}
}

bool Node::remove(Node_ptr node) {
	return doRemove(node);
}

bool Node::remove(vector<Node_ptr>& nodes) {
	bool removed = false;
	for(vector<Node_ptr>::iterator i = nodes.begin(), end = nodes.end(); i != end; ++i)
		removed |= doRemove(*i);
	return removed;
}

bool Node::removeContaining(shared_ptr<void> parentData, shared_ptr<void> childData) {
	Node_ptr node = findContaining(parentData);

	if(node)
		return node->removeChildContaining(childData);

	return false;
}

bool Node::removeChildContaining(shared_ptr<void> data) {
	Node_ptr child;
	for(set<Node_ptr>::iterator i = m_children.begin(), end = m_children.end(); i != end; ++i) {
		child = *i;
		if(child->contains(data)) break;
	}
	return removeChild(child);
}

bool Node::removeChild(Node_ptr child) {
	if(child) {
		const set<Node_ptr>::iterator i = m_children.find(child);
		if(i == m_children.end())
			return false;
		m_children.erase(i);
		return true;
	}
	return false;
}

void Node::setParent(Node_ptr parent) {
	m_parent = weak_ptr<Node>(parent);
}


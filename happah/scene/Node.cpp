#include "happah/scene/Node.h"
#include <iostream>

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

void Node::accept(SimulationVisitor& simulationVisitor) {
    for(set<Node_ptr>::iterator i = m_children.begin(), end = m_children.end(); i != end; ++i)
        (*i)->accept(simulationVisitor);
}


bool Node::contains(shared_ptr<void> data) const {
	return false;
}

Node_ptr Node::doRemove(Node_ptr node) {
	for(set<Node_ptr>::iterator i = m_children.begin(), end = m_children.end(); i != end; ++i) {
		Node_ptr child = *i;
		if(child == node) {
			m_children.erase(i);
			return child;
		} else {
			Node_ptr descendant = child->doRemove(node);
			if(descendant) return descendant;
		}
	}
	return Node_ptr();
}

void Node::draw(DrawVisitor& drawVisitor, RigidAffineTransformation& rigidAffineTransformation) {
	for(set<Node_ptr>::iterator i = m_children.begin(), end = m_children.end(); i != end; ++i)
		(*i)->draw(drawVisitor, rigidAffineTransformation);
}

Node_ptr Node::findContainingData(shared_ptr<void> data) const {
	for(set<Node_ptr>::iterator i = m_children.begin(), end = m_children.end(); i != end; ++i) {
		Node_ptr child = *i;
		if(child->contains(data)) return child;
		Node_ptr node = child->findContainingData(data);
		if(node) return node;
	}

	return Node_ptr();
}

Node_ptr Node::findChildContainingData(shared_ptr<void> data) const {
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

Node_ptr Node::remove(Node_ptr node) {
	return doRemove(node);
}

void Node::remove(vector<Node_ptr>& nodes) {
	for(vector<Node_ptr>::iterator i = nodes.begin(), end = nodes.end(); i != end; ++i)
		doRemove(*i);
}

void Node::remove(vector<Node_ptr>& nodes, vector<Node_ptr>& removedNodes) {
	for(vector<Node_ptr>::iterator i = nodes.begin(), end = nodes.end(); i != end; ++i) {
		Node_ptr removedNode = doRemove(*i);
		if(removedNode) removedNodes.push_back(removedNode);
	}
}

Node_ptr Node::removeContainingData(shared_ptr<void> parentData, shared_ptr<void> childData) {
	Node_ptr node = findContainingData(parentData);
	if(node)
		return node->removeChildContainingData(childData);
	return Node_ptr();
}

Node_ptr Node::removeChildContainingData(shared_ptr<void> data) {
	Node_ptr child;
	for(set<Node_ptr>::iterator i = m_children.begin(), end = m_children.end(); i != end; ++i) {
		child = *i;
		if(child->contains(data))
			return removeChild(child);
	}
	return Node_ptr();
}

Node_ptr Node::removeChild(Node_ptr child) {
	if(child) {
		const set<Node_ptr>::iterator i = m_children.find(child);
		if(i != m_children.end()) {
			m_children.erase(i);
			return child;
		}
	}
	return Node_ptr();
}

void Node::setParent(Node_ptr parent) {
	m_parent = weak_ptr<Node>(parent);
}


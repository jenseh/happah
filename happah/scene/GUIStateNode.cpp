#include "happah/scene/GUIStateNode.h"

GUIStateNode::GUIStateNode(string name)
	: m_name(name) {}

GUIStateNode::~GUIStateNode() {}

const string& GUIStateNode::getName() const {
	return m_name;
}

TriangleMesh_ptr GUIStateNode::getTriangleMesh() const {
	return m_triangleMesh;
}

void GUIStateNode::setName(const char* name) {
	m_name = string(name);
}

void GUIStateNode::setTriangleMesh(TriangleMesh_ptr triangleMesh) {
	m_triangleMesh = triangleMesh;
}

InvoluteGearGUIStateNode::InvoluteGearGUIStateNode(InvoluteGear_ptr involuteGear, InvoluteGearForm* involuteGearForm, string name)
	: GUIStateNode(name), m_involuteGear(involuteGear), m_involuteGearForm(involuteGearForm) {}

InvoluteGearGUIStateNode::~InvoluteGearGUIStateNode() {}

void InvoluteGearGUIStateNode::accept(GUIVisitor& guiVisitor) {
	guiVisitor.visit(getptr());
	Node::accept(guiVisitor);
}

Form* InvoluteGearGUIStateNode::getForm() {
	m_involuteGearForm->setInvoluteGear(m_involuteGear);
	return m_involuteGearForm;
}

InvoluteGear_ptr InvoluteGearGUIStateNode::getInvoluteGear() const {
	return m_involuteGear;
}

InvoluteGearGUIStateNode_ptr InvoluteGearGUIStateNode::getptr() {
	return static_pointer_cast<InvoluteGearGUIStateNode>(shared_from_this());
}

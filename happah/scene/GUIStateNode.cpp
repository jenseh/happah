#include "happah/scene/GUIStateNode.h"

GUIStateNode::GUIStateNode(const char* name)
	: m_name(name) {}

GUIStateNode::~GUIStateNode() {}

const string& GUIStateNode::getName() const {
	return m_name;
}

void GUIStateNode::setName(const char* name) {
	m_name = string(name);
}

InvoluteGearGUIStateNode::InvoluteGearGUIStateNode(InvoluteGear_ptr involuteGear, InvoluteGearForm* involuteGearForm, const char* name)
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

InvoluteGearGUIStateNode_ptr InvoluteGearGUIStateNode::getptr() {
	return shared_from_this();
}

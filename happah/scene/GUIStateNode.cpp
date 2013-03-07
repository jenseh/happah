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

InvoluteGearGUIStateNode::~InvoluteGearGUIStateNode() {
	if(m_involuteGearForm->getInvoluteGear() == m_involuteGear)
		m_involuteGearForm->reset();
}

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

PlaneGUIStateNode::PlaneGUIStateNode( Plane_ptr plane, PlaneForm* planeForm, string name ) :
	GUIStateNode(name), m_plane(plane), m_planeForm(planeForm) {
}

PlaneGUIStateNode::~PlaneGUIStateNode() {
	if(m_planeForm->getPlane() == m_plane) {
		m_planeForm->reset();
	}
}

void PlaneGUIStateNode::accept(GUIVisitor& guiVisitor) {
	guiVisitor.visit(getptr());
	Node::accept(guiVisitor);
}

Form* PlaneGUIStateNode::getForm() {
	m_planeForm->setPlane(m_plane);
	return m_planeForm;
}

Plane_ptr PlaneGUIStateNode::getPlane() const {
	return m_plane;
}

PlaneGUIStateNode_ptr PlaneGUIStateNode::getptr() {
	return static_pointer_cast<PlaneGUIStateNode>(shared_from_this());
}

SimpleGearGUIStateNode::SimpleGearGUIStateNode(SimpleGear_ptr simpleGear, SimpleGearForm* simpleGearForm, string name)
	: GUIStateNode(name), m_simpleGear(simpleGear), m_simpleGearForm(simpleGearForm) {}

SimpleGearGUIStateNode::~SimpleGearGUIStateNode() {
	if(m_simpleGearForm->getSimpleGear() == m_simpleGear)
		m_simpleGearForm->reset();
}

void SimpleGearGUIStateNode::accept(GUIVisitor& guiVisitor) {
	guiVisitor.visit(getptr());
	Node::accept(guiVisitor);
}

Form* SimpleGearGUIStateNode::getForm() {
	m_simpleGearForm->setSimpleGear(m_simpleGear);
	return m_simpleGearForm;
}

SimpleGear_ptr SimpleGearGUIStateNode::getSimpleGear() const {
	return m_simpleGear;
}

SimpleGearGUIStateNode_ptr SimpleGearGUIStateNode::getptr() {
	return static_pointer_cast<SimpleGearGUIStateNode>(shared_from_this());
}


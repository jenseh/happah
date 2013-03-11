#include "happah/scene/GUIStateNode.h"

GUIStateNode::GUIStateNode(string name)
	: m_name(name) {}

GUIStateNode::~GUIStateNode() {}

void GUIStateNode::accept(GUIVisitor& guiVisitor) {
	guiVisitor.visit(getptr());
	Node::accept(guiVisitor);
}

ContextMenu* GUIStateNode::getContextMenu() {
	return NULL;
}

const string& GUIStateNode::getName() const {
	return m_name;
}

GUIStateNode_ptr GUIStateNode::getptr() {
	return static_pointer_cast<GUIStateNode>(shared_from_this());
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

shared_ptr<void> InvoluteGearGUIStateNode::getData() const {
	return m_involuteGear;
}

Form* InvoluteGearGUIStateNode::getForm() {
	m_involuteGearForm->setInvoluteGear(m_involuteGear);
	return m_involuteGearForm;
}

PlaneGUIStateNode::PlaneGUIStateNode( Plane_ptr plane, PlaneForm* planeForm, string name ) :
	GUIStateNode(name), m_plane(plane), m_planeForm(planeForm) {
}

PlaneGUIStateNode::~PlaneGUIStateNode() {
	if(m_planeForm->getPlane() == m_plane) {
		m_planeForm->reset();
	}
}

shared_ptr<void> PlaneGUIStateNode::getData() const {
	return m_plane;
}

Form* PlaneGUIStateNode::getForm() {
	m_planeForm->setPlane(m_plane);
	return m_planeForm;
}

SimpleGearGUIStateNode::SimpleGearGUIStateNode(SimpleGear_ptr simpleGear, SimpleGearForm* simpleGearForm, string name)
	: GUIStateNode(name), m_simpleGear(simpleGear), m_simpleGearForm(simpleGearForm) {}

SimpleGearGUIStateNode::~SimpleGearGUIStateNode() {
	if(m_simpleGearForm->getSimpleGear() == m_simpleGear)
		m_simpleGearForm->reset();
}

shared_ptr<void> SimpleGearGUIStateNode::getData() const {
	return m_simpleGear;
}

Form* SimpleGearGUIStateNode::getForm() {
	m_simpleGearForm->setSimpleGear(m_simpleGear);
	return m_simpleGearForm;
}

DiscGUIStateNode::DiscGUIStateNode(Disc_ptr disc, DiscForm* discForm, string name)
	: GUIStateNode(name), m_disc(disc), m_discForm(discForm) {}

DiscGUIStateNode::~DiscGUIStateNode() {
	if(m_discForm->getDisc() == m_disc)
		m_discForm->reset();
}

shared_ptr<void> DiscGUIStateNode::getData() const {
	return m_disc;
}

Form* DiscGUIStateNode::getForm() {
	m_discForm->setDisc(m_disc);
	return m_discForm;
}


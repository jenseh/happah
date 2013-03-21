#include "happah/scene/GUIStateNode.h"

GUIStateNode::GUIStateNode(string& name)
	: m_name(name) {}

GUIStateNode::~GUIStateNode() {}

void GUIStateNode::accept(GUIVisitor& guiVisitor) {
	guiVisitor.visit(getptr());
	Node::accept(guiVisitor);
}

ContextMenu* GUIStateNode::getContextMenu() const {
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

// BSplineCurve

BSplineCurveGUIStateNode::BSplineCurveGUIStateNode(
		BSplineCurve_ptr curve,
		BSplineCurveForm* bSplineCurveForm,
		string name )
	: GUIStateNode(name), m_curve(curve), m_bSplineCurveForm(bSplineCurveForm)
{}

BSplineCurveGUIStateNode::~BSplineCurveGUIStateNode()
{
	if(m_bSplineCurveForm->getCurve() == m_curve) {
		m_bSplineCurveForm->reset();
	}
}

shared_ptr<void> BSplineCurveGUIStateNode::getData() const {
	return m_curve;
}

Form* BSplineCurveGUIStateNode::getForm() {
	m_bSplineCurveForm->setCurve(m_curve);
	return m_bSplineCurveForm;
}

// InvoluteGear

InvoluteGearGUIStateNode::InvoluteGearGUIStateNode(
	InvoluteGear_ptr involuteGear,
	InvoluteGearForm* involuteGearForm, 
	InvoluteGearContextMenu* contextMenu, 
	string name
) : GUIStateNode(name), 
	m_involuteGear(involuteGear), 
	m_involuteGearForm(involuteGearForm), 
	m_involuteGearContextMenu(contextMenu) {
}

InvoluteGearGUIStateNode::~InvoluteGearGUIStateNode() {
	if(m_involuteGearForm->getInvoluteGear() == m_involuteGear)
		m_involuteGearForm->reset();
}


ContextMenu* InvoluteGearGUIStateNode::getContextMenu() const {
	m_involuteGearContextMenu->setInvoluteGear(m_involuteGear);
	return m_involuteGearContextMenu;
}

shared_ptr<void> InvoluteGearGUIStateNode::getData() const {
	return m_involuteGear;
}

Form* InvoluteGearGUIStateNode::getForm() {
	m_involuteGearForm->setInvoluteGear(m_involuteGear);
	return m_involuteGearForm;
}

// Plane

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

SimpleGearGUIStateNode::SimpleGearGUIStateNode(SimpleGear_ptr simpleGear, SimpleGearForm* simpleGearForm, SimpleGearContextMenu* simpleGearContextMenu, string name)
	: GUIStateNode(name), m_simpleGear(simpleGear), m_simpleGearForm(simpleGearForm), m_simpleGearContextMenu(simpleGearContextMenu) {}

SimpleGearGUIStateNode::~SimpleGearGUIStateNode() {
	if(m_simpleGearForm->getSimpleGear() == m_simpleGear)
		m_simpleGearForm->reset();
}

ContextMenu* SimpleGearGUIStateNode::getContextMenu() const {
	m_simpleGearContextMenu->setSimpleGear(m_simpleGear, getTriangleMesh());
	return m_simpleGearContextMenu;
}

shared_ptr<void> SimpleGearGUIStateNode::getData() const {
	return m_simpleGear;
}

Form* SimpleGearGUIStateNode::getForm() {
	m_simpleGearForm->setSimpleGear(m_simpleGear);
	return m_simpleGearForm;
}

DiscGUIStateNode::DiscGUIStateNode(Disc_ptr disc, DiscForm* discForm, DiscContextMenu* discContextMenu, string name)
	: GUIStateNode(name), m_disc(disc), m_discForm(discForm), m_discContextMenu(discContextMenu) {}

DiscGUIStateNode::~DiscGUIStateNode() {
	if(m_discForm->getDisc() == m_disc)
		m_discForm->reset();
}

ContextMenu* DiscGUIStateNode::getContextMenu() const {
	m_discContextMenu->setDisc(m_disc, getTriangleMesh());
	return m_discContextMenu;
}

shared_ptr<void> DiscGUIStateNode::getData() const {
	return m_disc;
}

Form* DiscGUIStateNode::getForm() {
	m_discForm->setDisc(m_disc);
	return m_discForm;
}

// Worm

WormGUIStateNode::WormGUIStateNode(Worm_ptr worm, WormForm* wormForm, string name)
	: GUIStateNode(name), m_worm(worm), m_wormForm(wormForm) {}

WormGUIStateNode::~WormGUIStateNode() {
	if(m_wormForm->getWorm() == m_worm)
		m_wormForm->reset();
}

shared_ptr<void> WormGUIStateNode::getData() const {
	return m_worm;
}

Form* WormGUIStateNode::getForm() {
	m_wormForm->setWorm(m_worm);
	return m_wormForm;
}

SpherePatchGUIStateNode::SpherePatchGUIStateNode(SpherePatch_ptr spherePatch, SpherePatchForm* spherePatchForm, string name)
	: GUIStateNode(name), m_spherePatch(spherePatch), m_spherePatchForm(spherePatchForm) {}

SpherePatchGUIStateNode::~SpherePatchGUIStateNode() {
	if(m_spherePatchForm->getSpherePatch() == m_spherePatch)
		m_spherePatchForm->reset();
}

shared_ptr<void> SpherePatchGUIStateNode::getData() const {
	return m_spherePatch;
}

Form* SpherePatchGUIStateNode::getForm() {
	m_spherePatchForm->setSpherePatch(m_spherePatch);
	return m_spherePatchForm;
}

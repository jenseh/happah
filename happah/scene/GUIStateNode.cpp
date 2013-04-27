#include "happah/scene/GUIStateNode.h"

GUIStateNode::GUIStateNode(string& name)
	: m_name(name),m_selectListener(*this),m_connectListener(*this) {}

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
	return static_pointer_cast<GUIStateNode>(shared_from_this()); //TODO: what is this?
}

TriangleMesh_ptr GUIStateNode::getTriangleMesh() const {
	return m_triangleMesh;
}

LineMesh_ptr GUIStateNode::getLineMesh() const {
	return m_lineMesh;
}

PointCloud_ptr GUIStateNode::getPointCloud() const {
	return m_pointCloud;
}

void GUIStateNode::setName(const char* name) {
	m_name = string(name);
}

void GUIStateNode::setTriangleMesh(TriangleMesh_ptr triangleMesh) {
	m_triangleMesh = triangleMesh;
}

void GUIStateNode::setLineMesh(LineMesh_ptr lineMesh){
	m_lineMesh = lineMesh;
}
void GUIStateNode::setPointCloud(PointCloud_ptr pointCloud){
	m_pointCloud = pointCloud;
}

void GUIStateNode::GUISelectListener::handleSelectEvent(){
	m_guiStateNode.getForm()->handleSelection();
}

void GUIStateNode::GUISelectListener::handleSelectEvent(int pointIndex){
	m_guiStateNode.getForm()->handleSelection(pointIndex);
}

void GUIStateNode::GUISelectListener::handleDeselectEvent(){

}

void GUIStateNode::GUIConnectListener::handleConnectionEvent(){
	m_guiStateNode.getForm()->handleConnection();
}

void GUIStateNode::registerConnectListener(ConnectListener* connectListener){
	m_connectListeners.push_back(connectListener);
}

void GUIStateNode::removeConnectListener(ConnectListener* connectListener){
	m_connectListeners.remove(connectListener);
}

void GUIStateNode::triggerConnectionEvent(){
	for(list<ConnectListener*>::iterator i = m_connectListeners.begin(), end = m_connectListeners.end(); i != end; ++i)
				(*i)->handleConnectionEvent();
}

// BSplineCurve

BSplineCurveGUIStateNode::BSplineCurveGUIStateNode(
	BSplineCurve2D_ptr curve,
	BSplineCurveForm* bSplineCurveForm,
	BSplineCurveContextMenu* bSplineCurveContextMenu,
	string name
) : GUIStateNode(name),
	m_curve(curve),
	m_bSplineCurveForm(bSplineCurveForm),
	m_bSplineCurveContextMenu(bSplineCurveContextMenu) {}

BSplineCurveGUIStateNode::~BSplineCurveGUIStateNode()
{
	if(m_bSplineCurveForm->getCurve() == m_curve) {
		m_bSplineCurveForm->reset();
	}
}

ContextMenu* BSplineCurveGUIStateNode::getContextMenu() const {
	m_bSplineCurveContextMenu->setBSplineCurve(m_curve);
	return m_bSplineCurveContextMenu;
}

shared_ptr<void> BSplineCurveGUIStateNode::getData() const {
	return m_curve;
}

Form* BSplineCurveGUIStateNode::getForm() {
	m_bSplineCurveForm->setCurve(m_curve);
	return m_bSplineCurveForm;
}

// Disc

DiscGUIStateNode::DiscGUIStateNode(SurfaceOfRevolution_ptr disc, DiscForm* discForm, DiscContextMenu* discContextMenu, string name)
	: GUIStateNode(name), m_surfaceOfRevolution(disc), m_discForm(discForm), m_discContextMenu(discContextMenu) {}

DiscGUIStateNode::~DiscGUIStateNode() {
	if(m_discForm->getDisc() == m_surfaceOfRevolution)
		m_discForm->reset();
}

ContextMenu* DiscGUIStateNode::getContextMenu() const {
	m_discContextMenu->setDisc(m_surfaceOfRevolution, getTriangleMesh());
	return m_discContextMenu;
}

shared_ptr<void> DiscGUIStateNode::getData() const {
	return m_surfaceOfRevolution;
}

Form* DiscGUIStateNode::getForm() {
	m_discForm->setDisc(m_surfaceOfRevolution);
	return m_discForm;
}

SurfaceOfRevolution_ptr DiscGUIStateNode::getSurfaceOfRevolution()const{
	return m_surfaceOfRevolution;
}

// DiscGearGrind

DiscGearGrindGUIStateNode::DiscGearGrindGUIStateNode(DiscGearGrind_ptr discGearGrind, SimulationForm* simulationForm, SimulationContextMenu* simulationContextMenu, string name)
	:	GUIStateNode(name), m_discGearGrind(discGearGrind), m_simulationForm(simulationForm), m_simulationContextMenu(simulationContextMenu) {}

DiscGearGrindGUIStateNode::~DiscGearGrindGUIStateNode() {
//	if(m_simulationForm->getDiscGearGrind() == m_discGearGrind) {
		m_simulationForm->reset();
//	}
}

ContextMenu* DiscGearGrindGUIStateNode::getContextMenu() const {
	m_simulationContextMenu->setSimulation(m_discGearGrind);
	return m_simulationContextMenu;
}

shared_ptr<void> DiscGearGrindGUIStateNode::getData() const {
	return m_discGearGrind;
}

Form* DiscGearGrindGUIStateNode::getForm() {
//	m_simulationForm->setDiscGearGrind(m_discGearGrind);
	return m_simulationForm;
}

// Focal Spline

FocalSplineGUIStateNode::FocalSplineGUIStateNode(
		FocalSpline_ptr focalSpline,
		FocalSplineForm* focalSplineForm,
		string name)
	: GUIStateNode(name), m_focalSpline(focalSpline),m_focalSplineForm(focalSplineForm) {

}
FocalSplineGUIStateNode::~FocalSplineGUIStateNode()
{
	if(m_focalSplineForm->getFocalSpline() == m_focalSpline) {
		m_focalSplineForm->reset();
	}
}

shared_ptr<void> FocalSplineGUIStateNode::getData() const {
	return m_focalSpline;
}

Form* FocalSplineGUIStateNode::getForm() {
	m_focalSplineForm->setFocalSpline(m_focalSpline);
	return m_focalSplineForm;
}



// InvoluteGear

InvoluteGearGUIStateNode::InvoluteGearGUIStateNode(
	InvoluteGear_ptr involuteGear,
	InvoluteGearForm* involuteGearForm, 
	InvoluteGearContextMenu* contextMenu, 
	string name
) : GUIStateNode(name), 
	m_involuteGear(involuteGear),
	m_involuteGearContextMenu(contextMenu),
	m_involuteGearForm(involuteGearForm) {
}

InvoluteGearGUIStateNode::~InvoluteGearGUIStateNode() {
	if(m_involuteGearForm->getInvoluteGear() == m_involuteGear)
		m_involuteGearForm->reset();
}

ContextMenu* InvoluteGearGUIStateNode::getContextMenu() const {
	m_involuteGearContextMenu->setInvoluteGear(m_involuteGear, getTriangleMesh());
	return m_involuteGearContextMenu;
}

shared_ptr<void> InvoluteGearGUIStateNode::getData() const {
	return m_involuteGear;
}

Form* InvoluteGearGUIStateNode::getForm() {
	m_involuteGearForm->setInvoluteGear(m_involuteGear);
	return m_involuteGearForm;
}

InvoluteGear_ptr InvoluteGearGUIStateNode::getInvoluteGear()const {
	return m_involuteGear;
}

// Plane

PlaneGUIStateNode::PlaneGUIStateNode( Plane_ptr plane, PlaneForm* planeForm, PlaneContextMenu* contextMenu, string name ) :
	GUIStateNode(name), m_plane(plane), m_planeContextMenu(contextMenu), m_planeForm(planeForm) {
}

PlaneGUIStateNode::~PlaneGUIStateNode() {
	if(m_planeForm->getPlane() == m_plane) {
		m_planeForm->reset();
	}
}

ContextMenu* PlaneGUIStateNode::getContextMenu() const {
	m_planeContextMenu->setPlane(m_plane);
	return m_planeContextMenu;
}

shared_ptr<void> PlaneGUIStateNode::getData() const {
	return m_plane;
}

Form* PlaneGUIStateNode::getForm() {
	m_planeForm->setPlane(m_plane);
	return m_planeForm;
}

// SimpleGear

SimpleGearGUIStateNode::SimpleGearGUIStateNode(SimpleGear_ptr simpleGear, SimpleGearForm* simpleGearForm, SimpleGearContextMenu* simpleGearContextMenu, string name)
	: GUIStateNode(name), m_simpleGear(simpleGear), m_simpleGearContextMenu(simpleGearContextMenu), m_simpleGearForm(simpleGearForm) {}

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

SimpleGear_ptr SimpleGearGUIStateNode::getSimpleGear()const {
	return m_simpleGear;
}

// SpherePatch

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

// ToothProfile

ToothProfileGUIStateNode::ToothProfileGUIStateNode (
	ToothProfile_ptr toothProfile,
	ToothProfileForm* toothProfileForm,
	ToothProfileContextMenu* toothProfileContextMenu,
	string name
) : GUIStateNode(name),
	m_toothProfile(toothProfile),
	m_toothProfileForm(toothProfileForm),
	m_toothProfileContextMenu(toothProfileContextMenu) {
}

ToothProfileGUIStateNode::~ToothProfileGUIStateNode()
{
	if(m_toothProfileForm->getToothProfile() == m_toothProfile) {
		m_toothProfileForm->reset();
	}
}

ContextMenu* ToothProfileGUIStateNode::getContextMenu() const {
	m_toothProfileContextMenu->setToothProfile(m_toothProfile);
	return m_toothProfileContextMenu;
}

shared_ptr<void> ToothProfileGUIStateNode::getData() const {
	return m_toothProfile;
}

Form* ToothProfileGUIStateNode::getForm() {
	m_toothProfileForm->setToothProfile(m_toothProfile);
	return m_toothProfileForm;
}

// TriangleMesh

TriangleMeshGUIStateNode::TriangleMeshGUIStateNode (TriangleMesh_ptr triangleMesh, TriangleMeshContextMenu* triangleMeshContextMenu, string name) 
	: GUIStateNode(name), m_triangleMesh(triangleMesh), m_triangleMeshContextMenu(triangleMeshContextMenu) {}

TriangleMeshGUIStateNode::~TriangleMeshGUIStateNode() {}

ContextMenu* TriangleMeshGUIStateNode::getContextMenu() const {
	m_triangleMeshContextMenu->setTriangleMesh(m_triangleMesh);
	return m_triangleMeshContextMenu;
}

shared_ptr<void> TriangleMeshGUIStateNode::getData() const {
	return m_triangleMesh;
}

Form* TriangleMeshGUIStateNode::getForm() {
	return 0;
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


Worm_ptr WormGUIStateNode::getWorm() const {
	return m_worm;
}

// WormGearGrind

WormGearGrindGUIStateNode::WormGearGrindGUIStateNode(WormGearGrind_ptr wormGearGrind, SimulationForm* simulationForm, SimulationContextMenu* simulationContextMenu, string name)
	:	GUIStateNode(name), m_wormGearGrind(wormGearGrind), m_simulationForm(simulationForm), m_simulationContextMenu(simulationContextMenu) {}

WormGearGrindGUIStateNode::~WormGearGrindGUIStateNode() {
//	if(m_simulationForm->getWormGearGrind() == m_wormGearGrind) //TODO
//		m_simulationForm->reset();
}

ContextMenu* WormGearGrindGUIStateNode::getContextMenu() const {
	m_simulationContextMenu->setSimulation(m_wormGearGrind);
	return m_simulationContextMenu;
}

shared_ptr<void> WormGearGrindGUIStateNode::getData() const {
	return m_wormGearGrind;
}

Form* WormGearGrindGUIStateNode::getForm() {
//	m_simulationForm->setWormGearGrind(m_wormGearGrind);
	return m_simulationForm;
}

#include <sstream>

#include "happah/gui/GUIManager.h"

GUIManager::GUIManager(SceneManager_ptr sceneManager)
	:  m_counter(0),
		m_drawManager(sceneManager), 
		m_mainWindow(*this, m_drawManager), 
		m_sceneGraphExplorerPanel(m_mainWindow.getSceneGraphExplorerPanel()),
		m_sceneManager(sceneManager),
		m_toolPanel(m_mainWindow.getToolPanel()) {
	m_sceneManager->registerListener(this);
}

GUIManager::~GUIManager() {
	vector<Node_ptr> guiStateNodes;
	guiStateNodes.reserve(m_guiStateNodes.size());
	for(auto i = m_guiStateNodes.begin(), end = m_guiStateNodes.end(); i != end; ++i)
		guiStateNodes.push_back(i->second);
	m_sceneManager->remove(guiStateNodes);
}

template<class G, class S, class F>
void GUIManager::doInsert3D(shared_ptr<G> geometry, const char* label, F* form) {
	TriangleMesh_ptr triangleMesh = TriangleMesh_ptr(geometry->toTriangleMesh());
	hpcolor color(1.0, 0.0, 0.0, 1.0);
	m_sceneManager->insert(geometry, triangleMesh, color);
	ostringstream oss;
	oss << label << " " << m_counter++;
	shared_ptr<S> guiStateNode = shared_ptr<S>(new S(geometry, form, oss.str()));
	guiStateNode->setTriangleMesh(triangleMesh);
	m_sceneManager->insert(geometry, guiStateNode);
}

template<class G>
void GUIManager::doUpdate3D(shared_ptr<G> geometry) {
	GUIStateNode_ptr guiStateNode = m_guiStateNodes[geometry];
	if(!guiStateNode) {
		cerr << "GUI state node not found." << endl;
		return;
	}
	m_sceneManager->removeContaining(geometry, guiStateNode->getTriangleMesh());
	TriangleMesh_ptr triangleMesh = TriangleMesh_ptr(geometry->toTriangleMesh());
	hpcolor color(1.0, 0.0, 0.0, 1.0);
	guiStateNode->setTriangleMesh(triangleMesh);
	m_sceneManager->insert(geometry, triangleMesh, color);
}

void GUIManager::handleGUIStateNodesDeletedEvent(vector<GUIStateNode_ptr>& guiStateNodes) {
	vector<Node_ptr> parents;
	parents.reserve(guiStateNodes.size());
	for(vector<GUIStateNode_ptr>::iterator i = guiStateNodes.begin(), end = guiStateNodes.end(); i != end; ++i)
		parents.push_back((*i)->getParent());
	m_sceneManager->remove(parents);
}

void GUIManager::handleGUIStateNodeSelectedEvent(GUIStateNode_ptr guiStateNode) {
	m_toolPanel->setForm(guiStateNode->getForm());
}

bool GUIManager::init() {
	if (!m_drawManager.init()) {
		fprintf(stderr, "Draw manager initialization failed.\n");
		return false;
	}
	m_mainWindow.show();
	return true;
}

void GUIManager::insert(InvoluteGear_ptr involuteGear) {
	doInsert3D<InvoluteGear, InvoluteGearGUIStateNode, InvoluteGearForm>(involuteGear, "Involute Gear", m_toolPanel->getInvoluteGearForm());
}

void GUIManager::insert(SimpleGear_ptr simpleGear) {
	doInsert3D<SimpleGear, SimpleGearGUIStateNode, SimpleGearForm>(simpleGear, "Simple Gear", m_toolPanel->getSimpleGearForm());
}

void GUIManager::insert( Plane_ptr plane ) {
	ostringstream oss;
	oss << "Plane " << m_counter++;
	PlaneGUIStateNode_ptr planeGUIStateNode = PlaneGUIStateNode_ptr(new PlaneGUIStateNode(plane, m_toolPanel->getPlaneForm(), oss.str()));
	m_sceneManager->insert(plane, planeGUIStateNode);
}

void GUIManager::update(InvoluteGear_ptr involuteGear) {
	doUpdate3D<InvoluteGear>(involuteGear);
}

void GUIManager::update(SimpleGear_ptr simpleGear) {
	doUpdate3D<SimpleGear>(simpleGear);
}

void GUIManager::sceneChanged() {
	m_guiStateNodes.clear();
	m_sceneGraphExplorerPanel->clear();
	m_sceneManager->accept(*this);
}

void GUIManager::visit(InvoluteGearGUIStateNode_ptr involuteGearGUIStateNode) {
	m_guiStateNodes[involuteGearGUIStateNode->getInvoluteGear()] = involuteGearGUIStateNode;
	m_sceneGraphExplorerPanel->addItem(QString(involuteGearGUIStateNode->getName().c_str()), involuteGearGUIStateNode);
}

void GUIManager::visit(PlaneGUIStateNode_ptr planeGUIStateNode) {
	m_guiStateNodes[planeGUIStateNode->getPlane()] = planeGUIStateNode;
	m_sceneGraphExplorerPanel->addItem(QString(planeGUIStateNode->getName().c_str()), planeGUIStateNode);
}

void GUIManager::visit(SimpleGearGUIStateNode_ptr simpleGearGUIStateNode) {
	m_guiStateNodes[simpleGearGUIStateNode->getSimpleGear()] = simpleGearGUIStateNode;
	m_sceneGraphExplorerPanel->addItem(QString(simpleGearGUIStateNode->getName().c_str()), simpleGearGUIStateNode);
}


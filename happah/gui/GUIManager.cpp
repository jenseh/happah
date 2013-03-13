#include <sstream>

#include "happah/gui/GUIManager.h"

GUIManager::GUIManager(SceneManager_ptr sceneManager)
	  : m_counter(0),
		m_contextMenuControl(m_mainWindow.getContextMenuControl()),
		m_drawManager(sceneManager),
		m_sceneGraphExplorerListener(*this),
		m_mainWindow(*this, m_sceneGraphExplorerListener, m_drawManager),
		m_sceneGraphExplorerPanel(m_mainWindow.getSceneGraphExplorerPanel()),
		m_sceneListener(*this),
		m_sceneManager(sceneManager),
		m_subtreesInsertedEventHandler(*this),
		m_subtreesRemovedEventHandler(*this),
		m_subtreesUpdatedEventHandler(*this),
		m_toolPanel(m_mainWindow.getToolPanel()){
	m_sceneManager->registerSceneListener(&m_sceneListener);
}

GUIManager::~GUIManager() {
	vector<Node_ptr> guiStateNodes;
	guiStateNodes.reserve(m_guiStateNodes.size());
	for(auto i = m_guiStateNodes.begin(), end = m_guiStateNodes.end(); i != end; ++i)
		guiStateNodes.push_back(i->second);
	m_sceneManager->remove(guiStateNodes);
}

template<class G, class S, class F, class M>
void GUIManager::doInsert3D(shared_ptr<G> geometry, const char* label, F* form, M* contextMenu) {
	TriangleMesh_ptr triangleMesh = TriangleMesh_ptr(geometry->toTriangleMesh());
	hpcolor color(1.0, 0.0, 0.0, 1.0);
	m_sceneManager->insert(geometry, triangleMesh, color);
	ostringstream oss;
	oss << label << " " << m_counter++;
	shared_ptr<S> guiStateNode = shared_ptr<S>(new S(geometry, form, contextMenu, oss.str()));
	guiStateNode->setTriangleMesh(triangleMesh);
	// if (contextMenu != NULL) {
	// 	guiStateNode->setContextMenu(contextMenu);
	// }
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


void GUIManager::handleMouseClickEvent(Ray ray){
	//TODO do something fancy here
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
	doInsert3D<InvoluteGear, InvoluteGearGUIStateNode, InvoluteGearForm, InvoluteGearContextMenu>(
		involuteGear, "Involute Gear", m_toolPanel->getInvoluteGearForm(), m_contextMenuControl->getInvoluteGearContextMenu());
}

void GUIManager::insert(SimpleGear_ptr simpleGear) {
	doInsert3D<SimpleGear, SimpleGearGUIStateNode, SimpleGearForm, ContextMenu>(simpleGear, "Simple Gear", m_toolPanel->getSimpleGearForm());
}

void GUIManager::insert(SimulationResult simulationResult) {
	m_sceneManager->insert(simulationResult.m_gear, simulationResult.m_gearMesh, simulationResult.m_gearColor, simulationResult.m_gearTransformation);
	hpcolor toolColor = hpcolor(1.0, 0.5, 0.5, 1.0);
	m_sceneManager->insert(simulationResult.m_tool, simulationResult.m_toolMesh, toolColor, simulationResult.m_toolTransformation);
}

void GUIManager::insert(Plane_ptr plane) {
	ostringstream oss;
	oss << "Plane " << m_counter++;
	doInsert3D<Plane, PlaneGUIStateNode, PlaneForm, ContextMenu>(plane, "Plane", m_toolPanel->getPlaneForm());
//	PlaneGUIStateNode_ptr planeGUIStateNode = PlaneGUIStateNode_ptr(new PlaneGUIStateNode(plane, m_toolPanel->getPlaneForm(), m_contextMenuControl->getContextMenu(), oss.str()));
//	m_sceneManager->insert(plane, planeGUIStateNode);
}

void GUIManager::insert(Disc_ptr disc) {
	doInsert3D<Disc, DiscGUIStateNode, DiscForm, ContextMenu>(disc, "Disc", m_toolPanel->getDiscForm());
}

void GUIManager::insert(Worm_ptr worm) {
	doInsert3D<Worm, WormGUIStateNode, WormForm, ContextMenu>(worm, "Worm", m_toolPanel->getWormForm());
}

void GUIManager::update(InvoluteGear_ptr involuteGear) {
	doUpdate3D<InvoluteGear>(involuteGear);
}

void GUIManager::update(SimpleGear_ptr simpleGear) {
	doUpdate3D<SimpleGear>(simpleGear);
}

void GUIManager::update(SimulationResult simulationResult) {

}

void GUIManager::update(Plane_ptr plane) {
	doUpdate3D<Plane>(plane);
}

void GUIManager::update(Disc_ptr disc) {
	doUpdate3D<Disc>(disc);
}

void GUIManager::update(Worm_ptr worm) {
	doUpdate3D<Worm>(worm);
}

GUIManager::DefaultSceneGraphExplorerListener::DefaultSceneGraphExplorerListener(GUIManager& guiManager)
	: m_guiManager(guiManager) {}

GUIManager::DefaultSceneGraphExplorerListener::~DefaultSceneGraphExplorerListener() {}

void GUIManager::DefaultSceneGraphExplorerListener::handleGUIStateNodesDeletedEvent(vector<GUIStateNode_ptr>& guiStateNodes) {
	vector<Node_ptr> parents;
	parents.reserve(guiStateNodes.size());
	for(vector<GUIStateNode_ptr>::iterator i = guiStateNodes.begin(), end = guiStateNodes.end(); i != end; ++i)
		parents.push_back((*i)->getParent());
	m_guiManager.m_sceneManager->remove(parents);
}

void GUIManager::DefaultSceneGraphExplorerListener::handleGUIStateNodeSelectedEvent(GUIStateNode_ptr guiStateNode) {
	m_guiManager.m_toolPanel->setForm(guiStateNode->getForm());
}

GUIManager::DefaultSceneListener::DefaultSceneListener(GUIManager& guiManager)
	: m_guiManager(guiManager) {}

GUIManager::DefaultSceneListener::~DefaultSceneListener() {}

void GUIManager::DefaultSceneListener::handleSubtreeInsertedEvent(Node_ptr root) {
	root->accept(m_guiManager.m_subtreesInsertedEventHandler);
}

void GUIManager::DefaultSceneListener::handleSubtreesInsertedEvent(vector<Node_ptr>& roots) {
	for(vector<Node_ptr>::iterator i = roots.begin(), end = roots.end(); i != end; ++i)
		(*i)->accept(m_guiManager.m_subtreesInsertedEventHandler);
}

void GUIManager::DefaultSceneListener::handleSubtreeRemovedEvent(Node_ptr root) {
	root->accept(m_guiManager.m_subtreesRemovedEventHandler);
}

void GUIManager::DefaultSceneListener::handleSubtreesRemovedEvent(vector<Node_ptr>& roots) {
	for(vector<Node_ptr>::iterator i = roots.begin(), end = roots.end(); i != end; ++i)
		(*i)->accept(m_guiManager.m_subtreesRemovedEventHandler);
}

void GUIManager::DefaultSceneListener::handleSubtreeUpdatedEvent(Node_ptr root) {
	root->accept(m_guiManager.m_subtreesUpdatedEventHandler);
}

void GUIManager::DefaultSceneListener::handleSubtreesUpdatedEvent(vector<Node_ptr>& roots) {
	for(vector<Node_ptr>::iterator i = roots.begin(), end = roots.end(); i != end; ++i)
		(*i)->accept(m_guiManager.m_subtreesUpdatedEventHandler);
}

GUIManager::SubtreesInsertedEventHandler::SubtreesInsertedEventHandler(GUIManager& guiManager)
	: m_guiManager(guiManager) {}

GUIManager::SubtreesInsertedEventHandler::~SubtreesInsertedEventHandler() {}

void GUIManager::SubtreesInsertedEventHandler::visit(GUIStateNode_ptr guiStateNode) {
	m_guiManager.m_guiStateNodes[guiStateNode->getData()] = guiStateNode;
	m_guiManager.m_sceneGraphExplorerPanel->insert(guiStateNode);
}

GUIManager::SubtreesRemovedEventHandler::SubtreesRemovedEventHandler(GUIManager& guiManager)
	: m_guiManager(guiManager) {}

GUIManager::SubtreesRemovedEventHandler::~SubtreesRemovedEventHandler() {}

void GUIManager::SubtreesRemovedEventHandler::visit(GUIStateNode_ptr guiStateNode) {
	m_guiManager.m_guiStateNodes.erase(guiStateNode->getData());
	m_guiManager.m_sceneGraphExplorerPanel->remove(guiStateNode);
}

GUIManager::SubtreesUpdatedEventHandler::SubtreesUpdatedEventHandler(GUIManager& guiManager)
	: m_guiManager(guiManager) {}

GUIManager::SubtreesUpdatedEventHandler::~SubtreesUpdatedEventHandler() {}

void GUIManager::SubtreesUpdatedEventHandler::visit(GUIStateNode_ptr guiStateNode) {
	m_guiManager.m_sceneGraphExplorerPanel->update(guiStateNode);
}


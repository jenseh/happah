#include <sstream>

#include "happah/gui/DefaultGUIManager.h"

DefaultGUIManager::DefaultGUIManager(SceneManager_ptr sceneManager)
	  : m_counter(0),
		m_drawManager(sceneManager),
		m_sceneGraphExplorerListener(*this),
		m_viewport3DListener(*this),
		m_mainWindow(*this, m_viewport3DListener, m_sceneGraphExplorerListener, m_drawManager),
		m_sceneGraphExplorerPanel(m_mainWindow.getSceneGraphExplorerPanel()),
		m_sceneListener(*this),
		m_sceneManager(sceneManager),
		m_subtreesInsertedEventHandler(*this),
		m_subtreesRemovedEventHandler(*this),
		m_subtreesUpdatedEventHandler(*this),
		m_toolPanel(m_mainWindow.getToolPanel()) {
	m_sceneManager->registerSceneListener(&m_sceneListener);
}

DefaultGUIManager::~DefaultGUIManager() {
	vector<Node_ptr> guiStateNodes;
	guiStateNodes.reserve(m_guiStateNodes.size());
	for(auto i = m_guiStateNodes.begin(), end = m_guiStateNodes.end(); i != end; ++i)
		guiStateNodes.push_back(i->second);
	m_sceneManager->remove(guiStateNodes);
}

template<class G, class S>
void DefaultGUIManager::doInsert3D(shared_ptr<G> geometry, shared_ptr<S> guiStateNode) {
	TriangleMesh_ptr triangleMesh = TriangleMesh_ptr(geometry->toTriangleMesh());
	hpcolor color(1.0, 0.0, 0.0, 1.0);
	m_sceneManager->insert(geometry, triangleMesh, color);
	guiStateNode->setTriangleMesh(triangleMesh);
	m_sceneManager->insert(geometry, guiStateNode);
}

template<class G, class S, class F>
void DefaultGUIManager::doInsert3D(shared_ptr<G> geometry, const char* label, F* form) {
	shared_ptr<S> guiStateNode = shared_ptr<S>(new S(geometry, form, toFinalLabel(label)));
	doInsert3D(geometry, guiStateNode);
}

template<class G, class S, class F, class M>
void DefaultGUIManager::doInsert3D(shared_ptr<G> geometry, const char* label, F* form, M* contextMenu) {
	shared_ptr<S> guiStateNode = shared_ptr<S>(new S(geometry, form, contextMenu, toFinalLabel(label)));
	doInsert3D(geometry, guiStateNode);
}

template<class G>
void DefaultGUIManager::doUpdate3D(shared_ptr<G> geometry) {
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

bool DefaultGUIManager::init() {
	if (!m_drawManager.init()) {
		fprintf(stderr, "Draw manager initialization failed.\n");
		return false;
	}
	m_mainWindow.show();
	return true;
}

void DefaultGUIManager::insert(DiscGearGrindResult simulationResult) {
	m_sceneManager->insert(simulationResult.m_gear, simulationResult.m_gearMesh, simulationResult.m_gearColor, simulationResult.m_gearTransformation);
	hpcolor toolColor = hpcolor(1.0, 0.5, 0.5, 1.0);
	m_sceneManager->insert(simulationResult.m_tool, simulationResult.m_toolMesh, toolColor, simulationResult.m_toolTransformation);
}

void DefaultGUIManager::insert(InvoluteGear_ptr involuteGear) {
	doInsert3D<InvoluteGear, InvoluteGearGUIStateNode, InvoluteGearForm, InvoluteGearContextMenu>(
		involuteGear, "Involute Gear", m_toolPanel->getInvoluteGearForm(), m_mainWindow.getInvoluteGearContextMenu());
}

void DefaultGUIManager::insert(SimpleGear_ptr simpleGear) {
	doInsert3D<SimpleGear, SimpleGearGUIStateNode, SimpleGearForm>(simpleGear, "Simple Gear", m_toolPanel->getSimpleGearForm());
}

void DefaultGUIManager::insert(Plane_ptr plane) {
	ostringstream oss;
//	oss << "Plane " << m_counter++; TODO: m_counter is increased in doInsert3D call => delete this???
	doInsert3D<Plane, PlaneGUIStateNode, PlaneForm>(plane, "Plane", m_toolPanel->getPlaneForm());
//	PlaneGUIStateNode_ptr planeGUIStateNode = PlaneGUIStateNode_ptr(new PlaneGUIStateNode(plane, m_toolPanel->getPlaneForm(), oss.str()));
//	m_sceneManager->insert(plane, planeGUIStateNode);
}

void DefaultGUIManager::insert(Disc_ptr disc) {
	doInsert3D<Disc, DiscGUIStateNode, DiscForm>(disc, "Disc", m_toolPanel->getDiscForm());
}

void DefaultGUIManager::insert(Worm_ptr worm) {
	doInsert3D<Worm, WormGUIStateNode, WormForm>(worm, "Worm", m_toolPanel->getWormForm());
}

void DefaultGUIManager::insert(SpherePatch_ptr spherePatch) {
	doInsert3D<SpherePatch, SpherePatchGUIStateNode, SpherePatchForm>(spherePatch, "SpherePatch", m_toolPanel->getSpherePatchForm());
}

string DefaultGUIManager::toFinalLabel(const char* label) {
	ostringstream oss;
	oss << label << " " << m_counter++;
	return oss.str();
}

void DefaultGUIManager::update(DiscGearGrindResult simulationResult) {
	m_sceneManager->removeContaining(simulationResult.m_gear, simulationResult.m_gearMesh);
	m_sceneManager->insert(simulationResult.m_gear, simulationResult.m_gearMesh, simulationResult.m_gearColor, simulationResult.m_gearTransformation);
}

void DefaultGUIManager::update(InvoluteGear_ptr involuteGear) {
	doUpdate3D<InvoluteGear>(involuteGear);
}

void DefaultGUIManager::update(SimpleGear_ptr simpleGear) {
	doUpdate3D<SimpleGear>(simpleGear);
}

void DefaultGUIManager::update(Plane_ptr plane) {
	doUpdate3D<Plane>(plane);
}

void DefaultGUIManager::update(Disc_ptr disc) {
	doUpdate3D<Disc>(disc);
}

void DefaultGUIManager::update(Worm_ptr worm) {
	doUpdate3D<Worm>(worm);
}
void DefaultGUIManager::update(SpherePatch_ptr spherePatch) {
	doUpdate3D<SpherePatch>(spherePatch);
}

void DefaultGUIManager::visitScene(SceneVisitor& visitor) {
	m_sceneManager->accept(visitor);

}

DefaultGUIManager::DefaultSceneGraphExplorerListener::DefaultSceneGraphExplorerListener(DefaultGUIManager& defaultGUIManager)
	: m_defaultGUIManager(defaultGUIManager) {}

DefaultGUIManager::DefaultSceneGraphExplorerListener::~DefaultSceneGraphExplorerListener() {}

void DefaultGUIManager::DefaultSceneGraphExplorerListener::handleGUIStateNodesDeletedEvent(vector<GUIStateNode_ptr>& guiStateNodes) {
	vector<Node_ptr> parents;
	parents.reserve(guiStateNodes.size());
	for(vector<GUIStateNode_ptr>::iterator i = guiStateNodes.begin(), end = guiStateNodes.end(); i != end; ++i)
		parents.push_back((*i)->getParent());
	m_defaultGUIManager.m_sceneManager->remove(parents);
}

void DefaultGUIManager::DefaultSceneGraphExplorerListener::handleGUIStateNodeSelectedEvent(GUIStateNode_ptr guiStateNode) {
	m_defaultGUIManager.m_toolPanel->setForm(guiStateNode->getForm());
}

DefaultGUIManager::DefaultSceneListener::DefaultSceneListener(DefaultGUIManager& defaultGUIManager)
	: m_defaultGUIManager(defaultGUIManager) {}

DefaultGUIManager::DefaultSceneListener::~DefaultSceneListener() {}

void DefaultGUIManager::DefaultSceneListener::handleSubtreeInsertedEvent(Node_ptr root) {
	root->accept(m_defaultGUIManager.m_subtreesInsertedEventHandler);
}

void DefaultGUIManager::DefaultSceneListener::handleSubtreesInsertedEvent(vector<Node_ptr>& roots) {
	for(vector<Node_ptr>::iterator i = roots.begin(), end = roots.end(); i != end; ++i)
		(*i)->accept(m_defaultGUIManager.m_subtreesInsertedEventHandler);
}

void DefaultGUIManager::DefaultSceneListener::handleSubtreeRemovedEvent(Node_ptr root) {
	root->accept(m_defaultGUIManager.m_subtreesRemovedEventHandler);
}

void DefaultGUIManager::DefaultSceneListener::handleSubtreesRemovedEvent(vector<Node_ptr>& roots) {
	for(vector<Node_ptr>::iterator i = roots.begin(), end = roots.end(); i != end; ++i)
		(*i)->accept(m_defaultGUIManager.m_subtreesRemovedEventHandler);
}

void DefaultGUIManager::DefaultSceneListener::handleSubtreeUpdatedEvent(Node_ptr root) {
	root->accept(m_defaultGUIManager.m_subtreesUpdatedEventHandler);
}

void DefaultGUIManager::DefaultSceneListener::handleSubtreesUpdatedEvent(vector<Node_ptr>& roots) {
	for(vector<Node_ptr>::iterator i = roots.begin(), end = roots.end(); i != end; ++i)
		(*i)->accept(m_defaultGUIManager.m_subtreesUpdatedEventHandler);
}

DefaultGUIManager::DefaultViewport3DListener::DefaultViewport3DListener(DefaultGUIManager& defaultGUIManager)
	: m_defaultGUIManager(defaultGUIManager) {}

DefaultGUIManager::DefaultViewport3DListener::~DefaultViewport3DListener() {}

void DefaultGUIManager::DefaultViewport3DListener::DefaultViewport3DListener::handleMouseClickEvent(Ray& ray) {
	RayIntersectionVisitor intersectionVisitor(ray);
	m_defaultGUIManager.m_sceneManager->accept( intersectionVisitor );
	if( intersectionVisitor.hasGotIntersection() ) {
		hpvec3 secPoint = intersectionVisitor.getFirstIntersection();
		std::cout << "(" << secPoint.x << ", " << secPoint.y << ", " << secPoint.z << ")" << std::endl;
	}
	else {
		std::cout << "No intersection." << std::endl;
	}
}

DefaultGUIManager::SubtreesInsertedEventHandler::SubtreesInsertedEventHandler(DefaultGUIManager& defaultGUIManager)
	: m_defaultGUIManager(defaultGUIManager) {}

DefaultGUIManager::SubtreesInsertedEventHandler::~SubtreesInsertedEventHandler() {}

void DefaultGUIManager::SubtreesInsertedEventHandler::visit(GUIStateNode_ptr guiStateNode) {
	m_defaultGUIManager.m_guiStateNodes[guiStateNode->getData()] = guiStateNode;
	m_defaultGUIManager.m_sceneGraphExplorerPanel->insert(guiStateNode);
}

DefaultGUIManager::SubtreesRemovedEventHandler::SubtreesRemovedEventHandler(DefaultGUIManager& defaultGUIManager)
	: m_defaultGUIManager(defaultGUIManager) {}

DefaultGUIManager::SubtreesRemovedEventHandler::~SubtreesRemovedEventHandler() {}

void DefaultGUIManager::SubtreesRemovedEventHandler::visit(GUIStateNode_ptr guiStateNode) {
	m_defaultGUIManager.m_guiStateNodes.erase(guiStateNode->getData());
	m_defaultGUIManager.m_sceneGraphExplorerPanel->remove(guiStateNode);
}

DefaultGUIManager::SubtreesUpdatedEventHandler::SubtreesUpdatedEventHandler(DefaultGUIManager& defaultGUIManager)
	: m_defaultGUIManager(defaultGUIManager) {}

DefaultGUIManager::SubtreesUpdatedEventHandler::~SubtreesUpdatedEventHandler() {}

void DefaultGUIManager::SubtreesUpdatedEventHandler::visit(GUIStateNode_ptr guiStateNode) {
	m_defaultGUIManager.m_sceneGraphExplorerPanel->update(guiStateNode);
}


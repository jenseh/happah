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
void DefaultGUIManager::doInsert2D(shared_ptr<G> geometry, shared_ptr<S> guiStateNode) {
	TriangleMesh_ptr triangleMesh = TriangleMesh_ptr(geometry->toTriangleMesh());
	hpcolor color(1.0, 0.0, 0.0, 1.0);
	m_sceneManager->insert(geometry, triangleMesh, color);
	guiStateNode->setTriangleMesh(triangleMesh);
	m_sceneManager->insert(geometry, guiStateNode);
}

template<class G, class S, class F>
void DefaultGUIManager::doInsert2D(shared_ptr<G> geometry, const char* label, F* form) {
	shared_ptr<S> guiStateNode = shared_ptr<S>(new S(geometry, form, toFinalLabel(label)));
	doInsert2D(geometry, guiStateNode);
}

template<class G, class S, class F, class M>
void DefaultGUIManager::doInsert2D(shared_ptr<G> geometry, const char* label, F* form, M* contextMenu) {
	shared_ptr<S> guiStateNode = shared_ptr<S>(new S(geometry, form, contextMenu, toFinalLabel(label)));
	doInsert2D(geometry, guiStateNode);
}

template<class G, class S>
void DefaultGUIManager::doInsert1D(shared_ptr<G> geometry, shared_ptr<S> guiStateNode) {
	LineMesh_ptr lineMesh = LineMesh_ptr(geometry->toLineMesh());
	hpcolor color(1.0, 0.0, 0.0, 1.0);
	m_sceneManager->insert(geometry, lineMesh, color);
	guiStateNode->setLineMesh(lineMesh);
	m_sceneManager->insert(geometry, guiStateNode);
}

template<class G, class S, class F>
void DefaultGUIManager::doInsert1D(shared_ptr<G> geometry, const char* label, F* form) {
	shared_ptr<S> guiStateNode = shared_ptr<S>(new S(geometry, form, toFinalLabel(label)));
	doInsert1D(geometry, guiStateNode);
}

template<class G, class S>
void DefaultGUIManager::doInsert0D(shared_ptr<G> geometry, shared_ptr<S> guiStateNode){
	PointCloud_ptr pointCloud = PointCloud_ptr(geometry->toPointCloud());
	hpcolor color(0.0f,1.0f,0.0f,1.0f);
	m_sceneManager->insert(geometry,pointCloud,color);
	guiStateNode->setPointCloud(pointCloud);
	m_sceneManager->insert(geometry,guiStateNode);
}

template<class G, class S, class F>
void DefaultGUIManager::doInsert0D(shared_ptr<G> geometry, const char* label, F* form) {
	shared_ptr<S> guiStateNode = shared_ptr<S>(new S(geometry, form, toFinalLabel(label)));
	doInsert0D(geometry, guiStateNode);
}

template<class G>
void DefaultGUIManager::doUpdate2D(shared_ptr<G> geometry) {
	GUIStateNode_ptr guiStateNode = m_guiStateNodes[geometry];
	if(!guiStateNode) {
		cerr << "GUI state node not found." << endl;
		return;
	}
	m_sceneManager->removeContainingData(geometry, guiStateNode->getTriangleMesh());
	TriangleMesh_ptr triangleMesh = TriangleMesh_ptr(geometry->toTriangleMesh());
	hpcolor color(1.0, 0.0, 0.0, 1.0);
	guiStateNode->setTriangleMesh(triangleMesh);
	m_sceneManager->insert(geometry, triangleMesh, color);
}

void DefaultGUIManager::generateDisc(Gear_ptr gear) {
	SurfaceOfRevolution_ptr disc = DiscGenerator::generateDiscFrom(*gear);
	insert(disc, HP_TRIANGLE_MESH);
}

bool DefaultGUIManager::init() {
	if (!m_drawManager.init()) {
		fprintf(stderr, "Draw manager initialization failed.\n");
		return false;
	}
	m_mainWindow.show();
	return true;
}

void DefaultGUIManager::insert(BSplineCurve_ptr bSplineCurve,hpuint drawMode) {
	hpcolor color(0.0, 1.0, 0.0, 1.0);
	PointCloud_ptr pointCloud = PointCloud_ptr(bSplineCurve->toPointCloud());
	m_sceneManager->insert(bSplineCurve, pointCloud, color);
	BSplineCurveGUIStateNode_ptr guiStateNode = BSplineCurveGUIStateNode_ptr(new BSplineCurveGUIStateNode(
				bSplineCurve, m_toolPanel->getBSplineCurveForm(), toFinalLabel("BSplineCurve") ));
	m_sceneManager->insert(bSplineCurve, guiStateNode);
}

void DefaultGUIManager::insert(SurfaceOfRevolution_ptr disc,hpuint drawMode) {
	if (drawMode & HP_TRIANGLE_MESH)
		doInsert2D<SurfaceOfRevolution, DiscGUIStateNode, DiscForm, DiscContextMenu>(disc, "Disc",  m_toolPanel->getDiscForm(), m_mainWindow.getDiscContextMenu() );
}

/*
void DefaultGUIManager::insert(DiscGearGrindResult simulationResult) {
	m_sceneManager->insert(simulationResult.m_gear, simulationResult.m_gearMesh, simulationResult.m_gearColor, simulationResult.m_gearTransformation);
	hpcolor toolColor = hpcolor(1.0, 0.5, 0.5, 1.0);
	m_sceneManager->insert(simulationResult.m_tool, simulationResult.m_toolMesh, toolColor, simulationResult.m_toolTransformation);
}
*/

void DefaultGUIManager::insert(DiscGearGrind_ptr discGearGrind) {
    m_sceneManager->insert(discGearGrind);
}

void DefaultGUIManager::insert(InvoluteGear_ptr involuteGear,hpuint drawMode) {
	if (drawMode & HP_TRIANGLE_MESH)
		doInsert2D<InvoluteGear, InvoluteGearGUIStateNode, InvoluteGearForm, InvoluteGearContextMenu>(
				involuteGear, "Involute Gear", m_toolPanel->getInvoluteGearForm(), m_mainWindow.getInvoluteGearContextMenu());
}

void DefaultGUIManager::insert(Plane_ptr plane,hpuint drawMode) {

	if (drawMode & HP_TRIANGLE_MESH)
		doInsert2D<Plane, PlaneGUIStateNode, PlaneForm>(plane, "Plane", m_toolPanel->getPlaneForm());
	if (drawMode & HP_LINE_MESH){
		doInsert1D<Plane,PlaneGUIStateNode, PlaneForm>(plane,"Plane",m_toolPanel->getPlaneForm());
	}
	if (drawMode & HP_POINT_CLOUD){
		doInsert0D<Plane,PlaneGUIStateNode, PlaneForm>(plane,"Plane",m_toolPanel->getPlaneForm());
	}
}

void DefaultGUIManager::insert(SimpleGear_ptr simpleGear,hpuint drawMode) {
	if (drawMode & HP_TRIANGLE_MESH)
		doInsert2D<SimpleGear, SimpleGearGUIStateNode, SimpleGearForm, SimpleGearContextMenu>(simpleGear, "Simple Gear", m_toolPanel->getSimpleGearForm(), m_mainWindow.getSimpleGearContextMenu());
}

void DefaultGUIManager::insert(SpherePatch_ptr spherePatch,hpuint drawMode) {
	if (drawMode & HP_TRIANGLE_MESH)
		doInsert2D<SpherePatch, SpherePatchGUIStateNode, SpherePatchForm>(spherePatch, "SpherePatch", m_toolPanel->getSpherePatchForm());
}

void DefaultGUIManager::insert(Worm_ptr worm,hpuint drawMode) {
	if (drawMode & HP_TRIANGLE_MESH)
		doInsert2D<Worm, WormGUIStateNode, WormForm>(worm, "Worm", m_toolPanel->getWormForm());
}

string DefaultGUIManager::toFinalLabel(const char* label) {
	ostringstream oss;
	oss << label << " " << m_counter++;
	return oss.str();
}

void DefaultGUIManager::update(BSplineCurve_ptr bSplineCurve) {
}

void DefaultGUIManager::update(SurfaceOfRevolution_ptr disc) {
	doUpdate2D<SurfaceOfRevolution>(disc);
}

/*
void DefaultGUIManager::update(DiscGearGrindResult simulationResult) {
	m_sceneManager->removeContainingData(simulationResult.m_gear, simulationResult.m_gearMesh);
	m_sceneManager->insert(simulationResult.m_gear, simulationResult.m_gearMesh, simulationResult.m_gearColor, simulationResult.m_gearTransformation);
	m_sceneManager->removeContainingData(simulationResult.m_tool, simulationResult.m_toolMesh);
	hpcolor toolColor = hpcolor(1.0, 0.5, 0.5, 0.1);
	m_sceneManager->insert(simulationResult.m_tool, simulationResult.m_toolMesh, toolColor, simulationResult.m_toolTransformation);
} */

void DefaultGUIManager::update(InvoluteGear_ptr involuteGear) {
	doUpdate2D<InvoluteGear>(involuteGear);
}

void DefaultGUIManager::update(Plane_ptr plane) {
	doUpdate2D<Plane>(plane);
}

void DefaultGUIManager::update(SimpleGear_ptr simpleGear) {
	doUpdate2D<SimpleGear>(simpleGear);
}

void DefaultGUIManager::update(SpherePatch_ptr spherePatch) {
	doUpdate2D<SpherePatch>(spherePatch);
}

void DefaultGUIManager::update(Worm_ptr worm) {
	doUpdate2D<Worm>(worm);
}

void DefaultGUIManager::useInSimulation(SurfaceOfRevolution_ptr disc, TriangleMesh_ptr discMesh) {
	m_toolPanel->getSimulationForm()->setDisc(disc, discMesh);
}

void DefaultGUIManager::useInSimulation(SimpleGear_ptr gear, TriangleMesh_ptr gearMesh){
	m_toolPanel->getSimulationForm()->setGear(gear, gearMesh);
}

void DefaultGUIManager::visitScene(SceneVisitor& visitor) {
	m_sceneManager->accept(visitor);
}

void DefaultGUIManager::visitScene(SimulationVisitor& visitor) {
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


#include <sstream>

#include "happah/gui/DefaultGUIManager.h"

DefaultGUIManager::DefaultGUIManager(SceneManager_ptr sceneManager)
	  : m_counter(0),
		m_drawManager(sceneManager),
		m_sceneGraphExplorerListener(*this),
		m_viewportListener(*this),
		m_mainWindow(*this, m_viewportListener, m_sceneGraphExplorerListener, m_drawManager),
		m_sceneGraphExplorerPanel(m_mainWindow.getSceneGraphExplorerPanel()),
		m_sceneListener(*this),
		m_sceneManager(sceneManager),
		m_subtreesInsertedEventHandler(*this),
		m_subtreesRemovedEventHandler(*this),
		m_subtreesUpdatedEventHandler(*this),
		m_toolPanel(m_mainWindow.getToolPanel()){
	m_sceneManager->registerSceneListener(&m_sceneListener);
}

DefaultGUIManager::~DefaultGUIManager() {
	vector<Node_ptr> guiStateNodes;
	guiStateNodes.reserve(m_guiStateNodes.size());
	for(auto i = m_guiStateNodes.begin(), end = m_guiStateNodes.end(); i != end; ++i)
		guiStateNodes.push_back(i->second);
	m_sceneManager->remove(guiStateNodes);
}

void DefaultGUIManager::createDiscGearGrind(SimpleGear_ptr simpleGear) {
	TriangleMesh_ptr gearMesh = TriangleMesh_ptr(simpleGear->toTriangleMesh());
	SurfaceOfRevolution_ptr disc = DiscGenerator::generateDiscFrom(*simpleGear);
	TriangleMesh_ptr discMesh = disc->toTriangleMesh();
	DiscGearGrind_ptr simulation = DiscGearGrind_ptr(new DiscGearGrind(disc, discMesh, simpleGear, gearMesh));

	QThread* thread = new QThread();
	DiscGearGrindWorkerListener* listener = new DiscGearGrindWorkerListener(this);
	DiscGearGrindWorker* discGearGrindWorker = new DiscGearGrindWorker(simulation, thread, listener);
	thread->start();
}

void DefaultGUIManager::createDiscGearGrind(SurfaceOfRevolution_ptr disc, SimpleGear_ptr simpleGear) {
	TriangleMesh_ptr gearMesh = TriangleMesh_ptr(simpleGear->toTriangleMesh());
	TriangleMesh_ptr discMesh = disc->toTriangleMesh();
	DiscGearGrind_ptr simulation = DiscGearGrind_ptr(new DiscGearGrind(disc, discMesh, simpleGear, gearMesh));

	QThread* thread = new QThread();
	DiscGearGrindWorkerListener* listener = new DiscGearGrindWorkerListener(this);
	DiscGearGrindWorker* discGearGrindWorker = new DiscGearGrindWorker(simulation, thread, listener);
	thread->start();
}

template<class G, class S>
void DefaultGUIManager::doInsert2D(shared_ptr<G> geometry, shared_ptr<S> guiStateNode) {
	TriangleMesh_ptr triangleMesh = TriangleMesh_ptr(geometry->toTriangleMesh());
	hpcolor color(1.0, 0.0, 0.0, 1.0);
	TriangleMeshRenderStateNode_ptr triangleMeshRenderStateNode = m_sceneManager->insert(geometry, triangleMesh, color);
	guiStateNode->setTriangleMesh(triangleMesh);
	m_sceneManager->insert(geometry, guiStateNode);
	triangleMeshRenderStateNode->registerSelectListener(guiStateNode->getSelectListener());
	//TODO: Find a way to Remove the listener again

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
	LineMeshRenderStateNode_ptr lineMeshRenderStateNode = m_sceneManager->insert(geometry, lineMesh, color);
	guiStateNode->setLineMesh(lineMesh);
	m_sceneManager->insert(geometry, guiStateNode);
	lineMeshRenderStateNode->registerSelectListener(guiStateNode->getSelectListener());
}

template<class G, class S, class F>
void DefaultGUIManager::doInsert1D(shared_ptr<G> geometry, const char* label, F* form) {
	shared_ptr<S> guiStateNode = shared_ptr<S>(new S(geometry, form, toFinalLabel(label)));
	doInsert1D(geometry, guiStateNode);
}

template<class G, class S, class F, class M>
void DefaultGUIManager::doInsert1D(shared_ptr<G> geometry, const char* label, F* form, M* contextMenu) {
	shared_ptr<S> guiStateNode = shared_ptr<S>(new S(geometry, form, contextMenu, toFinalLabel(label)));
	doInsert1D(geometry, guiStateNode);
}

template<class G, class S>
void DefaultGUIManager::doInsert0D(shared_ptr<G> geometry, shared_ptr<S> guiStateNode){
	PointCloud_ptr pointCloud = PointCloud_ptr(geometry->toPointCloud());
	hpcolor color(0.0f,1.0f,0.0f,1.0f);

	PointCloudRenderStateNode_ptr pointCloudRenderStateNode = m_sceneManager->insert(geometry,pointCloud,color);
	guiStateNode->setPointCloud(pointCloud);
	m_sceneManager->insert(geometry,guiStateNode);
	pointCloudRenderStateNode->registerSelectListener(guiStateNode->getSelectListener());
}

template<class G, class S, class F>
void DefaultGUIManager::doInsert0D(shared_ptr<G> geometry, const char* label, F* form) {
	shared_ptr<S> guiStateNode = shared_ptr<S>(new S(geometry, form, toFinalLabel(label)));
	// TODO : guiStateNode->registerForm
	doInsert0D(geometry, guiStateNode);
}

template<class G, class S, class F, class M>
void DefaultGUIManager::doInsert0D(shared_ptr<G> geometry, const char* label, F* form, M* contextMenu) {
	shared_ptr<S> guiStateNode = shared_ptr<S>(new S(geometry, form, contextMenu, toFinalLabel(label)));
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
	TriangleMeshRenderStateNode_ptr triangleMeshRenderStateNode =m_sceneManager->insert(geometry, triangleMesh, color);
	triangleMeshRenderStateNode->registerSelectListener(guiStateNode->getSelectListener());
}

template<class G>
void DefaultGUIManager::doUpdate1D(shared_ptr<G> geometry) {
	GUIStateNode_ptr guiStateNode = m_guiStateNodes[geometry];
	if(!guiStateNode) {
		cerr << "GUI state node not found." << endl;
		return;
	}
	m_sceneManager->removeContainingData(geometry, guiStateNode->getLineMesh());
	LineMesh_ptr lineMesh = LineMesh_ptr(geometry->toLineMesh());
	hpcolor color(1.0, 0.0, 0.0, 1.0);
	guiStateNode->setLineMesh(lineMesh);
	LineMeshRenderStateNode_ptr lineMeshRenderStateNode = m_sceneManager->insert(geometry, lineMesh, color);
	lineMeshRenderStateNode->registerSelectListener(guiStateNode->getSelectListener());

}

template<class G>
void DefaultGUIManager::doUpdate0D(shared_ptr<G> geometry) {
	GUIStateNode_ptr guiStateNode = m_guiStateNodes[geometry];
	if(!guiStateNode) {
		cerr << "GUI state node not found." << endl;
		return;
	}
	m_sceneManager->removeContainingData(geometry, guiStateNode->getPointCloud());
	PointCloud_ptr pointCloud = PointCloud_ptr(geometry->toPointCloud());
	hpcolor color(1.0, 0.0, 0.0, 1.0);
	guiStateNode->setPointCloud(pointCloud);
	PointCloudRenderStateNode_ptr pointCloudRenderStateNode = m_sceneManager->insert(geometry, pointCloud, color);
	pointCloudRenderStateNode->registerSelectListener(guiStateNode->getSelectListener());
}


void DefaultGUIManager::generateDisc(CylindricalGear_ptr cylindricalGear) {
	SurfaceOfRevolution_ptr disc = DiscGenerator::generateDiscFrom(*cylindricalGear);
	insert(disc, HP_TRIANGLE_MESH);
}


Plane_ptr DefaultGUIManager::getParentPlane( BSplineCurve_ptr bSplineCurve ) {
	Node_ptr parent = m_sceneManager->findContainingData(bSplineCurve)->getParent();
	
	PlaneNode_ptr planeNode = dynamic_pointer_cast<PlaneNode>(parent);
	if( planeNode ) {
		Plane_ptr plane = static_pointer_cast<Plane>(planeNode->getGeometry());
		return plane;
	}

	return Plane_ptr();
}

const SceneManager_ptr DefaultGUIManager::getSceneManager() {
	return m_sceneManager;
}

bool DefaultGUIManager::init() {
	if (!m_drawManager.init()) {
		fprintf(stderr, "Draw manager initialization failed.\n");
		return false;
	}
	m_mainWindow.show();

//	Plane_ptr plane = Plane_ptr( new Plane( hpvec3(0.0f, 0.0f, 0.0f), hpvec3(0.0f, 1.0f, 0.0f) ));
//	m_sceneManager->insert(plane);
	return true;
}

void DefaultGUIManager::insert(BSplineCurve_ptr bSplineCurve, hpuint drawMode) {

	if( drawMode & HP_LINE_MESH ) {
		doInsert1D<BSplineCurve, BSplineCurveGUIStateNode, BSplineCurveForm, BSplineCurveContextMenu>(
				bSplineCurve, "BSplineCurve", m_toolPanel->getBSplineCurveForm(), m_mainWindow.getBSplineCurveContextMenu());
	}

	if( drawMode & HP_POINT_CLOUD ) {
		doInsert0D<BSplineCurve, BSplineCurveGUIStateNode, BSplineCurveForm, BSplineCurveContextMenu>(
				bSplineCurve, "BSplineCurve", m_toolPanel->getBSplineCurveForm(), m_mainWindow.getBSplineCurveContextMenu());
	}

}

void DefaultGUIManager::insert(SurfaceOfRevolution_ptr disc,hpuint drawMode) {
	if (drawMode & HP_TRIANGLE_MESH)
		doInsert2D<SurfaceOfRevolution, DiscGUIStateNode, DiscForm, DiscContextMenu>(disc, "Disc",  m_toolPanel->getDiscForm(), m_mainWindow.getDiscContextMenu() );
}


void DefaultGUIManager::insert(DiscGearGrind_ptr discGearGrind) {
    DiscGearGrindGUIStateNode_ptr guiStateNode = DiscGearGrindGUIStateNode_ptr(new DiscGearGrindGUIStateNode(
    			discGearGrind, m_toolPanel->getSimulationForm(), m_mainWindow.getSimulationContextMenu(), toFinalLabel("Disc gear grind simulation") ));
    m_sceneManager->insert(discGearGrind, guiStateNode);
}
void DefaultGUIManager::insert(FocalSpline_ptr focalSpline,hpuint drawMode){
	if(drawMode & HP_TRIANGLE_MESH){
			// DO nothing .. we don't want triangles
			//doInsert2D<FocalSpline,FocalSplineGUIStateNode,FocalSplineForm>(focalSpline,"Focal Spline",m_toolPanel->getFocalSplineForm());
	}
	if(drawMode & HP_POINT_CLOUD){
			doInsert0D<FocalSpline,FocalSplineGUIStateNode,FocalSplineForm>(focalSpline,"Focal Spline",m_toolPanel->getFocalSplineForm());
		}

	if(drawMode & HP_LINE_MESH){
		doInsert1D<FocalSpline,FocalSplineGUIStateNode,FocalSplineForm>(focalSpline,"Focal Spline",m_toolPanel->getFocalSplineForm());
	}

}

void DefaultGUIManager::insert(InvoluteGear_ptr involuteGear,hpuint drawMode) {
	if (drawMode & HP_TRIANGLE_MESH)
		doInsert2D<InvoluteGear, InvoluteGearGUIStateNode, InvoluteGearForm, InvoluteGearContextMenu>(
				involuteGear, "Involute Gear", m_toolPanel->getInvoluteGearForm(), m_mainWindow.getInvoluteGearContextMenu());
}

void DefaultGUIManager::insert(Plane_ptr plane, BSplineCurve_ptr curve) {
	m_sceneManager->insert(plane, curve);
}

void DefaultGUIManager::insert(Plane_ptr plane, hpuint drawMode) {

	if (drawMode & HP_TRIANGLE_MESH) {
		doInsert2D<Plane, PlaneGUIStateNode, PlaneForm, PlaneContextMenu>
			(plane, "Plane", m_toolPanel->getPlaneForm(), m_mainWindow.getPlaneContextMenu());
	}
	if (drawMode & HP_LINE_MESH) {
		doInsert1D<Plane, PlaneGUIStateNode, PlaneForm, PlaneContextMenu>
			(plane, "Plane", m_toolPanel->getPlaneForm(), m_mainWindow.getPlaneContextMenu());
	}
	if (drawMode & HP_POINT_CLOUD) {
		doInsert0D<Plane, PlaneGUIStateNode, PlaneForm, PlaneContextMenu>
			(plane, "Plane", m_toolPanel->getPlaneForm(), m_mainWindow.getPlaneContextMenu());
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

void DefaultGUIManager::insert(ToothProfile_ptr toothProfile, hpuint drawMode) {
	if(drawMode & HP_LINE_MESH) {
		doInsert1D<ToothProfile, ToothProfileGUIStateNode, ToothProfileForm>(toothProfile, "Tooth Profile", m_toolPanel->getToothProfileForm());
	}
	if(drawMode & HP_POINT_CLOUD) {
		doInsert0D<ToothProfile, ToothProfileGUIStateNode, ToothProfileForm>(toothProfile, "Tooth Profile", m_toolPanel->getToothProfileForm());
	}
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
	/*
	GUIStateNode_ptr guiStateNode = m_guiStateNodes[bSplineCurve];
	if(!guiStateNode) {
		cerr << "GUI state node not found." << endl;
		return;
	}
	// FIXME : old point cloud needs to be deleted
	//m_sceneManager->removeContaining(bSplineCurve, guiStateNode->getPointCloud());

	PointCloud_ptr pointCloud = PointCloud_ptr(bSplineCurve->toPointCloud());
	hpcolor color(0.0, 1.0, 0.0, 1.0);
	//guiStateNode->setPointCloud( pointCloud );
	m_sceneManager->insert(bSplineCurve, pointCloud, color);

	LineMesh_ptr lineMesh = LineMesh_ptr(bSplineCurve->toLineMesh());
	m_sceneManager->insert(bSplineCurve, lineMesh, color);
	*/
	doUpdate0D<BSplineCurve>(bSplineCurve);
	doUpdate1D<BSplineCurve>(bSplineCurve);
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
void DefaultGUIManager::update(FocalSpline_ptr focalSpline){
	doUpdate1D<FocalSpline>(focalSpline);
	doUpdate0D<FocalSpline>(focalSpline);

}

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

void DefaultGUIManager::update(ToothProfile_ptr toothProfile) {
	doUpdate0D<ToothProfile>(toothProfile);
	doUpdate1D<ToothProfile>(toothProfile);
}

void DefaultGUIManager::update(Worm_ptr worm) {
	doUpdate2D<Worm>(worm);
}

void DefaultGUIManager::useForBSpline(Plane_ptr plane) {
	m_toolPanel->getBSplineCurveForm()->reset();
	m_toolPanel->getBSplineCurveForm()->setPlane(plane);
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

void DefaultGUIManager::DefaultSceneGraphExplorerListener::createDiscGearGrind(SurfaceOfRevolution_ptr surfaceOfRevolution, SimpleGear_ptr simpleGear) {
	m_defaultGUIManager.createDiscGearGrind(surfaceOfRevolution, simpleGear);
}

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

DefaultGUIManager::DefaultViewportListener::DefaultViewportListener(DefaultGUIManager& defaultGUIManager)
	: m_defaultGUIManager(defaultGUIManager) {}

DefaultGUIManager::DefaultViewportListener::~DefaultViewportListener() {}

void DefaultGUIManager::DefaultViewportListener::DefaultViewportListener::handleMouseClickEvent(Ray& ray) {
	m_defaultGUIManager.m_toolPanel->handleMouseClickEvent(ray);
	RayIntersectionVisitor intersectionVisitor(ray);
	m_defaultGUIManager.m_sceneManager->accept( intersectionVisitor );
	if( intersectionVisitor.hasGotIntersection() ) {
		hpvec3 secPoint = intersectionVisitor.getFirstIntersection();
		//std::cout << "(" << secPoint.x << ", " << secPoint.y << ", " << secPoint.z << ")" << std::endl;
	}
	else {
		//std::cout << "No intersection." << std::endl;
	}
}


void DefaultGUIManager::DefaultViewportListener::DefaultViewportListener::handleDragEvent(Ray& ray){
	m_defaultGUIManager.m_toolPanel->handleDragEvent(ray);
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


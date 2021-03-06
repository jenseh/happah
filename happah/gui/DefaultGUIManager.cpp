#include "happah/gui/DefaultGUIManager.h"
#include <sstream>

vector<hpvec3>* to3D(vector<hpvec2>* vs2D) {
	vector<hpvec3>* vs3D = new vector<hpvec3>(vs2D->size());
	vector<hpvec3>::iterator i3D = vs3D->begin();
	for(vector<hpvec2>::iterator i2D = vs2D->begin(), end = vs2D->end(); i2D != end; ++i2D, ++i3D)
		(*i3D) = hpvec3(*i2D, 0.0f);
	return vs3D;
}

LineMesh3D* to3D(LineMesh2D* lineMesh2D) {
	vector<hpvec3>* verticesAndNormals = to3D(lineMesh2D->getVerticesAndNormals());
	vector<hpuint>* indices = new vector<hpuint>(*(lineMesh2D->getIndices()));
	return new LineMesh3D(verticesAndNormals, indices);
}

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
	TriangleMesh3D_ptr gearMesh = TriangleMesh3D_ptr(simpleGear->toTriangleMesh(100, 30));
	SurfaceOfRevolution_ptr disc = DiscGenerator::generateDiscFrom(*simpleGear);
	TriangleMesh3D_ptr discMesh = TriangleMesh3D_ptr(disc->toTriangleMesh());
	DiscGearGrind_ptr simulation = DiscGearGrind_ptr(new DiscGearGrind(disc, discMesh, simpleGear, gearMesh));

	QThread* thread = new QThread();
	DiscGearGrindWorkerListener* listener = new DiscGearGrindWorkerListener(this);
	DiscGearGrindWorker* discGearGrindWorker = new DiscGearGrindWorker(simulation, thread, listener);
	thread->start();
}

void DefaultGUIManager::createDiscGearGrind(SurfaceOfRevolution_ptr disc, SimpleGear_ptr simpleGear) {
	TriangleMesh3D_ptr gearMesh = TriangleMesh3D_ptr(simpleGear->toTriangleMesh());
	TriangleMesh3D_ptr discMesh = TriangleMesh3D_ptr(disc->toTriangleMesh());
	DiscGearGrind_ptr simulation = DiscGearGrind_ptr(new DiscGearGrind(disc, discMesh, simpleGear, gearMesh));

	QThread* thread = new QThread();
	DiscGearGrindWorkerListener* listener = new DiscGearGrindWorkerListener(this);
	DiscGearGrindWorker* discGearGrindWorker = new DiscGearGrindWorker(simulation, thread, listener);
	thread->start();
}

void DefaultGUIManager::createWormGearGrind(InvoluteGear_ptr involuteGear) {
	Worm_ptr worm = WormGenerator::generateWormFrom(involuteGear);
	createWormGearGrind(worm, involuteGear);
}

void DefaultGUIManager::createWormGearGrind(Worm_ptr worm, InvoluteGear_ptr involuteGear) {
	SimpleGear_ptr simpleGear = SimpleGear_ptr(involuteGear->toSimpleGear());

	TriangleMesh3D_ptr gearMesh = TriangleMesh3D_ptr(simpleGear->toTriangleMesh(150, 100));
	TriangleMesh3D_ptr wormMesh = worm->toTriangleMesh(30, 100);
	WormGearGrind_ptr simulation = WormGearGrind_ptr(new WormGearGrind(worm, wormMesh, simpleGear, involuteGear->getReferenceRadius(), gearMesh));

	QThread* thread = new QThread();
	WormGearGrindWorkerListener* listener = new WormGearGrindWorkerListener(this);
	WormGearGrindWorker* wormGearGrindWorker = new WormGearGrindWorker(simulation, thread, listener);
	thread->start();
}

template<class G, class S>
void DefaultGUIManager::doInsert2D(shared_ptr<G> geometry, shared_ptr<S> guiStateNode) {
	TriangleMesh3D_ptr triangleMesh = TriangleMesh3D_ptr(geometry->toTriangleMesh());
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
	LineMesh3D_ptr lineMesh = LineMesh3D_ptr(geometry->toLineMesh());
	hpcolor color(1.0, 0.0, 0.0, 1.0);
	guiStateNode->setLineMesh(lineMesh);
	m_sceneManager->insert(geometry, guiStateNode);
	LineMeshRenderStateNode_ptr lineMeshRenderStateNode = m_sceneManager->insert(geometry, lineMesh, color);
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
	guiStateNode->setPointCloud(pointCloud);
	m_sceneManager->insert(geometry,guiStateNode);
	PointCloudRenderStateNode_ptr pointCloudRenderStateNode = m_sceneManager->insert(geometry,pointCloud,color);
	pointCloudRenderStateNode->registerSelectListener(guiStateNode->getSelectListener());
}

template<class G, class S, class F>
void DefaultGUIManager::doInsert0D(shared_ptr<G> geometry, const char* label, F* form) {
	shared_ptr<S> guiStateNode = shared_ptr<S>(new S(geometry, form, toFinalLabel(label)));
	// TODO : guiStateNode->registerForm
	doInsert0D<G, S>(geometry, guiStateNode);
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
	TriangleMesh3D_ptr triangleMesh = TriangleMesh3D_ptr(geometry->toTriangleMesh());
	hpcolor color(1.0, 0.0, 0.0, 1.0);
	guiStateNode->setTriangleMesh(triangleMesh);
	TriangleMeshRenderStateNode_ptr triangleMeshRenderStateNode =m_sceneManager->insert(geometry, triangleMesh, color);
	triangleMeshRenderStateNode->registerSelectListener(guiStateNode->getSelectListener());
}

template<class G>
void DefaultGUIManager::doUpdate1D(shared_ptr<G> geometry, hpcolor color) {
	GUIStateNode_ptr guiStateNode = m_guiStateNodes[geometry];
	if(!guiStateNode) {
		cerr << "GUI state node not found." << endl;
		return;
	}
	m_sceneManager->removeContainingData(geometry, guiStateNode->getLineMesh());
	LineMesh3D_ptr lineMesh = LineMesh3D_ptr(geometry->toLineMesh());
	guiStateNode->setLineMesh(lineMesh);
	LineMeshRenderStateNode_ptr lineMeshRenderStateNode = m_sceneManager->insert(geometry, lineMesh, color);
	lineMeshRenderStateNode->registerSelectListener(guiStateNode->getSelectListener());

}

template<class G>
void DefaultGUIManager::doUpdate0D(shared_ptr<G> geometry, hpcolor color) {
	GUIStateNode_ptr guiStateNode = m_guiStateNodes[geometry];
	if(!guiStateNode) {
		cerr << "GUI state node not found." << endl;
		return;
	}
	m_sceneManager->removeContainingData(geometry, guiStateNode->getPointCloud());
	PointCloud_ptr pointCloud = PointCloud_ptr(geometry->toPointCloud());
	guiStateNode->setPointCloud(pointCloud);
	PointCloudRenderStateNode_ptr pointCloudRenderStateNode = m_sceneManager->insert(geometry, pointCloud, color);
	pointCloudRenderStateNode->registerSelectListener(guiStateNode->getSelectListener());
}


void DefaultGUIManager::generateDisc(CylindricalGear_ptr cylindricalGear) {
	SurfaceOfRevolution_ptr disc = DiscGenerator::generateDiscFrom(*cylindricalGear);
	insert(disc, HP_TRIANGLE_MESH);
}

void DefaultGUIManager::generateWorm(InvoluteGear_ptr involuteGear) {
	Worm_ptr worm = WormGenerator::generateWormFrom(involuteGear);
	insert(worm, HP_TRIANGLE_MESH);
}


Plane_ptr DefaultGUIManager::getParentPlane( BSplineCurve2D_ptr bSplineCurve ) {
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

void DefaultGUIManager::insert(BSplineCurve2D_ptr bSplineCurve, hpuint drawMode) {
	insert(bSplineCurve, "BSplineCurve", hpcolor(1.0, 0.0, 0.0, 1.0), drawMode);
	/*if( drawMode & HP_LINE_MESH ) {
		doInsert1D<BSplineCurve<hpvec2>, BSplineCurveGUIStateNode, BSplineCurveForm, BSplineCurveContextMenu>(
				bSplineCurve, "BSplineCurve", m_toolPanel->getBSplineCurveForm(), m_mainWindow.getBSplineCurveContextMenu());
	}

	if( drawMode & HP_POINT_CLOUD ) {
		doInsert0D<BSplineCurve<hpvec2>, BSplineCurveGUIStateNode, BSplineCurveForm, BSplineCurveContextMenu>(
				bSplineCurve, "BSplineCurve", m_toolPanel->getBSplineCurveForm(), m_mainWindow.getBSplineCurveContextMenu());
	}*/

}

void DefaultGUIManager::insert(BSplineCurve2D_ptr bSplineCurve, const char* label, hpcolor curveColor, hpuint drawMode) {
	if( drawMode & HP_LINE_MESH ) {
		shared_ptr<BSplineCurveGUIStateNode> guiStateNode = shared_ptr<BSplineCurveGUIStateNode>(
			new BSplineCurveGUIStateNode(bSplineCurve, m_toolPanel->getBSplineCurveForm(), m_mainWindow.getBSplineCurveContextMenu(), toFinalLabel(label)));
		LineMesh2D* lineMesh2D = bSplineCurve->toLineMesh();
		LineMesh3D_ptr lineMesh = LineMesh3D_ptr(to3D(lineMesh2D));
		guiStateNode->setLineMesh(lineMesh);
		m_sceneManager->insert(bSplineCurve, guiStateNode);
		LineMeshRenderStateNode_ptr lineMeshRenderStateNode = m_sceneManager->insert(bSplineCurve, lineMesh, curveColor);
		lineMeshRenderStateNode->registerSelectListener(guiStateNode->getSelectListener());
	}
	if( drawMode & HP_POINT_CLOUD ) {
		shared_ptr<BSplineCurveGUIStateNode> guiStateNode = shared_ptr<BSplineCurveGUIStateNode>(
			new BSplineCurveGUIStateNode(bSplineCurve, m_toolPanel->getBSplineCurveForm(), m_mainWindow.getBSplineCurveContextMenu(), toFinalLabel(label)));
		PointCloud_ptr pointCloud = PointCloud_ptr(bSplineCurve->toPointCloud());
		guiStateNode->setPointCloud(pointCloud);
		m_sceneManager->insert(bSplineCurve, guiStateNode);
		PointCloudRenderStateNode_ptr pointCloudRenderStateNode = m_sceneManager->insert(bSplineCurve, pointCloud, curveColor);
		pointCloudRenderStateNode->registerSelectListener(guiStateNode->getSelectListener());
	}
}

void DefaultGUIManager::insert(SurfaceOfRevolution_ptr disc,hpuint drawMode) {
	if (drawMode & HP_TRIANGLE_MESH)
		doInsert2D<SurfaceOfRevolution, DiscGUIStateNode, DiscForm, DiscContextMenu>(disc, "Disc",  m_toolPanel->getDiscForm(), m_mainWindow.getDiscContextMenu() );
}


void DefaultGUIManager::insert(DiscGearGrind_ptr discGearGrind) {
	DiscGearGrindGUIStateNode_ptr guiStateNode = DiscGearGrindGUIStateNode_ptr(new DiscGearGrindGUIStateNode(
				discGearGrind, m_toolPanel->getSimulationForm(), m_mainWindow.getSimulationContextMenu(), toFinalLabel("Disc gear grind simulation")));
	m_sceneManager->insert(discGearGrind, guiStateNode);
}

void DefaultGUIManager::insert(WormGearGrind_ptr wormGearGrind) {
	WormGearGrindGUIStateNode_ptr guiStateNode = WormGearGrindGUIStateNode_ptr(new WormGearGrindGUIStateNode(
				wormGearGrind, m_toolPanel->getSimulationForm(), m_mainWindow.getSimulationContextMenu(), toFinalLabel("Worm gear grind simulation")));
	m_sceneManager->insert(wormGearGrind, guiStateNode);
}

void DefaultGUIManager::insert(FocalSpline_ptr focalSpline, hpuint drawMode){
	if(drawMode & HP_TRIANGLE_MESH){
			// DO nothing .. we don't want triangles
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

void DefaultGUIManager::insert(Plane_ptr plane, BSplineCurve2D_ptr curve) {
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
		doInsert1D<ToothProfile, ToothProfileGUIStateNode, ToothProfileForm, ToothProfileContextMenu>(toothProfile, "Tooth Profile", m_toolPanel->getToothProfileForm(), m_mainWindow.getToothProfileContextMenu());
	}
	if(drawMode & HP_POINT_CLOUD) {
		doInsert0D<ToothProfile, ToothProfileGUIStateNode, ToothProfileForm, ToothProfileContextMenu>(toothProfile, "Tooth Profile", m_toolPanel->getToothProfileForm(), m_mainWindow.getToothProfileContextMenu());
	}
}

void DefaultGUIManager::insert(ToothProfile_ptr toothProfile, const char* label, hpcolor curveColor, hpuint drawMode) {
	if( drawMode & HP_LINE_MESH ) {
		shared_ptr<ToothProfileGUIStateNode> guiStateNode = shared_ptr<ToothProfileGUIStateNode>(
			new ToothProfileGUIStateNode(toothProfile, m_toolPanel->getToothProfileForm(), m_mainWindow.getToothProfileContextMenu(), toFinalLabel(label)));
		// LineMesh2D* lineMesh2D = toothProfile->toLineMesh();
		LineMesh3D_ptr lineMesh = LineMesh3D_ptr(toothProfile->toLineMesh());
		guiStateNode->setLineMesh(lineMesh);
		m_sceneManager->insert(toothProfile, guiStateNode);
		LineMeshRenderStateNode_ptr lineMeshRenderStateNode = m_sceneManager->insert(toothProfile, lineMesh, curveColor);
		lineMeshRenderStateNode->registerSelectListener(guiStateNode->getSelectListener());
	}
	if( drawMode & HP_POINT_CLOUD ) {
		shared_ptr<ToothProfileGUIStateNode> guiStateNode = shared_ptr<ToothProfileGUIStateNode>(
			new ToothProfileGUIStateNode(toothProfile, m_toolPanel->getToothProfileForm(), m_mainWindow.getToothProfileContextMenu(), toFinalLabel(label)));
		PointCloud_ptr pointCloud = PointCloud_ptr(toothProfile->toPointCloud());
		guiStateNode->setPointCloud(pointCloud);
		m_sceneManager->insert(toothProfile, guiStateNode);
		PointCloudRenderStateNode_ptr pointCloudRenderStateNode = m_sceneManager->insert(toothProfile, pointCloud, curveColor);
		pointCloudRenderStateNode->registerSelectListener(guiStateNode->getSelectListener());
	}
}

void DefaultGUIManager::insert(TriangleMesh3D_ptr triangleMesh) {
	TriangleMeshGUIStateNode_ptr triangleMeshGUIStateNode = TriangleMeshGUIStateNode_ptr(new TriangleMeshGUIStateNode(triangleMesh, m_mainWindow.getTriangleMeshContextMenu(), toFinalLabel("Triangle Mesh")));
	hpcolor color(1.0, 0.0, 0.0, 1.0);
	TriangleMeshRenderStateNode_ptr triangleMeshRenderStateNode = m_sceneManager->insert(triangleMesh, color);
	triangleMeshGUIStateNode->setTriangleMesh(triangleMesh);
	m_sceneManager->insert(triangleMesh, triangleMeshGUIStateNode);
}

void DefaultGUIManager::insert(Worm_ptr worm, hpuint drawMode) {
	if (drawMode & HP_TRIANGLE_MESH)
		doInsert2D<Worm, WormGUIStateNode, WormForm>(worm, "Worm", m_toolPanel->getWormForm());
}

string DefaultGUIManager::toFinalLabel(const char* label) {
	ostringstream oss;
	oss << label << " " << m_counter++;
	return oss.str();
}

void DefaultGUIManager::update(BSplineCurve2D_ptr bSplineCurve) {
	update(bSplineCurve, hpcolor(1.0, 0.0, 0.0, 1.0));
}

void DefaultGUIManager::update(BSplineCurve2D_ptr bSplineCurve, hpcolor color) {
	doUpdate0D<BSplineCurve<hpvec2>>(bSplineCurve);
	GUIStateNode_ptr guiStateNode = m_guiStateNodes[bSplineCurve];
	if(!guiStateNode) {
		cerr << "GUI state node not found." << endl;
		return;
	}
	m_sceneManager->removeContainingData(bSplineCurve, guiStateNode->getLineMesh());
	LineMesh2D* lineMesh2D = bSplineCurve->toLineMesh();
	LineMesh3D_ptr lineMesh = LineMesh3D_ptr(to3D(lineMesh2D));
	guiStateNode->setLineMesh(lineMesh);
	LineMeshRenderStateNode_ptr lineMeshRenderStateNode = m_sceneManager->insert(bSplineCurve, lineMesh, color);
	lineMeshRenderStateNode->registerSelectListener(guiStateNode->getSelectListener());
}

void DefaultGUIManager::update(SurfaceOfRevolution_ptr disc) {
	doUpdate2D<SurfaceOfRevolution>(disc);
}

void DefaultGUIManager::update(FocalSpline_ptr focalSpline){
	doUpdate0D<FocalSpline>(focalSpline);
	doUpdate1D<FocalSpline>(focalSpline);


}

void DefaultGUIManager::update(InvoluteGear_ptr involuteGear) {
	doUpdate2D<InvoluteGear>(involuteGear);
}

void DefaultGUIManager::update(Plane_ptr plane) {
	doUpdate2D<Plane>(plane);
	m_sceneManager->update(plane);
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
	m_toolPanel->setForm(m_toolPanel->getBSplineCurveForm());
}

//TODO: This should be removed since it is discriminating other simulations that dont have a disc..
//void DefaultGUIManager::useInSimulation(SurfaceOfRevolution_ptr disc, TriangleMesh3D_ptr discMesh) {
//	m_toolPanel->getSimulationForm()->setDisc(disc, discMesh);
//}
//
//void DefaultGUIManager::useInSimulation(SimpleGear_ptr gear, TriangleMesh3D_ptr gearMesh){
//	m_toolPanel->getSimulationForm()->setGear(gear, gearMesh);
//}

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

void DefaultGUIManager::DefaultSceneGraphExplorerListener::createWormGearGrind(Worm_ptr worm, InvoluteGear_ptr involuteGear) {
	m_defaultGUIManager.createWormGearGrind(worm, involuteGear);
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
//		hpvec3 secPoint = intersectionVisitor.getFirstIntersection();
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


#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <list>
#include <vector>

using namespace std;

//class SceneManager;

#include "happah/geometries/gears/InvoluteGear.h"
#include "happah/geometries/gears/SimpleGear.h"
#include "happah/geometries/gears/ToothProfile.h"
#include "happah/geometries/gears/Worm.h"
#include "happah/geometries/Plane.h"
#include "happah/geometries/SpherePatch.h"
#include "happah/geometries/SurfaceOfRevolution.h"
#include "happah/scene/DiscGearGrindNode.h"
#include "happah/scene/GUIStateNode.h"
#include "happah/scene/SceneListener.h"
#include "happah/scene/PointCloudNode.h"
#include "happah/scene/WormGearGrindNode.h"
#include "happah/simulations/DiscGearGrind.h"
#include "happah/geometries/FocalSpline.h"


class SceneManager : public Node {
public:
	SceneManager();
	~SceneManager();

	template <class T> void insert(shared_ptr<BSplineCurve<T>> curve, BSplineCurveGUIStateNode_ptr guiStateNode);
	template <class T> LineMeshRenderStateNode_ptr insert(shared_ptr<BSplineCurve<T>> curve, LineMesh_ptr LineMesh, hpcolor&color);
	template <class T> PointCloudRenderStateNode_ptr insert(shared_ptr<BSplineCurve<T>> curve, PointCloud_ptr pointCloud, hpcolor& color);
	void insert(FocalSpline_ptr focalSpline, FocalSplineGUIStateNode_ptr guiStateNode);
	PointCloudRenderStateNode_ptr insert(FocalSpline_ptr focalSpline, PointCloud_ptr pointCloud, hpcolor&color);
	LineMeshRenderStateNode_ptr insert(FocalSpline_ptr focalSpline, LineMesh_ptr LineMesh, hpcolor&color);
	void insert(SurfaceOfRevolution_ptr disc, DiscGUIStateNode_ptr discGUIStateNode);
	TriangleMeshRenderStateNode_ptr insert(SurfaceOfRevolution_ptr disc, TriangleMesh3D_ptr triangleMesh, hpcolor& color);
	TriangleMeshRenderStateNode_ptr insert(SurfaceOfRevolution_ptr geometry, TriangleMesh3D_ptr triangleMesh, hpcolor& color, RigidAffineTransformation& transformation);
	void insert(DiscGearGrind_ptr discGearGrind, DiscGearGrindGUIStateNode_ptr discGearGrindGUIStateNode);
	void insert(WormGearGrind_ptr wormGearGrind, WormGearGrindGUIStateNode_ptr wormGearGrindGUIStateNode);
	void insert(InvoluteGear_ptr involuteGear, InvoluteGearGUIStateNode_ptr involuteGearGUIStateNode);
	TriangleMeshRenderStateNode_ptr insert(InvoluteGear_ptr involuteGear, TriangleMesh3D_ptr triangleMesh, hpcolor& color);
	void insert(Plane_ptr plane);
	void insert(Plane_ptr plane, PlaneGUIStateNode_ptr planeGUIStateNode);
	TriangleMeshRenderStateNode_ptr insert(Plane_ptr plane, TriangleMesh3D_ptr triangleMesh, hpcolor& color);
	PointCloudRenderStateNode_ptr insert(Plane_ptr plane, PointCloud_ptr pointCloud, hpcolor& color);
	LineMeshRenderStateNode_ptr insert(Plane_ptr plane, LineMesh_ptr LineMesh,hpcolor&color);
	template <class T> void insert(Plane_ptr plane, shared_ptr<BSplineCurve<T>> curve);
	LineMeshRenderStateNode_ptr insert(SimpleGear_ptr simpleGear, LineMesh_ptr lineMesh, hpcolor& color);
	TriangleMeshRenderStateNode_ptr insert(SimpleGear_ptr gear, TriangleMesh3D_ptr triangleMesh, vector<hpcolor>* color, RigidAffineTransformation& transformation);
	void insert(SimpleGear_ptr simpleGear, SimpleGearGUIStateNode_ptr simpleGearGUIStateNode);
	TriangleMeshRenderStateNode_ptr insert(SimpleGear_ptr simpleGear, TriangleMesh3D_ptr triangleMesh, hpcolor& color);
	void insert(SpherePatch_ptr spherePatch, SpherePatchGUIStateNode_ptr spherePatchGUIStateNode);
	TriangleMeshRenderStateNode_ptr insert(SpherePatch_ptr spherePatch, TriangleMesh3D_ptr triangleMesh, hpcolor& color);
	void insert(ToothProfile_ptr toothProfile, ToothProfileGUIStateNode_ptr toothProfileGuiStateNode);
	LineMeshRenderStateNode_ptr insert(ToothProfile_ptr toothProfile, LineMesh_ptr lineMesh, hpcolor& color);
	PointCloudRenderStateNode_ptr insert(ToothProfile_ptr toothProfile, PointCloud_ptr pointCloud, hpcolor& color);
	void insert(TriangleMesh3D_ptr triangleMesh, TriangleMeshGUIStateNode_ptr triangleMeshGUIStateNode);
	TriangleMeshRenderStateNode_ptr insert(TriangleMesh3D_ptr triangleMesh, hpcolor& color);
	TriangleMeshRenderStateNode_ptr insert(Worm_ptr worm, TriangleMesh3D_ptr triangleMesh, hpcolor& color);
	void insert(Worm_ptr worm, WormGUIStateNode_ptr wormGUIStateNode);
	void registerSceneListener(SceneListener* sceneListener);
	Node_ptr remove(Node_ptr node);
	void remove(vector<Node_ptr>& nodes);
	void remove(vector<Node_ptr>& nodes, vector<Node_ptr>& removedNodes);
	Node_ptr removeChildContainingData(shared_ptr<void> data);
	Node_ptr removeContainingData(shared_ptr<void> parentData, shared_ptr<void> childData);
	void unregisterSceneListener(SceneListener* sceneListener);
	void update(Plane_ptr plane);

private:
	list<SceneListener*> m_listeners;

	template<class G, class N>
	void doInsert(shared_ptr<G> geometry);
	template<class G1, class N1, class G2, class N2>
	void doInsert(shared_ptr<G1> geometry1, shared_ptr<G2> geometry2);
	template<class G, class N, class S> 
	void doInsert(shared_ptr<G> data, shared_ptr<S> guiStateNode);
	template<class G, class N>
	TriangleMeshRenderStateNode_ptr doInsert(shared_ptr<G> geometry, TriangleMesh3D_ptr triangleMesh, hpcolor& color);
	template<class G, class N>
	TriangleMeshRenderStateNode_ptr doInsert(shared_ptr<G> geometry, TriangleMesh3D_ptr triangleMesh, vector<hpcolor>* color, RigidAffineTransformation& transformation);
	template<class G, class N>
	TriangleMeshRenderStateNode_ptr doInsert(shared_ptr<G> geometry, TriangleMesh3D_ptr triangleMesh, hpcolor& color, RigidAffineTransformation& transformation);
	template<class G, class N>
	PointCloudRenderStateNode_ptr doInsert(shared_ptr<G> geometry, PointCloud_ptr pointCloud, hpcolor& color, RigidAffineTransformation& transformation);
	template<class G, class N>
	PointCloudRenderStateNode_ptr doInsert(shared_ptr<G> geometry, PointCloud_ptr pointCloud, hpcolor& color);
	template<class G, class N>
	LineMeshRenderStateNode_ptr doInsert(shared_ptr<G> geometry, LineMesh_ptr lineMesh, hpcolor& color);
	template<class G, class N>
	LineMeshRenderStateNode_ptr doInsert(shared_ptr<G> geometry, LineMesh_ptr lineMesh, vector<hpcolor>* color, RigidAffineTransformation& transformation);
	template<class G, class N>
	LineMeshRenderStateNode_ptr doInsert(shared_ptr<G> geometry, LineMesh_ptr lineMesh, hpcolor& color, RigidAffineTransformation& transformation);
	template<class S, class N, class G>
	void doInsertSimulation(shared_ptr<S> simulation, shared_ptr<G> guiStateNode);


	void triggerSubtreeInsertedEvent(Node_ptr root);
	void triggerSubtreesInsertedEvent(vector<Node_ptr>& roots);
	void triggerSubtreeRemovedEvent(Node_ptr root);
	void triggerSubtreesRemovedEvent(vector<Node_ptr>& roots);
	void triggerSubtreeUpdatedEvent(Node_ptr root);
	void triggerSubtreesUpdatedEvent(vector<Node_ptr>& roots);

};
typedef shared_ptr<SceneManager> SceneManager_ptr;

#endif // SCENEMANAGER_H

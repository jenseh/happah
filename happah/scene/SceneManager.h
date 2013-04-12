#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <list>
#include <vector>

using namespace std;

//class SceneManager;

#include "happah/geometries/gears/InvoluteGear.h"
#include "happah/geometries/gears/SimpleGear.h"
#include "happah/geometries/Plane.h"
#include "happah/geometries/SpherePatch.h"
#include "happah/geometries/SurfaceOfRevolution.h"
#include "happah/geometries/gears/Worm.h"
#include "happah/scene/DiscGearGrindNode.h"
#include "happah/scene/GUIStateNode.h"
#include "happah/scene/SceneListener.h"
#include "happah/scene/PointCloudNode.h"
#include "happah/simulations/DiscGearGrind.h"
#include "happah/geometries/FocalSpline.h"


class SceneManager : public Node {
public:
	SceneManager();
	~SceneManager();

	void insert(BSplineCurve_ptr curve, BSplineCurveGUIStateNode_ptr guiStateNode);
	void insert(BSplineCurve_ptr curve, LineMesh_ptr LineMesh, hpcolor&color);
	void insert(BSplineCurve_ptr curve, PointCloud_ptr pointCloud, hpcolor& color);
	void insert(FocalSpline_ptr focalSpline, FocalSplineGUIStateNode_ptr guiStateNode);
	void insert(FocalSpline_ptr focalSpline, PointCloud_ptr pointCloud, hpcolor&color);
	void insert(FocalSpline_ptr focalSpline, LineMesh_ptr LineMesh, hpcolor&color);
	void insert(SurfaceOfRevolution_ptr disc, DiscGUIStateNode_ptr discGUIStateNode);
	void insert(SurfaceOfRevolution_ptr disc, TriangleMesh_ptr triangleMesh, hpcolor& color);
	void insert(SurfaceOfRevolution_ptr geometry, TriangleMesh_ptr triangleMesh, hpcolor& color, RigidAffineTransformation& transformation);
	void insert(DiscGearGrind_ptr, DiscGearGrindGUIStateNode_ptr discGearGrindGUIStateNode);
	void insert(InvoluteGear_ptr involuteGear, InvoluteGearGUIStateNode_ptr involuteGearGUIStateNode);
	void insert(InvoluteGear_ptr involuteGear, TriangleMesh_ptr triangleMesh, hpcolor& color);
	void insert(Plane_ptr plane);
	void insert(Plane_ptr plane, PlaneGUIStateNode_ptr planeGUIStateNode);
	void insert(Plane_ptr plane, TriangleMesh_ptr triangleMesh, hpcolor& color);
	void insert(Plane_ptr plane, PointCloud_ptr pointCloud, hpcolor& color);
	void insert(Plane_ptr plane, LineMesh_ptr LineMesh,hpcolor&color);
	void insert(Plane_ptr plane, BSplineCurve_ptr curve);
//void insert(Plane_ptr plane, BSplineCurve<hpvec2> splineCurve, LineMesh_ptr<hpvec2> lineMesh_ptr, hpcolor& color);
	void insert(SimpleGear_ptr simpleGear, LineMesh_ptr lineMesh, hpcolor& color);
	void insert(SimpleGear_ptr gear, TriangleMesh_ptr triangleMesh, vector<hpcolor>* color, RigidAffineTransformation& transformation);
	void insert(SimpleGear_ptr simpleGear, SimpleGearGUIStateNode_ptr simpleGearGUIStateNode);
	void insert(SimpleGear_ptr simpleGear, TriangleMesh_ptr triangleMesh, hpcolor& color);
	void insert(SpherePatch_ptr spherePatch, SpherePatchGUIStateNode_ptr spherePatchGUIStateNode);
	void insert(SpherePatch_ptr spherePatch, TriangleMesh_ptr triangleMesh, hpcolor& color);
	void insert(Worm_ptr worm, TriangleMesh_ptr triangleMesh, hpcolor& color);
	void insert(Worm_ptr worm, WormGUIStateNode_ptr wormGUIStateNode);
	void registerSceneListener(SceneListener* sceneListener);
	Node_ptr remove(Node_ptr node);
	void remove(vector<Node_ptr>& nodes);
	void remove(vector<Node_ptr>& nodes, vector<Node_ptr>& removedNodes);
	Node_ptr removeChildContainingData(shared_ptr<void> data);
	Node_ptr removeContainingData(shared_ptr<void> parentData, shared_ptr<void> childData);
	void unregisterSceneListener(SceneListener* sceneListener);

private:
	list<SceneListener*> m_listeners;

	template<class G, class N>
	void doInsert(shared_ptr<G> geometry);
	template<class G1, class N1, class G2, class N2>
	void doInsert(shared_ptr<G1> geometry1, shared_ptr<G2> geometry2);
	template<class G, class N, class S> 
	void doInsert(shared_ptr<G> data, shared_ptr<S> guiStateNode);
	template<class G, class N>
	void doInsert(shared_ptr<G> geometry, TriangleMesh_ptr triangleMesh, hpcolor& color);
	template<class G, class N>
	void doInsert(shared_ptr<G> geometry, TriangleMesh_ptr triangleMesh, vector<hpcolor>* color, RigidAffineTransformation& transformation);
	template<class G, class N>
	void doInsert(shared_ptr<G> geometry, TriangleMesh_ptr triangleMesh, hpcolor& color, RigidAffineTransformation& transformation);
	template<class G, class N>
	void doInsert(shared_ptr<G> geometry, PointCloud_ptr pointCloud, hpcolor& color, RigidAffineTransformation& transformation);
	template<class G, class N>
	void doInsert(shared_ptr<G> geometry, PointCloud_ptr pointCloud, hpcolor& color);
	template<class G, class N>
	void doInsert(shared_ptr<G> geometry, LineMesh_ptr lineMesh, hpcolor& color);
	template<class G, class N>
	void doInsert(shared_ptr<G> geometry, LineMesh_ptr lineMesh, vector<hpcolor>* color, RigidAffineTransformation& transformation);
	template<class G, class N>
	void doInsert(shared_ptr<G> geometry, LineMesh_ptr lineMesh, hpcolor& color, RigidAffineTransformation& transformation);
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

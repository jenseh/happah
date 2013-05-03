#include <ctime>
#include <iostream>

#include "happah/scene/BSplineCurveNode.h"
#include "happah/scene/FocalSplineNode.h"
#include "happah/scene/InvoluteGearNode.h"
#include "happah/scene/LineMeshNode.h"
#include "happah/scene/PlaneNode.h"
#include "happah/scene/PointCloudNode.h"
#include "happah/scene/SceneManager.h"
#include "happah/scene/TriangleMeshNode.h"
#include "happah/scene/RenderStateNode.h"
#include "happah/scene/SimpleGearNode.h"
#include "happah/scene/DiscNode.h"
#include "happah/scene/ToothProfileNode.h"
#include "happah/scene/WormNode.h"
#include "happah/scene/SpherePatchNode.h"

SceneManager::SceneManager() {}

SceneManager::~SceneManager() {}

template<class G, class N>
void SceneManager::doInsert(shared_ptr<G> geometry) {
	Node_ptr node = findContainingData(geometry);
	if(!node){
		shared_ptr<N> geometryNode = shared_ptr<N>(new N(geometry));
		insertChild( geometryNode );
	}
}

/**
  * Inserts a second geometry beneath a given geometry.
  * @param geometry1 Parent geometry. If not existent, it will be inserted as child of root.
  * @param geometry2 Geometry to be inserted beneath geometry1. If it already exists,
    function call will change nothing in scene.
  */
template<class G1, class N1, class G2, class N2>
void SceneManager::doInsert(shared_ptr<G1> geometry1, shared_ptr<G2> geometry2) {
	Node_ptr node = findContainingData(geometry2);
	// If geometry2 is already in scene, don't change anything. Otherwise proceed
	if(!node){
		Node_ptr parentNode = findContainingData(geometry1);
		shared_ptr<N1> parentGeometryNode;
		if(!parentNode) {
			// create parent geometry, if it's not in the scene
			parentGeometryNode = shared_ptr<N1>(new N1(geometry1));
			insertChild( parentGeometryNode );
		}
		else {
			parentGeometryNode = static_pointer_cast<N1>(parentNode);
		}

		// create geometry2 node and insert beneath geometry1 node
		shared_ptr<N2> childGeometryNode = shared_ptr<N2>(new N2(geometry2));
		parentGeometryNode->insertChild( childGeometryNode );
	}
}

template<class G, class N, class S>
void SceneManager::doInsert(shared_ptr<G> data, shared_ptr<S> guiStateNode) {
	Node_ptr node = findContainingData(data);

	Node_ptr root = guiStateNode;
	shared_ptr<N> dataNode;
	if(node) {
		dataNode = static_pointer_cast<N>(node);
		if(dataNode->hasChild(guiStateNode)) {
			triggerSubtreeUpdatedEvent(guiStateNode);
			return;
		}
	} else {
		dataNode = shared_ptr<N>(new N(data));
		insertChild(dataNode);
		root = dataNode;
	}

	dataNode->insertChild(guiStateNode);

	triggerSubtreeInsertedEvent(root);
}

template<class G, class N>
TriangleMeshRenderStateNode_ptr SceneManager::doInsert(shared_ptr<G> geometry, TriangleMesh3D_ptr triangleMesh, hpcolor& color) {
	Node_ptr node = findContainingData(geometry);
	Node_ptr root;
	shared_ptr<N> geometryNode;
	if(node) {
		geometryNode = static_pointer_cast<N>(node);
		node = node->findChildContainingData(triangleMesh);
		if(node) {
			TriangleMeshNode_ptr triangleMeshNode = dynamic_pointer_cast<TriangleMeshNode>(node);
			TriangleMeshRenderStateNode_ptr triangleMeshRenderStateNode = triangleMeshNode->getTriangleMeshRenderStateNode();
			triangleMeshRenderStateNode->setColor(color);
			triggerSubtreeUpdatedEvent(triangleMeshRenderStateNode);
			return triangleMeshRenderStateNode;
		}
	} else {
		geometryNode = shared_ptr<N>(new N(geometry));
		insertChild(geometryNode);
		root = geometryNode;
	}

	TriangleMeshNode_ptr triangleMeshNode(new TriangleMeshNode(triangleMesh));
	geometryNode->insertChild(triangleMeshNode);

	if(!root) root = triangleMeshNode;

	TriangleMeshRenderStateNode_ptr triangleMeshRenderStateNode(new TriangleMeshRenderStateNode(triangleMesh, color));
	triangleMeshNode->insertChild(triangleMeshRenderStateNode);
	triangleMeshRenderStateNode->registerSelectListener(geometryNode->getSelectListener());
	triggerSubtreeInsertedEvent(root);
	return triangleMeshRenderStateNode;
}

template<class G, class N>
TriangleMeshRenderStateNode_ptr SceneManager::doInsert(shared_ptr<G> geometry, TriangleMesh3D_ptr triangleMesh, vector<hpcolor>* color, RigidAffineTransformation& transformation) {
	Node_ptr node = findContainingData(geometry);

		Node_ptr root;
		shared_ptr<N> geometryNode;
		if(node) {
			geometryNode = static_pointer_cast<N>(node);
			node = node->findChildContainingData(triangleMesh);
			if(node) {
				TriangleMeshNode_ptr triangleMeshNode = dynamic_pointer_cast<TriangleMeshNode>(node);
				TriangleMeshRenderStateNode_ptr triangleMeshRenderStateNode = triangleMeshNode->getTriangleMeshRenderStateNode();
				triangleMeshRenderStateNode->setColorVector(color);
				triggerSubtreeUpdatedEvent(triangleMeshRenderStateNode);
				return triangleMeshRenderStateNode;
			}
		} else {
			geometryNode = shared_ptr<N>(new N(geometry));
			insertChild(geometryNode);
			root = geometryNode;
		}

		TriangleMeshNode_ptr triangleMeshNode(new TriangleMeshNode(triangleMesh, transformation));
		geometryNode->insertChild(triangleMeshNode);

		if(!root) root = triangleMeshNode;

		TriangleMeshRenderStateNode_ptr triangleMeshRenderStateNode(new TriangleMeshRenderStateNode(triangleMesh, color));
		triangleMeshNode->insertChild(triangleMeshRenderStateNode);
		triangleMeshRenderStateNode->registerSelectListener(geometryNode->getSelectListener());
		triggerSubtreeInsertedEvent(root);
		return triangleMeshRenderStateNode;
}

template<class G, class N>
TriangleMeshRenderStateNode_ptr SceneManager::doInsert(shared_ptr<G> geometry, TriangleMesh3D_ptr triangleMesh, hpcolor& color, RigidAffineTransformation& transformation) {
	Node_ptr node = findContainingData(geometry);

	Node_ptr root;
	shared_ptr<N> geometryNode;
	if(node) {
		geometryNode = static_pointer_cast<N>(node);
		node = node->findChildContainingData(triangleMesh);
		if(node) {
			TriangleMeshNode_ptr triangleMeshNode = dynamic_pointer_cast<TriangleMeshNode>(node);
			TriangleMeshRenderStateNode_ptr triangleMeshRenderStateNode = triangleMeshNode->getTriangleMeshRenderStateNode();
			triangleMeshRenderStateNode->setColor(color);
			triggerSubtreeUpdatedEvent(triangleMeshRenderStateNode);
			return triangleMeshRenderStateNode;
		}
	} else {
		geometryNode = shared_ptr<N>(new N(geometry));
		insertChild(geometryNode);
		root = geometryNode;
	}

	TriangleMeshNode_ptr triangleMeshNode(new TriangleMeshNode(triangleMesh, transformation));
	geometryNode->insertChild(triangleMeshNode);

	if(!root) root = triangleMeshNode;

	TriangleMeshRenderStateNode_ptr triangleMeshRenderStateNode(new TriangleMeshRenderStateNode(triangleMesh, color));
	triangleMeshNode->insertChild(triangleMeshRenderStateNode);
	triangleMeshRenderStateNode->registerSelectListener(geometryNode->getSelectListener());
	triggerSubtreeInsertedEvent(root);
	return triangleMeshRenderStateNode;
}
template<class G, class N>
LineMeshRenderStateNode_ptr SceneManager::doInsert(shared_ptr<G> geometry, LineMesh_ptr lineMesh, hpcolor& color) {
	Node_ptr node = findContainingData(geometry);

	Node_ptr root;
	shared_ptr<N> geometryNode;
	if(node) {
		geometryNode = static_pointer_cast<N>(node);
		node = node->findChildContainingData(lineMesh);
		if(node) {
			LineMeshNode_ptr lineMeshNode = dynamic_pointer_cast<LineMeshNode>(node);
			LineMeshRenderStateNode_ptr lineMeshRenderStateNode = lineMeshNode->getLineMeshRenderStateNode();
			lineMeshRenderStateNode->setColor(color);
			triggerSubtreeUpdatedEvent(lineMeshRenderStateNode);
			return lineMeshRenderStateNode;
		}
	} else {
		geometryNode = shared_ptr<N>(new N(geometry));
		insertChild(geometryNode);
		root = geometryNode;
	}

	LineMeshNode_ptr lineMeshNode(new LineMeshNode(lineMesh));
	geometryNode->insertChild(lineMeshNode);

	if(!root) root = lineMeshNode;

	LineMeshRenderStateNode_ptr lineMeshRenderStateNode(new LineMeshRenderStateNode(lineMesh, color));
	lineMeshNode->insertChild(lineMeshRenderStateNode);
	lineMeshRenderStateNode->registerSelectListener(geometryNode->getSelectListener());
	triggerSubtreeInsertedEvent(root);
	return lineMeshRenderStateNode;
}

template<class G, class N>
LineMeshRenderStateNode_ptr SceneManager::doInsert(shared_ptr<G> geometry, LineMesh_ptr lineMesh, vector<hpcolor>* color, RigidAffineTransformation& transformation) {
	Node_ptr node = findContainingData(geometry);

		Node_ptr root;
		shared_ptr<N> geometryNode;
		if(node) {
			geometryNode = static_pointer_cast<N>(node);
			node = node->findChildContainingData(lineMesh);
			if(node) {
				LineMeshNode_ptr lineMeshNode = dynamic_pointer_cast<LineMeshNode>(node);
				LineMeshRenderStateNode_ptr lineMeshRenderStateNode = lineMeshNode->getLineMeshRenderStateNode();
				lineMeshRenderStateNode->setColorVector(color);
				triggerSubtreeUpdatedEvent(lineMeshRenderStateNode);
				return lineMeshRenderStateNode;
			}
		} else {
			geometryNode = shared_ptr<N>(new N(geometry));
			insertChild(geometryNode);
			root = geometryNode;
		}

		LineMeshNode_ptr lineMeshNode(new LineMeshNode(lineMesh, transformation));
		geometryNode->insertChild(lineMeshNode);

		if(!root) root = lineMeshNode;

		LineMeshRenderStateNode_ptr lineMeshRenderStateNode(new LineMeshRenderStateNode(lineMesh, color));
		lineMeshNode->insertChild(lineMeshRenderStateNode);
		lineMeshRenderStateNode->registerSelectListener(geometryNode->getSelectListener());
		triggerSubtreeInsertedEvent(root);
		return lineMeshRenderStateNode;
}

template<class G, class N>
LineMeshRenderStateNode_ptr SceneManager::doInsert(shared_ptr<G> geometry, LineMesh_ptr lineMesh, hpcolor& color, RigidAffineTransformation& transformation) {
	Node_ptr node = findContainingData(geometry);

	Node_ptr root;
	shared_ptr<N> geometryNode;
	if(node) {
		geometryNode = static_pointer_cast<N>(node);
		node = node->findChildContainingData(lineMesh);
		if(node) {
			LineMeshNode_ptr lineMeshNode = dynamic_pointer_cast<LineMeshNode>(node);
			LineMeshRenderStateNode_ptr lineMeshRenderStateNode = lineMeshNode->getLineMeshRenderStateNode();
			lineMeshRenderStateNode->setColor(color);
			triggerSubtreeUpdatedEvent(lineMeshRenderStateNode);
			return lineMeshRenderStateNode;
		}
	} else {
		geometryNode = shared_ptr<N>(new N(geometry));
		insertChild(geometryNode);
		root = geometryNode;
	}

	LineMeshNode_ptr lineMeshNode(new LineMeshNode(lineMesh, transformation));
	geometryNode->insertChild(lineMeshNode);

	if(!root) root = lineMeshNode;

	LineMeshRenderStateNode_ptr lineMeshRenderStateNode(new LineMeshRenderStateNode(lineMesh, color));
	lineMeshNode->insertChild(lineMeshRenderStateNode);
	lineMeshRenderStateNode->registerSelectListener(geometryNode->getSelectListener());
	triggerSubtreeInsertedEvent(root);
	return lineMeshRenderStateNode;
}


template<class G, class N>
PointCloudRenderStateNode_ptr SceneManager::doInsert(shared_ptr<G> geometry, PointCloud_ptr pointCloud, hpcolor& color, RigidAffineTransformation& transformation){
	Node_ptr node = findContainingData(geometry);

	Node_ptr root;
	shared_ptr<N> geometryNode;
	if(node){
		geometryNode = static_pointer_cast<N>(node);
		node = node->findChildContainingData(pointCloud);
		if(node) {
			PointCloudNode_ptr pointCloudNode = dynamic_pointer_cast<PointCloudNode>(node);
			PointCloudRenderStateNode_ptr pointCloudRenderStateNode = pointCloudNode->getPointCloudRenderStateNode();
			pointCloudRenderStateNode->setColor(color);
			triggerSubtreeUpdatedEvent(pointCloudRenderStateNode);
			return pointCloudRenderStateNode;
		}
	}else {
		geometryNode = shared_ptr<N>(new N(geometry));
		insertChild(geometryNode);
		root = geometryNode;
	}

	PointCloudNode_ptr pointCloudNode(new PointCloudNode(pointCloud , transformation));
	geometryNode->insertChild(pointCloudNode);

	if(!root) root = pointCloudNode;

	PointCloudRenderStateNode_ptr pointCloudRenderStateNode(new PointCloudRenderStateNode(pointCloud,color));
	pointCloudNode->insertChild(pointCloudRenderStateNode);
	pointCloudRenderStateNode->registerSelectListener(geometryNode->getSelectListener());
	triggerSubtreeInsertedEvent(root);
	return pointCloudRenderStateNode;
}

template<class G, class N>

PointCloudRenderStateNode_ptr SceneManager::doInsert(shared_ptr<G> geometry, PointCloud_ptr pointCloud, hpcolor& color){
	Node_ptr node = findContainingData(geometry);

	Node_ptr root;
	shared_ptr<N> geometryNode;
	if(node){
		geometryNode = static_pointer_cast<N>(node);
		node = node->findChildContainingData(pointCloud);
		if(node) {
			PointCloudNode_ptr pointCloudNode = dynamic_pointer_cast<PointCloudNode>(node);
			PointCloudRenderStateNode_ptr pointCloudRenderStateNode = pointCloudNode->getPointCloudRenderStateNode();
			pointCloudRenderStateNode->setColor(color);
			triggerSubtreeUpdatedEvent(pointCloudRenderStateNode);
			return pointCloudRenderStateNode;
		}
	}else {
		geometryNode = shared_ptr<N>(new N(geometry));
		insertChild(geometryNode);
		root = geometryNode;
	}

	PointCloudNode_ptr pointCloudNode(new PointCloudNode(pointCloud));
	geometryNode->insertChild(pointCloudNode);

	if(!root) root = pointCloudNode;

	PointCloudRenderStateNode_ptr pointCloudRenderStateNode(new PointCloudRenderStateNode(pointCloud,color));
	pointCloudNode->insertChild(pointCloudRenderStateNode);
	pointCloudRenderStateNode->registerSelectListener(geometryNode->getSelectListener());
	triggerSubtreeInsertedEvent(root);
	return pointCloudRenderStateNode;
}
template<class S, class N, class G>
void SceneManager::doInsertSimulation(shared_ptr<S> simulation, shared_ptr<G> guiStateNode) {
	shared_ptr<N> simulationNode = shared_ptr<N>(new N(simulation));
	insertChild(simulationNode);
	simulationNode->buildSubtree();
	simulationNode->insertChild(guiStateNode);
	triggerSubtreeInsertedEvent(simulationNode);
}

template <class T> void SceneManager::insert(shared_ptr<BSplineCurve<T>> curve, BSplineCurveGUIStateNode_ptr guiStateNode) {
	doInsert<BSplineCurve<T>, BSplineCurveNode, BSplineCurveGUIStateNode>(curve, guiStateNode);
}
template void SceneManager::insert(shared_ptr<BSplineCurve<hpvec2>> curve, BSplineCurveGUIStateNode_ptr guiStateNode);

template <class T> PointCloudRenderStateNode_ptr SceneManager::insert(shared_ptr<BSplineCurve<T>> curve, PointCloud_ptr pointCloud, hpcolor& color) {
	return doInsert<BSplineCurve<T>, BSplineCurveNode>(curve, pointCloud, color);
}
template PointCloudRenderStateNode_ptr SceneManager::insert(shared_ptr<BSplineCurve<hpvec2>> curve, PointCloud_ptr pointCloud, hpcolor& color);

template <class T> LineMeshRenderStateNode_ptr SceneManager::insert(shared_ptr<BSplineCurve<T>> curve, LineMesh_ptr lineMesh, hpcolor& color) {
	return doInsert<BSplineCurve<T>, BSplineCurveNode>(curve, lineMesh, color);
}
template LineMeshRenderStateNode_ptr SceneManager::insert(shared_ptr<BSplineCurve<hpvec2>> curve, LineMesh_ptr lineMesh, hpcolor& color);

void SceneManager::insert(FocalSpline_ptr focalSpline, FocalSplineGUIStateNode_ptr guiStateNode) {
	doInsert<FocalSpline, FocalSplineNode, FocalSplineGUIStateNode>(focalSpline, guiStateNode);
}

PointCloudRenderStateNode_ptr SceneManager::insert(FocalSpline_ptr focalSpline, PointCloud_ptr pointCloud, hpcolor& color) {
	return doInsert<FocalSpline, FocalSplineNode>(focalSpline, pointCloud, color);
}

LineMeshRenderStateNode_ptr SceneManager::insert(FocalSpline_ptr focalSpline, LineMesh_ptr lineMesh, hpcolor& color) {
	return doInsert<FocalSpline, FocalSplineNode>(focalSpline, lineMesh, color);
}


TriangleMeshRenderStateNode_ptr SceneManager::insert(SimpleGear_ptr simpleGear, TriangleMesh3D_ptr triangleMesh, vector<hpcolor>* color, RigidAffineTransformation& transformation){
	return doInsert<SimpleGear, SimpleGearNode >(simpleGear, triangleMesh, color, transformation);
}

void SceneManager::insert(InvoluteGear_ptr involuteGear, InvoluteGearGUIStateNode_ptr involuteGearGUIStateNode) {
	doInsert<InvoluteGear, InvoluteGearNode, InvoluteGearGUIStateNode>(involuteGear, involuteGearGUIStateNode);
}

TriangleMeshRenderStateNode_ptr SceneManager::insert(InvoluteGear_ptr involuteGear, TriangleMesh3D_ptr triangleMesh, hpcolor& color) {
	return doInsert<InvoluteGear, InvoluteGearNode>(involuteGear, triangleMesh, color);
}

void SceneManager::insert(Plane_ptr plane) {
	doInsert<Plane, PlaneNode>(plane);
}

template <class T> void SceneManager::insert(Plane_ptr plane, shared_ptr<BSplineCurve<T>> curve) {
	doInsert<Plane, PlaneNode, BSplineCurve<T>, BSplineCurveNode>(plane, curve);
}
template void SceneManager::insert(Plane_ptr plane, shared_ptr<BSplineCurve<hpvec2>> curve);

void SceneManager::insert(Plane_ptr plane, PlaneGUIStateNode_ptr planeGUIStateNode) {
	doInsert<Plane, PlaneNode, PlaneGUIStateNode>(plane, planeGUIStateNode);
}

TriangleMeshRenderStateNode_ptr  SceneManager::insert(Plane_ptr plane, TriangleMesh3D_ptr triangleMesh, hpcolor& color) {
	return doInsert<Plane, PlaneNode>(plane, triangleMesh, color);
}

LineMeshRenderStateNode_ptr SceneManager::insert(Plane_ptr plane, LineMesh_ptr lineMesh, hpcolor& color) {
	return doInsert<Plane, PlaneNode>(plane, lineMesh, color);
}

PointCloudRenderStateNode_ptr SceneManager::insert(Plane_ptr plane, PointCloud_ptr pointCloud, hpcolor& color){
	return doInsert<Plane,PlaneNode>(plane, pointCloud, color);
}

void SceneManager::insert(SimpleGear_ptr simpleGear, SimpleGearGUIStateNode_ptr simpleGearGUIStateNode) {
	doInsert<SimpleGear, SimpleGearNode, SimpleGearGUIStateNode>(simpleGear, simpleGearGUIStateNode);
}

TriangleMeshRenderStateNode_ptr SceneManager::insert(SimpleGear_ptr simpleGear, TriangleMesh3D_ptr triangleMesh, hpcolor& color) {
	return doInsert<SimpleGear, SimpleGearNode>(simpleGear, triangleMesh, color);
}

void SceneManager::insert(SurfaceOfRevolution_ptr disc, DiscGUIStateNode_ptr discGUIStateNode) {
    doInsert<SurfaceOfRevolution, DiscNode, DiscGUIStateNode>(disc, discGUIStateNode);
}

TriangleMeshRenderStateNode_ptr SceneManager::insert(SurfaceOfRevolution_ptr disc, TriangleMesh3D_ptr triangleMesh, hpcolor& color) {
   return doInsert<SurfaceOfRevolution, DiscNode>(disc, triangleMesh, color);
}

TriangleMeshRenderStateNode_ptr SceneManager::insert(SurfaceOfRevolution_ptr disc, TriangleMesh3D_ptr triangleMesh, hpcolor& color, RigidAffineTransformation& transformation){
   return doInsert<SurfaceOfRevolution, DiscNode >(disc, triangleMesh, color, transformation);
}

void SceneManager::insert(DiscGearGrind_ptr discGearGrind, DiscGearGrindGUIStateNode_ptr discGearGrindGUIStateNode) {
	doInsertSimulation<DiscGearGrind, DiscGearGrindNode, DiscGearGrindGUIStateNode>(discGearGrind, discGearGrindGUIStateNode);
}

void SceneManager::insert(WormGearGrind_ptr wormGearGrind, WormGearGrindGUIStateNode_ptr wormGearGrindGUIStateNode) {
	doInsertSimulation<WormGearGrind, WormGearGrindNode, WormGearGrindGUIStateNode>(wormGearGrind, wormGearGrindGUIStateNode);
}

void SceneManager::insert(ToothProfile_ptr toothProfile, ToothProfileGUIStateNode_ptr toothProfileGuiStateNode) {
	doInsert<ToothProfile, ToothProfileNode, ToothProfileGUIStateNode>(toothProfile, toothProfileGuiStateNode);
}
LineMeshRenderStateNode_ptr SceneManager::insert(ToothProfile_ptr toothProfile, LineMesh_ptr lineMesh, hpcolor& color) {
	return doInsert<ToothProfile, ToothProfileNode>(toothProfile, lineMesh, color);
}
PointCloudRenderStateNode_ptr SceneManager::insert(ToothProfile_ptr toothProfile, PointCloud_ptr pointCloud, hpcolor& color) {
	return doInsert<ToothProfile, ToothProfileNode>(toothProfile, pointCloud, color);
}

void SceneManager::insert(TriangleMesh3D_ptr triangleMesh, TriangleMeshGUIStateNode_ptr triangleMeshGUIStateNode) {
	doInsert<TriangleMesh3D, TriangleMeshNode, TriangleMeshGUIStateNode>(triangleMesh, triangleMeshGUIStateNode);
}

TriangleMeshRenderStateNode_ptr SceneManager::insert(TriangleMesh3D_ptr triangleMesh, hpcolor& color) {
	Node_ptr node = findContainingData(triangleMesh);
	TriangleMeshRenderStateNode_ptr triangleMeshRenderStateNode;
	if(node) {
		TriangleMeshNode_ptr triangleMeshNode = dynamic_pointer_cast<TriangleMeshNode>(node);
		TriangleMeshRenderStateNode_ptr triangleMeshRenderStateNode = triangleMeshNode->getTriangleMeshRenderStateNode();
		if(triangleMeshRenderStateNode) {
			triangleMeshRenderStateNode->setColor(color);
			triggerSubtreeUpdatedEvent(triangleMeshRenderStateNode);
		} else {
			TriangleMeshRenderStateNode_ptr triangleMeshRenderStateNode(new TriangleMeshRenderStateNode(triangleMesh, color));
			triangleMeshNode->insertChild(triangleMeshRenderStateNode);
			triggerSubtreeInsertedEvent(triangleMeshRenderStateNode);
		}
	} else {
		TriangleMeshNode_ptr triangleMeshNode(new TriangleMeshNode(triangleMesh));
		TriangleMeshRenderStateNode_ptr triangleMeshRenderStateNode(new TriangleMeshRenderStateNode(triangleMesh, color));
		triangleMeshNode->insertChild(triangleMeshRenderStateNode);
		insertChild(triangleMeshNode);
		triggerSubtreeInsertedEvent(triangleMeshNode);
	}
	return triangleMeshRenderStateNode;
}

void SceneManager::insert(Worm_ptr worm, WormGUIStateNode_ptr wormGUIStateNode) {
	doInsert<Worm, WormNode, WormGUIStateNode>(worm, wormGUIStateNode);
}

TriangleMeshRenderStateNode_ptr SceneManager::insert(Worm_ptr worm, TriangleMesh3D_ptr triangleMesh, hpcolor& color) {
	return doInsert<Worm, WormNode>(worm, triangleMesh, color);
}

TriangleMeshRenderStateNode_ptr SceneManager::insert(SpherePatch_ptr spherePatch, TriangleMesh3D_ptr triangleMesh, hpcolor& color) {
	return doInsert<SpherePatch, SpherePatchNode>(spherePatch,triangleMesh,color);
}
void SceneManager::insert(SpherePatch_ptr spherePatch, SpherePatchGUIStateNode_ptr spherePatchGUIStateNode) {
	doInsert<SpherePatch, SpherePatchNode>(spherePatch,spherePatchGUIStateNode);
}

void SceneManager::registerSceneListener(SceneListener* sceneListener) {
	m_listeners.push_back(sceneListener);
}

Node_ptr SceneManager::remove(Node_ptr node) {
	Node_ptr removed = Node::remove(node);
	if(removed) triggerSubtreeRemovedEvent(removed);
	return removed;
}

void SceneManager::remove(vector<Node_ptr>& nodes) {
	vector<Node_ptr> removedNodes;
	removedNodes.reserve(nodes.size());
	Node::remove(nodes, removedNodes);
	if(removedNodes.size() > 0) triggerSubtreesRemovedEvent(removedNodes);
}

void SceneManager::remove(vector<Node_ptr>& nodes, vector<Node_ptr>& removedNodes) {
	Node::remove(nodes, removedNodes);
	if(removedNodes.size() > 0) triggerSubtreesRemovedEvent(removedNodes);
}

Node_ptr SceneManager::removeChildContainingData(shared_ptr<void> data) {
	Node_ptr node = Node::removeChildContainingData(data);
	if(node) triggerSubtreeRemovedEvent(node);
	return node;
}

Node_ptr SceneManager::removeContainingData(shared_ptr<void> parentData, shared_ptr<void> childData) {
	Node_ptr node = Node::removeContainingData(parentData, childData);
	if(node) triggerSubtreeRemovedEvent(node);
	return node;
}

void SceneManager::triggerSubtreeInsertedEvent(Node_ptr root) {
	for(list<SceneListener*>::iterator i = m_listeners.begin(), end = m_listeners.end(); i != end; ++i)
		(*i)->handleSubtreeInsertedEvent(root);
}

void SceneManager::triggerSubtreesInsertedEvent(vector<Node_ptr>& roots) {
	for(list<SceneListener*>::iterator i = m_listeners.begin(), end = m_listeners.end(); i != end; ++i)
		(*i)->handleSubtreesInsertedEvent(roots);
}

void SceneManager::triggerSubtreeRemovedEvent(Node_ptr root) {
	for(list<SceneListener*>::iterator i = m_listeners.begin(), end = m_listeners.end(); i != end; ++i)
		(*i)->handleSubtreeRemovedEvent(root);
}

void SceneManager::triggerSubtreesRemovedEvent(vector<Node_ptr>& roots) {
	for(list<SceneListener*>::iterator i = m_listeners.begin(), end = m_listeners.end(); i != end; ++i)
		(*i)->handleSubtreesRemovedEvent(roots);
}

void SceneManager::triggerSubtreeUpdatedEvent(Node_ptr root) {
	for(list<SceneListener*>::iterator i = m_listeners.begin(), end = m_listeners.end(); i != end; ++i)
		(*i)->handleSubtreeUpdatedEvent(root);
}

void SceneManager::triggerSubtreesUpdatedEvent(vector<Node_ptr>& roots) {
	for(list<SceneListener*>::iterator i = m_listeners.begin(), end = m_listeners.end(); i != end; ++i)
		(*i)->handleSubtreesUpdatedEvent(roots);
}

void SceneManager::update( Plane_ptr plane ) {
	Node_ptr node = findContainingData(plane);
	if( node ) {
		PlaneNode_ptr planeNode = static_pointer_cast<PlaneNode>( node );
		planeNode->planeChanged();
	}
}

void SceneManager::unregisterSceneListener(SceneListener* sceneListener) {
	m_listeners.remove(sceneListener);
}


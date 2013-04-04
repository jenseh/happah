#include <ctime>
#include <iostream>

#include "happah/scene/BSplineCurveNode.h"
#include "happah/scene/InvoluteGearNode.h"
#include "happah/scene/LineMeshNode.h"
#include "happah/scene/PlaneNode.h"
#include "happah/scene/PointCloudNode.h"
#include "happah/scene/SceneManager.h"
#include "happah/scene/TriangleMeshNode.h"
#include "happah/scene/RenderStateNode.h"
#include "happah/scene/SimpleGearNode.h"
#include "happah/scene/DiscNode.h"
#include "happah/scene/WormNode.h"
#include "happah/scene/SpherePatchNode.h"

SceneManager::SceneManager() {}

SceneManager::~SceneManager() {}

template<class G, class N, class S>
void SceneManager::doInsert(shared_ptr<G> data, shared_ptr<S> guiStateNode) {
	Node_ptr node = findChildContainingData(data);

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
void SceneManager::doInsert(shared_ptr<G> geometry, TriangleMesh_ptr triangleMesh, hpcolor& color) {
	Node_ptr node = findChildContainingData(geometry);
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
			return;
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
}

template<class G, class N>
void SceneManager::doInsert(shared_ptr<G> geometry, TriangleMesh_ptr triangleMesh, vector<hpcolor>* color, RigidAffineTransformation& transformation) {
	Node_ptr node = findChildContainingData(geometry);

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
				return;
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
}

template<class G, class N>
void SceneManager::doInsert(shared_ptr<G> geometry, TriangleMesh_ptr triangleMesh, hpcolor& color, RigidAffineTransformation& transformation) {
	Node_ptr node = findChildContainingData(geometry);

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
			return;
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
}
template<class G, class N>
void SceneManager::doInsert(shared_ptr<G> geometry, LineMesh_ptr lineMesh, hpcolor& color) {
	Node_ptr node = findChildContainingData(geometry);

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
			return;
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
}

template<class G, class N>
void SceneManager::doInsert(shared_ptr<G> geometry, LineMesh_ptr lineMesh, vector<hpcolor>* color, RigidAffineTransformation& transformation) {
	Node_ptr node = findChildContainingData(geometry);

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
				return;
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
}

template<class G, class N>
void SceneManager::doInsert(shared_ptr<G> geometry, LineMesh_ptr lineMesh, hpcolor& color, RigidAffineTransformation& transformation) {
	Node_ptr node = findChildContainingData(geometry);

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
			return;
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
}


template<class G, class N>
void SceneManager::doInsert(shared_ptr<G> geometry, PointCloud_ptr pointCloud, hpcolor& color, RigidAffineTransformation& transformation){
	Node_ptr node = findChildContainingData(geometry);

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
			return;
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
}

template<class G, class N>

void SceneManager::doInsert(shared_ptr<G> geometry, PointCloud_ptr pointCloud, hpcolor& color){
	Node_ptr node = findChildContainingData(geometry);

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
			return;
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
}
template<class S, class N, class G>
void SceneManager::doInsertSimulation(shared_ptr<S> simulation, shared_ptr<G> guiStateNode) {
    shared_ptr<N> simulationNode = shared_ptr<N>(new N(simulation));
    insertChild(simulationNode);
    simulationNode->buildSubtree();
    simulationNode->insertChild(guiStateNode);
    triggerSubtreeInsertedEvent(simulationNode);
}

void SceneManager::insert(BSplineCurve_ptr curve, BSplineCurveGUIStateNode_ptr guiStateNode) {
	doInsert<BSplineCurve, BSplineCurveNode, BSplineCurveGUIStateNode>(curve, guiStateNode);
}

void SceneManager::insert(BSplineCurve_ptr curve, PointCloud_ptr pointCloud, hpcolor& color) {
	doInsert<BSplineCurve, BSplineCurveNode>(curve, pointCloud, color);
}

void SceneManager::insert(BSplineCurve_ptr curve, LineMesh_ptr lineMesh, hpcolor& color) {
	doInsert<BSplineCurve, BSplineCurveNode>(curve, lineMesh, color);
}


void SceneManager::insert(SimpleGear_ptr simpleGear, TriangleMesh_ptr triangleMesh, vector<hpcolor>* color, RigidAffineTransformation& transformation){
	doInsert<SimpleGear, SimpleGearNode >(simpleGear, triangleMesh, color, transformation);
}

void SceneManager::insert(InvoluteGear_ptr involuteGear, InvoluteGearGUIStateNode_ptr involuteGearGUIStateNode) {
	doInsert<InvoluteGear, InvoluteGearNode, InvoluteGearGUIStateNode>(involuteGear, involuteGearGUIStateNode);
}

void SceneManager::insert(InvoluteGear_ptr involuteGear, TriangleMesh_ptr triangleMesh, hpcolor& color) {
	doInsert<InvoluteGear, InvoluteGearNode>(involuteGear, triangleMesh, color);
}

void SceneManager::insert(Plane_ptr plane, PlaneGUIStateNode_ptr planeGUIStateNode) {
	doInsert<Plane, PlaneNode, PlaneGUIStateNode>(plane, planeGUIStateNode);
}

void SceneManager::insert(Plane_ptr plane, TriangleMesh_ptr triangleMesh, hpcolor& color) {
	doInsert<Plane, PlaneNode>(plane, triangleMesh, color);
}

void SceneManager::insert(Plane_ptr plane, LineMesh_ptr lineMesh, hpcolor& color) {
	doInsert<Plane, PlaneNode>(plane, lineMesh, color);
}

void SceneManager::insert(Plane_ptr plane,PointCloud_ptr pointCloud,hpcolor& color){
	doInsert<Plane,PlaneNode>(plane,pointCloud, color);
}

void SceneManager::insert(SimpleGear_ptr simpleGear, SimpleGearGUIStateNode_ptr simpleGearGUIStateNode) {
	doInsert<SimpleGear, SimpleGearNode, SimpleGearGUIStateNode>(simpleGear, simpleGearGUIStateNode);
}

void SceneManager::insert(SimpleGear_ptr simpleGear, TriangleMesh_ptr triangleMesh, hpcolor& color) {
	doInsert<SimpleGear, SimpleGearNode>(simpleGear, triangleMesh, color);
}

void SceneManager::insert(SurfaceOfRevolution_ptr disc, DiscGUIStateNode_ptr discGUIStateNode) {
    doInsert<SurfaceOfRevolution, DiscNode, DiscGUIStateNode>(disc, discGUIStateNode);
}

void SceneManager::insert(SurfaceOfRevolution_ptr disc, TriangleMesh_ptr triangleMesh, hpcolor& color) {
    doInsert<SurfaceOfRevolution, DiscNode>(disc, triangleMesh, color);
}

void SceneManager::insert(SurfaceOfRevolution_ptr disc, TriangleMesh_ptr triangleMesh, hpcolor& color, RigidAffineTransformation& transformation){
    doInsert<SurfaceOfRevolution, DiscNode >(disc, triangleMesh, color, transformation);
}

void SceneManager::insert(DiscGearGrind_ptr discGearGrind, DiscGearGrindGUIStateNode_ptr discGearGrindGUIStateNode) {
	doInsertSimulation<DiscGearGrind, DiscGearGrindNode, DiscGearGrindGUIStateNode>(discGearGrind, discGearGrindGUIStateNode);
}

void SceneManager::insert(Worm_ptr worm, WormGUIStateNode_ptr wormGUIStateNode) {
	doInsert<Worm, WormNode, WormGUIStateNode>(worm, wormGUIStateNode);
}

void SceneManager::insert(Worm_ptr worm, TriangleMesh_ptr triangleMesh, hpcolor& color) {
	doInsert<Worm, WormNode>(worm, triangleMesh, color);
}

void SceneManager::insert(SpherePatch_ptr spherePatch, TriangleMesh_ptr triangleMesh, hpcolor& color) {
	doInsert<SpherePatch, SpherePatchNode>(spherePatch,triangleMesh,color);
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

void SceneManager::unregisterSceneListener(SceneListener* sceneListener) {
	m_listeners.remove(sceneListener);
}


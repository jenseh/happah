#include "happah/scene/PlaneNode.h"

PlaneNode::PlaneNode(Plane_ptr plane) : SimpleGeometryNode<Plane>(plane) {
	planeChanged();
}

PlaneNode::~PlaneNode() {}

void PlaneNode::accept(SceneVisitor& sceneVisitor) {
	sceneVisitor.visit(*this);
	Node::accept(sceneVisitor);
}

void PlaneNode::draw(DrawVisitor& drawVisitor, RigidAffineTransformation& rigidAffineTransformation) {
	RigidAffineTransformation composedRigidAffineTransformation;
	rigidAffineTransformation.compose(m_xyPlaneToThisPlaneTransformation, composedRigidAffineTransformation);
	SimpleGeometryNode::draw(drawVisitor, composedRigidAffineTransformation);
}

void PlaneNode::insertChild(BSplineCurveNode_ptr curveNode) {
	Node::insertChild(curveNode);
}

void PlaneNode::insertChild(PlaneGUIStateNode_ptr planeGUIStateNode) {
	Node::insertChild(planeGUIStateNode);
}

void PlaneNode::insertChild(TriangleMeshNode_ptr triangleMeshNode) {
	Node::insertChild(triangleMeshNode);
}

void PlaneNode::insertChild(PointCloudNode_ptr pointCloudNode) {
	Node::insertChild(pointCloudNode);
}

void PlaneNode::insertChild(LineMeshNode_ptr LineMeshNode) {
	Node::insertChild(LineMeshNode);
}

void PlaneNode::planeChanged() {
	hpvec3 normal = glm::normalize(m_geometry->getNormal());
	hpvec3 v2 = m_geometry->getSystemXVector();
	/*
	hpvec3 v2 = hpvec3(1.f,0.f,0.f);
	hpvec3 v3 = hpvec3(0.f,0.f,0.f);

	if( std::abs( normal.x ) > HP_EPSILON || std::abs( normal.z ) > HP_EPSILON )
	{
		v2 = glm::cross( normal, hpvec3(0.f, 1.f, 0.f) );
		v2 = glm::normalize(v2);
	}
	*/
	hpvec3 v3 = glm::cross(normal, v2);
	v3 = glm::normalize(v3);

	hpmat3x3 transformation = hpmat3x3( v2, v3, normal );
	//transformation = glm::transpose(hpmat3x3( normal, v2, v3 ));

	m_xyPlaneToThisPlaneTransformation.setMatrix( transformation );

	m_xyPlaneToThisPlaneTransformation.setTranslation(m_geometry->getOrigin());
}

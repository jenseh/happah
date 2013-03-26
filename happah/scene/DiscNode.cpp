/*
 * DiscNode.cpp
 *
 *  Created on: 11.03.2013
 *      Author: jlabeit
 */

#include "DiscNode.h"

DiscNode::DiscNode(SurfaceOfRevolution_ptr disc)
	: SimpleGeometryNode<SurfaceOfRevolution>(disc) {}

DiscNode::~DiscNode() {}

void DiscNode::accept(SceneVisitor& sceneVisitor) {
	sceneVisitor.visit(*this);
	Node::accept(sceneVisitor);
}

void DiscNode::insertChild(DiscGUIStateNode_ptr discGUIStateNode) {
	Node::insertChild(discGUIStateNode);
}

void DiscNode::insertChild(TriangleMeshNode_ptr triangleMeshNode) {
	Node::insertChild(triangleMeshNode);
}

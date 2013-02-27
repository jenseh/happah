#include "happah/scene/SimpleGeometryNode.h"

SimpleGeometryNode::SimpleGeometryNode(G* geometry) 
	: m_geometry(geometry) {}

SimpleGeometryNode::~SimpleGeometryNode() {
	delete m_geometry;
}

G* SimpleGeometryNode::getGeometry() {
	return m_geometry;
}

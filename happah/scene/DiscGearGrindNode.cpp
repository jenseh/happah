#include "DiscGearGrindNode.h"

DiscGearGrindNode::DiscGearGrindNode(DiscGearGrind_ptr discGearGrind): m_discGearGrind(discGearGrind) {}

DiscGearGrindNode::~DiscGearGrindNode() {}

void DiscGearGrindNode::buildSubtree() {
	// Retrieve simulation result at start time
    DiscGearGrindResult result = m_discGearGrind->getSimulationResult(0);

    // Add a new tool node
    m_discMeshNode = TriangleMeshNode_ptr(new TriangleMeshNode(result.m_toolMesh, result.m_toolTransformation));
    m_discRenderStateNode = TriangleMeshRenderStateNode_ptr(new TriangleMeshRenderStateNode(result.m_toolMesh, result.m_toolColor) );
    m_discMeshNode->insertChild(m_discRenderStateNode);
    Node::insertChild(m_discMeshNode);

    // Add a new gear node
    m_gearMeshNode = TriangleMeshNode_ptr(new TriangleMeshNode(result.m_gearMesh, result.m_gearTransformation));
    m_gearRenderStateNode = TriangleMeshRenderStateNode_ptr(new TriangleMeshRenderStateNode(result.m_gearMesh, result.m_gearColor) );
    m_gearMeshNode->insertChild(m_gearRenderStateNode);
    Node::insertChild(m_gearMeshNode);
}

void DiscGearGrindNode::insertChild(DiscGearGrindGUIStateNode_ptr discGearGrindGUIStateNode) {
	Node::insertChild(discGearGrindGUIStateNode);
}

void DiscGearGrindNode::update(hpreal time) {
	// Retrieve simulation result at current time
	DiscGearGrindResult result = m_discGearGrind->getSimulationResult(time);

	// Remove previous disc and gear nodes
    removeChild(m_discMeshNode);
    removeChild(m_gearMeshNode);

    // Only add a new tool node, if it is set to be visible
    if(m_discGearGrind->getToolVisibility()) {
		m_discMeshNode = TriangleMeshNode_ptr(new TriangleMeshNode(result.m_toolMesh, result.m_toolTransformation));
		m_discRenderStateNode = TriangleMeshRenderStateNode_ptr(new TriangleMeshRenderStateNode(result.m_toolMesh, result.m_toolColor));
		m_discMeshNode->insertChild(m_discRenderStateNode);
		Node::insertChild(m_discMeshNode);
    }

    // Add updated gear node
    m_gearMeshNode = TriangleMeshNode_ptr(new TriangleMeshNode(result.m_gearMesh, result.m_gearTransformation));
    m_gearRenderStateNode = TriangleMeshRenderStateNode_ptr(new TriangleMeshRenderStateNode(result.m_gearMesh, result.m_gearColor));
    m_gearMeshNode->insertChild(m_gearRenderStateNode);
    Node::insertChild(m_gearMeshNode);
}

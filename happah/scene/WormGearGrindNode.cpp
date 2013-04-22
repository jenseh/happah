#include "WormGearGrindNode.h"

WormGearGrindNode::WormGearGrindNode(WormGearGrind_ptr wormGearGrind): m_wormGearGrind(wormGearGrind) {}

WormGearGrindNode::~WormGearGrindNode() {}

void WormGearGrindNode::buildSubtree() {
	// Retrieve simulation result at start time
    WormGearGrindResult result = m_wormGearGrind->getSimulationResult(0);

    // Add a new tool node
    m_wormMeshNode = TriangleMeshNode_ptr(new TriangleMeshNode(result.m_toolMesh, result.m_toolTransformation));
    m_wormRenderStateNode = TriangleMeshRenderStateNode_ptr(new TriangleMeshRenderStateNode(result.m_toolMesh, result.m_toolColor));
    m_wormMeshNode->insertChild(m_wormRenderStateNode);
    Node::insertChild(m_wormMeshNode);

    // Add a new gear node
    m_gearMeshNode = TriangleMeshNode_ptr(new TriangleMeshNode(result.m_gearMesh, result.m_gearTransformation));
    m_gearRenderStateNode = TriangleMeshRenderStateNode_ptr(new TriangleMeshRenderStateNode(result.m_gearMesh, result.m_gearColor));
    m_gearMeshNode->insertChild(m_gearRenderStateNode);
    Node::insertChild(m_gearMeshNode);
}

void WormGearGrindNode::insertChild(WormGearGrindGUIStateNode_ptr wormGearGrindGUIStateNode) {
	Node::insertChild(wormGearGrindGUIStateNode);
}

void WormGearGrindNode::update(hpreal time) {
	// Retrieve simulation result at current time
	WormGearGrindResult result = m_wormGearGrind->getSimulationResult(time);

	// Remove previous disc and gear nodes
    removeChild(m_wormMeshNode);
    removeChild(m_gearMeshNode);

    // Only add a new tool node, if it is set to be visible
    if(m_wormGearGrind->getToolVisibility()) {
		m_wormMeshNode = TriangleMeshNode_ptr(new TriangleMeshNode(result.m_toolMesh, result.m_toolTransformation));
		m_wormRenderStateNode = TriangleMeshRenderStateNode_ptr(new TriangleMeshRenderStateNode(result.m_toolMesh, result.m_toolColor) );
		m_wormMeshNode->insertChild(m_wormRenderStateNode);
		Node::insertChild(m_wormMeshNode);
    }

    // Add updated gear node
    m_gearMeshNode = TriangleMeshNode_ptr(new TriangleMeshNode(result.m_gearMesh, result.m_gearTransformation));
    m_gearRenderStateNode = TriangleMeshRenderStateNode_ptr(new TriangleMeshRenderStateNode(result.m_gearMesh, result.m_gearColor) );
    m_gearMeshNode->insertChild(m_gearRenderStateNode);
    Node::insertChild(m_gearMeshNode);
}

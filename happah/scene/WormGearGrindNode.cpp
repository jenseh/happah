#include "WormGearGrindNode.h"

WormGearGrindNode::WormGearGrindNode(WormGearGrind_ptr wormGearGrind): m_wormGearGrind(wormGearGrind)
{
    //m_wormGearGrind->runSimulation();
}

WormGearGrindNode::~WormGearGrindNode() {}

void WormGearGrindNode::buildSubtree() {
    WormGearGrindResult result = m_wormGearGrind->getSimulationResult(0);


    m_wormMeshNode = TriangleMeshNode_ptr(new TriangleMeshNode(result.m_toolMesh, result.m_toolTransformation));
    m_wormRenderStateNode = TriangleMeshRenderStateNode_ptr(new TriangleMeshRenderStateNode(result.m_toolMesh, result.m_toolColor));
    m_wormMeshNode->insertChild(m_wormRenderStateNode);
    Node::insertChild(m_wormMeshNode);

    m_gearMeshNode = TriangleMeshNode_ptr(new TriangleMeshNode(result.m_gearMesh, result.m_gearTransformation));
    m_gearRenderStateNode = TriangleMeshRenderStateNode_ptr(new TriangleMeshRenderStateNode(result.m_gearMesh, result.m_gearColor));
    m_gearMeshNode->insertChild(m_gearRenderStateNode);
    Node::insertChild(m_gearMeshNode);
}

void WormGearGrindNode::insertChild(WormGearGrindGUIStateNode_ptr wormGearGrindGUIStateNode) {
	Node::insertChild(wormGearGrindGUIStateNode);
}

void WormGearGrindNode::update(hpreal time) {
	WormGearGrindResult result = m_wormGearGrind->getSimulationResult(time);

	//TODO remove mesh nodes and render state nodes properly
    removeChild(m_wormMeshNode);
    removeChild(m_gearMeshNode);

    m_wormMeshNode = TriangleMeshNode_ptr(new TriangleMeshNode(result.m_toolMesh, result.m_toolTransformation));
    m_wormRenderStateNode = TriangleMeshRenderStateNode_ptr(new TriangleMeshRenderStateNode(result.m_toolMesh, result.m_toolColor) );
    m_wormMeshNode->insertChild(m_wormRenderStateNode);
    Node::insertChild(m_wormMeshNode);

    m_gearMeshNode = TriangleMeshNode_ptr(new TriangleMeshNode(result.m_gearMesh, result.m_gearTransformation));
    m_gearRenderStateNode = TriangleMeshRenderStateNode_ptr(new TriangleMeshRenderStateNode(result.m_gearMesh, result.m_gearColor) );
    m_gearMeshNode->insertChild(m_gearRenderStateNode);
    Node::insertChild(m_gearMeshNode);
}

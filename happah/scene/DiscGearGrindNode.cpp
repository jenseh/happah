#include "DiscGearGrindNode.h"

DiscGearGrindNode::DiscGearGrindNode(DiscGearGrind_ptr discGearGrind): m_discGearGrind(discGearGrind)
{
    //m_discGearGrind->runSimulation();
}

DiscGearGrindNode::~DiscGearGrindNode() {}

void DiscGearGrindNode::buildSubtree() {
    DiscGearGrindResult result = m_discGearGrind->getSimulationResult(0);


    m_discMeshNode = TriangleMeshNode_ptr(new TriangleMeshNode(result.m_toolMesh, result.m_toolTransformation));
    m_discRenderStateNode = TriangleMeshRenderStateNode_ptr(new TriangleMeshRenderStateNode(result.m_toolMesh, result.m_toolColor) );
    m_discMeshNode->insertChild(m_discRenderStateNode);
    Node::insertChild(m_discMeshNode);

    m_gearMeshNode = TriangleMeshNode_ptr(new TriangleMeshNode(result.m_gearMesh, result.m_gearTransformation));
    m_gearRenderStateNode = TriangleMeshRenderStateNode_ptr(new TriangleMeshRenderStateNode(result.m_gearMesh, result.m_gearColor) );
    m_gearMeshNode->insertChild(m_gearRenderStateNode);
    Node::insertChild(m_gearMeshNode);
}

void DiscGearGrindNode::insertChild(DiscGearGrindGUIStateNode_ptr discGearGrindGUIStateNode) {
	Node::insertChild(discGearGrindGUIStateNode);
}

void DiscGearGrindNode::update(hpreal time) {
	DiscGearGrindResult result = m_discGearGrind->getSimulationResult(time);
	//TODO mesh nodes and render state nodes properly
    removeChild(m_discMeshNode);
    removeChild(m_gearMeshNode);

    m_discMeshNode = TriangleMeshNode_ptr(new TriangleMeshNode(result.m_toolMesh, result.m_toolTransformation));
    m_discRenderStateNode = TriangleMeshRenderStateNode_ptr(new TriangleMeshRenderStateNode(result.m_toolMesh, result.m_toolColor) );
    m_discMeshNode->insertChild(m_discRenderStateNode);
    Node::insertChild(m_discMeshNode);

    m_gearMeshNode = TriangleMeshNode_ptr(new TriangleMeshNode(result.m_gearMesh, result.m_gearTransformation));
    m_gearRenderStateNode = TriangleMeshRenderStateNode_ptr(new TriangleMeshRenderStateNode(result.m_gearMesh, result.m_gearColor) );
    m_gearMeshNode->insertChild(m_gearRenderStateNode);
    Node::insertChild(m_gearMeshNode);
}

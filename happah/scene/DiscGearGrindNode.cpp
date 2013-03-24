#include "DiscGearGrindNode.h"

DiscGearGrindNode::DiscGearGrindNode(SceneManager* sceneManager, DiscGearGrind_ptr discGearGrind):
    SimulationNode(sceneManager), m_discGearGrind(discGearGrind)
{
    //m_discGearGrind->runSimulation();
    DiscGearGrindResult result = m_discGearGrind->getSimulationResult(0);

    m_discMeshNode = TriangleMeshNode_ptr(new TriangleMeshNode(result.m_toolMesh, result.m_toolTransformation));
    m_discRenderStateNode = TriangleMeshRenderStateNode_ptr(new TriangleMeshRenderStateNode(result.m_toolMesh, result.m_toolColor) );
    m_discMeshNode->insertChild(m_discRenderStateNode);
    Node::insertChild(m_discMeshNode);

    m_gearMeshNode = TriangleMeshNode_ptr(new TriangleMeshNode(result.m_toolMesh, result.m_toolTransformation));
    m_gearRenderStateNode = TriangleMeshRenderStateNode_ptr(new TriangleMeshRenderStateNode(result.m_gearMesh, result.m_gearColor) );
    m_gearMeshNode->insertChild(m_gearRenderStateNode);
    Node::insertChild(m_gearMeshNode);
}

DiscGearGrindNode::~DiscGearGrindNode() {}


void DiscGearGrindNode::update(hpreal time) {

}

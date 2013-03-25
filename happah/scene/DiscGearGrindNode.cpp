#include "DiscGearGrindNode.h"

DiscGearGrindNode::DiscGearGrindNode(SceneManager* sceneManager, DiscGearGrind_ptr discGearGrind):
    SimulationNode(sceneManager), m_discGearGrind(discGearGrind)
{
    //m_discGearGrind->runSimulation();
}

DiscGearGrindNode::~DiscGearGrindNode() {}

void DiscGearGrindNode::addTriangleMeshes() {
    DiscGearGrindResult result = m_discGearGrind->getSimulationResult(0);

    m_discMeshNode = TriangleMeshNode_ptr(new TriangleMeshNode(result.m_toolMesh, result.m_toolTransformation));
    m_discRenderStateNode = TriangleMeshRenderStateNode_ptr(new TriangleMeshRenderStateNode(result.m_toolMesh, result.m_toolColor) );
    m_discMeshNode->insertChild(m_discRenderStateNode);
    insertChild(m_discMeshNode);

    m_gearMeshNode = TriangleMeshNode_ptr(new TriangleMeshNode(result.m_gearMesh, result.m_gearTransformation));
    m_gearRenderStateNode = TriangleMeshRenderStateNode_ptr(new TriangleMeshRenderStateNode(result.m_gearMesh, result.m_gearColor) );
    m_gearMeshNode->insertChild(m_gearRenderStateNode);
    insertChild(m_gearMeshNode);
}

void DiscGearGrindNode::update(hpreal time) {

}

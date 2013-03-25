#ifndef DISCGEARGRINDSIMULATIONNODE_H
#define DISCGEARGRINDSIMULATIONNODE_H
#include "happah/scene/SimulationNode.h"
#include "happah/scene/TriangleMeshNode.h"


class DiscGearGrindNode : public SimulationNode
{
    DiscGearGrind_ptr m_discGearGrind;
    TriangleMeshNode_ptr m_discMeshNode;
    TriangleMeshRenderStateNode_ptr m_discRenderStateNode;
    TriangleMeshNode_ptr m_gearMeshNode;
    TriangleMeshRenderStateNode_ptr m_gearRenderStateNode;

public:
    DiscGearGrindNode(SceneManager* sceneManager, DiscGearGrind_ptr discGearGrind);
    virtual ~DiscGearGrindNode();

    void addTriangleMeshes();
    void update(hpreal time);
};

#endif // DISCGEARGRINDSIMULATIONNODE_H

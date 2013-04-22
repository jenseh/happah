#ifndef DISCGEARGRINDNODE_H
#define DISCGEARGRINDNODE_H
#include "happah/scene/GUIStateNode.h"
#include "happah/scene/SimulationNode.h"
#include "happah/scene/TriangleMeshNode.h"
#include "happah/simulations/DiscGearGrind.h"


class DiscGearGrindNode : public SimulationNode
{
    DiscGearGrind_ptr m_discGearGrind;
    TriangleMeshNode_ptr m_discMeshNode;
    TriangleMeshRenderStateNode_ptr m_discRenderStateNode;
    TriangleMeshNode_ptr m_gearMeshNode;
    TriangleMeshRenderStateNode_ptr m_gearRenderStateNode;

public:
    DiscGearGrindNode(DiscGearGrind_ptr discGearGrind);
    virtual ~DiscGearGrindNode();

    void buildSubtree();
    void insertChild(DiscGearGrindGUIStateNode_ptr discGearGrindGUIStateNode);
    void update(hpreal time);
};

#endif // DISCGEARGRINDSIMULATIONNODE_H

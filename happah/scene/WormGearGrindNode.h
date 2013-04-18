#ifndef WORMGEARGRINDNODE_H_
#define WORMGEARGRINDNODE_H_

#include "happah/scene/GUIStateNode.h"
#include "happah/scene/SimulationNode.h"
#include "happah/scene/TriangleMeshNode.h"
#include "happah/scene/ZCircleCloudNode.h"
#include "happah/simulations/WormGearGrind.h"


class WormGearGrindNode : public SimulationNode
{
    WormGearGrind_ptr m_wormGearGrind;
    TriangleMeshNode_ptr m_wormMeshNode;
    TriangleMeshRenderStateNode_ptr m_wormRenderStateNode;
    TriangleMeshNode_ptr m_gearMeshNode;
    TriangleMeshRenderStateNode_ptr m_gearRenderStateNode;

public:
    WormGearGrindNode(WormGearGrind_ptr wormGearGrind);
    virtual ~WormGearGrindNode();

    void buildSubtree();
    void insertChild(WormGearGrindGUIStateNode_ptr wormGearGrindGUIStateNode);
    void update(hpreal time);
};


#endif /* WORMGEARGRINDNODE_H_ */

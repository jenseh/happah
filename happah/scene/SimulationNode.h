#ifndef SIMULATIONNODE_H
#define SIMULATIONNODE_H
#include "happah/scene/Node.h"
#include "happah/scene/SimulationVisitor.h"

class SceneManager;

class SimulationNode : public Node
{
    SceneManager* m_sceneManager;
public:
    SimulationNode(SceneManager* sceneManager);
    virtual ~SimulationNode();

    void accept(SimulationVisitor& simulationVisitor);
    virtual void addTriangleMeshes() = 0;
    virtual void update(hpreal currentTime)= 0;
};

#endif // SIMULATIONNODE_H

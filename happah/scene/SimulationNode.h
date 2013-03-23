#ifndef SIMULATIONNODE_H
#define SIMULATIONNODE_H
#include "happah/scene/Node.h"
#include "happah/scene/SimulationVisitor.h"

class SimulationNode : public Node
{
public:
    SimulationNode();

    void accept(SimulationVisitor& simulationVisitor);
    virtual void update(hpreal currentTime)= 0;
};

#endif // SIMULATIONNODE_H

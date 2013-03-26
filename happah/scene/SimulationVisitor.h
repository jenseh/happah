#ifndef SIMULATIONVISITOR_H
#define SIMULATIONVISITOR_H

class SimulationNode;

class SimulationVisitor
{
public:
    virtual void visit(SimulationNode& simulationNode) = 0;
};

#endif // SIMULATIONVISITOR_H

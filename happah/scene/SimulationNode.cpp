#include "SimulationNode.h"

SimulationNode::SimulationNode(): Node() { }

void SimulationNode::accept(SimulationVisitor& simulationVisitor) {
    simulationVisitor.visit(*this);
    Node::accept(simulationVisitor);
}

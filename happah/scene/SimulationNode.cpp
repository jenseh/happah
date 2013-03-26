#include "SimulationNode.h"

SimulationNode::SimulationNode(): Node(){ }

SimulationNode::~SimulationNode() {}

void SimulationNode::accept(SimulationVisitor& simulationVisitor) {
    simulationVisitor.visit(*this);
    Node::accept(simulationVisitor);
}


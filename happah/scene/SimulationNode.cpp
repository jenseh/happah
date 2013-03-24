#include "SimulationNode.h"

SimulationNode::SimulationNode(SceneManager* sceneManager): Node(), m_sceneManager(sceneManager) { }

SimulationNode::~SimulationNode() {}

void SimulationNode::accept(SimulationVisitor& simulationVisitor) {
    simulationVisitor.visit(*this);
    Node::accept(simulationVisitor);
}

#include "happah/simulations/Simulation.h"

Simulation::Simulation() {
	m_toolVisible = true;
}
Simulation::~Simulation() {}


bool Simulation::getToolVisibility()const {
	return m_toolVisible;
}

void Simulation::setToolVisibility(bool visible) {
	m_toolVisible = visible;
}

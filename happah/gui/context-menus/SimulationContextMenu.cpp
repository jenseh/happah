#include "SimulationContextMenu.h"

SimulationContextMenu::SimulationContextMenu(
	GUIManager& guiManager,
	QWidget* parent
) : ContextMenu(parent),
	m_guiManager(guiManager) {

}

SimulationContextMenu::~SimulationContextMenu(){}


void SimulationContextMenu::setSimulation(Simulation_ptr simulation) {
	m_simulation = simulation;
}

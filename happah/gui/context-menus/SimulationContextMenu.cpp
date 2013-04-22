#include "SimulationContextMenu.h"

SimulationContextMenu::SimulationContextMenu(
	GUIManager& guiManager,
	QWidget* parent
) : ContextMenu(parent),
	m_guiManager(guiManager) {

	QAction* changeToolVisibleAction = new QAction(tr("toggle tool visibility"), this);
	addAction(changeToolVisibleAction);
	connect(changeToolVisibleAction, SIGNAL(triggered()), this, SLOT(changeToolVisibility()));

}

SimulationContextMenu::~SimulationContextMenu(){}

void SimulationContextMenu::changeToolVisibility() {
	m_simulation->setToolVisibility(!m_simulation->getToolVisibility());
//	cout<<m_simulation->getToolVisibility()<<endl;
}

void SimulationContextMenu::setSimulation(Simulation_ptr simulation) {
	m_simulation = simulation;
}

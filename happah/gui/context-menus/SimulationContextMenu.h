#ifndef SIMULATIONCONTEXTMENU_H_
#define SIMULATIONCONTEXTMENU_H_

#include <QAction>
#include "happah/gui/GUIManager.h"
#include "happah/gui/context-menus/ContextMenu.h"
#include "happah/simulations/Simulation.h"


class SimulationContextMenu : public ContextMenu {
Q_OBJECT
public:
SimulationContextMenu(GUIManager& guiManager, QWidget* parent);
	~SimulationContextMenu();

	void setSimulation(Simulation_ptr simulation);

private:
	GUIManager& m_guiManager;
	Simulation_ptr m_simulation;

private slots:
	void changeToolVisibility();


};
#endif /* SIMULATIONCONTEXTMENU_H_ */

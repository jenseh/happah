#include "SimpleGearContextMenu.h"

SimpleGearContextMenu::SimpleGearContextMenu(
	GUIManager& guiManager,
	QWidget* parent
) : ContextMenu(parent),
	m_guiManager(guiManager) {

	QAction* useSimpleGearInSumulationAction = new QAction(tr("Use in simulation"), this);
	addAction(useSimpleGearInSumulationAction);
	connect(useSimpleGearInSumulationAction, SIGNAL(triggered()), this, SLOT(useSimpleGearInSumulation()));
}

SimpleGearContextMenu::~SimpleGearContextMenu(){}


void SimpleGearContextMenu::useSimpleGearInSumulation() {
	m_guiManager.useInSimulation(m_simpleGear, m_simpleGearMesh);
}

void SimpleGearContextMenu::setSimpleGear(SimpleGear_ptr simpleGear, TriangleMesh_ptr simpleGearMesh) {
	m_simpleGear = simpleGear;
	m_simpleGearMesh = simpleGearMesh;
}

#include "SimpleGearContextMenu.h"

SimpleGearContextMenu::SimpleGearContextMenu(
	GUIManager& guiManager,
	QWidget* parent
) : ContextMenu(parent),
	m_guiManager(guiManager) {

	QAction* useSimpleGearInSumulationAction = new QAction(tr("Use in simulation"), this);
	addAction(useSimpleGearInSumulationAction);
	connect(useSimpleGearInSumulationAction, SIGNAL(triggered()), this, SLOT(useSimpleGearInSumulation()));

	QAction* generateDiscAction = new QAction(tr("Generate disc"), this);
	addAction(generateDiscAction);
	connect(generateDiscAction, SIGNAL(triggered()), this, SLOT(generateDisc()));
}

SimpleGearContextMenu::~SimpleGearContextMenu(){}

void SimpleGearContextMenu::generateDisc() {
	m_guiManager.generateDisc(m_simpleGear);
}

void SimpleGearContextMenu::useSimpleGearInSumulation() {
	m_guiManager.useInSimulation(m_simpleGear, m_simpleGearMesh);
}

void SimpleGearContextMenu::setSimpleGear(SimpleGear_ptr simpleGear, TriangleMesh_ptr simpleGearMesh) {
	m_simpleGear = simpleGear;
	m_simpleGearMesh = simpleGearMesh;
}

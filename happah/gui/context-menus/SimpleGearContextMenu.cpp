#include "SimpleGearContextMenu.h"

SimpleGearContextMenu::SimpleGearContextMenu(
	GUIManager& guiManager,
	QWidget* parent
) : ContextMenu(parent),
	m_guiManager(guiManager) {

	QAction* createDiscGearGrind = new QAction(tr("Create disc gear grind"), this);
	addAction(createDiscGearGrind);
	connect(createDiscGearGrind, SIGNAL(triggered()), this, SLOT(createDiscGearGrind()));

	QAction* generateDiscAction = new QAction(tr("Generate disc"), this);
	addAction(generateDiscAction);
	connect(generateDiscAction, SIGNAL(triggered()), this, SLOT(generateDisc()));

}

SimpleGearContextMenu::~SimpleGearContextMenu(){}

void SimpleGearContextMenu::generateDisc() {
	m_guiManager.generateDisc(m_simpleGear);
}

void SimpleGearContextMenu::createDiscGearGrind() {
	// Make a copy for both threads
	SimpleGear_ptr simpleGear = SimpleGear_ptr(new SimpleGear(*m_simpleGear));
	m_guiManager.createDiscGearGrind(simpleGear);
}

void SimpleGearContextMenu::setSimpleGear(SimpleGear_ptr simpleGear, TriangleMesh_ptr simpleGearMesh) {
	m_simpleGear = simpleGear;
	m_simpleGearMesh = simpleGearMesh;
}

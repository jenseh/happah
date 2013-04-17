#include <memory>
#include <QAction>

#include "happah/gui/context-menus/InvoluteGearContextMenu.h"

InvoluteGearContextMenu::InvoluteGearContextMenu(
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

	QAction* createSimpleGearAction = new QAction(tr("Create simple gear"), this);
	addAction(createSimpleGearAction);
	connect(createSimpleGearAction, SIGNAL(triggered()), this, SLOT(createSimpleGear()));

}

InvoluteGearContextMenu::~InvoluteGearContextMenu() {}

void InvoluteGearContextMenu::createSimpleGear() {
	SimpleGear_ptr simpleGear = SimpleGear_ptr(m_involuteGear->toSimpleGear());
	m_guiManager.insert(simpleGear,HP_TRIANGLE_MESH);
}

void InvoluteGearContextMenu::generateDisc() {
	m_guiManager.generateDisc(m_involuteGear);
}

void InvoluteGearContextMenu::createDiscGearGrind() {
	SimpleGear_ptr simpleGear = SimpleGear_ptr(m_involuteGear->toSimpleGear());
	m_guiManager.createDiscGearGrind(simpleGear);
}

void InvoluteGearContextMenu::setInvoluteGear(InvoluteGear_ptr involuteGear, TriangleMesh_ptr involuteGearMesh) {
	m_involuteGear = involuteGear;
	m_involuteGearMesh = involuteGearMesh;
}

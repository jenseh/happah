#include <memory>
#include "happah/gui/context-menus/InvoluteGearContextMenu.h"

InvoluteGearContextMenu::InvoluteGearContextMenu(
	SimpleGearListener& simpleGearListener,
	QWidget *parent
) : ContextMenu(parent),
	m_simpleGearListener(simpleGearListener) {
	
	m_createSimpleGearAction = new QAction(tr("Create simple gear"), this);
	addAction(m_createSimpleGearAction);
	connect(m_createSimpleGearAction, SIGNAL(triggered()), this, SLOT(createSimpleGear()));
}

InvoluteGearContextMenu::~InvoluteGearContextMenu(){}

void InvoluteGearContextMenu::createSimpleGear() {
	SimpleGear_ptr simpleGear = SimpleGear_ptr(m_involuteGear->toSimpleGear());
	m_simpleGearListener.insert(simpleGear);
}

void InvoluteGearContextMenu::setInvoluteGear(InvoluteGear_ptr involuteGear) {
	m_involuteGear = involuteGear;
}
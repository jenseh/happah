#include <memory>
#include "happah/gui/context-menus/InvoluteGearContextMenu.h"

InvoluteGearContextMenu::InvoluteGearContextMenu(
	InvoluteGearListener& involuteGearListener,
	SimpleGearListener& simpleGearListener,
	QWidget *parent
) : ContextMenu(parent),
	m_involuteGearListener(involuteGearListener),
	m_simpleGearListener(simpleGearListener) {
	
	m_toSimpleGearAction = new QAction(tr("Create simple gear"), this);
	addAction(m_toSimpleGearAction);
	connect(m_toSimpleGearAction, SIGNAL(triggered()), this, SLOT(createSimpleGear()));
}

InvoluteGearContextMenu::~InvoluteGearContextMenu(){}

void InvoluteGearContextMenu::createSimpleGear() {
	SimpleGear_ptr simpleGear = SimpleGear_ptr(m_involuteGear->toSimpleGear());
	m_simpleGearListener.insert(simpleGear);
}

void InvoluteGearContextMenu::setInvoluteGear(InvoluteGear_ptr involuteGear) {
	m_involuteGear = involuteGear;
}
#include "happah/gui/context-menus/InvoluteGearContextMenu.h"

InvoluteGearContextMenu::InvoluteGearContextMenu(SimpleGearListener& simpleGearListener, QWidget *parent)
	: ContextMenu(parent), m_simpleGearListener(simpleGearListener) {
	
	m_toSimpleGearAction = new QAction(tr("Create simple gear"), this);
	addAction(m_toSimpleGearAction);
	connect(m_toSimpleGearAction, SIGNAL(triggered()), this, SLOT(createSimpleGear()));
	
	m_resetValuesAction = new QAction(tr("Reset values"), this);
	addAction(m_resetValuesAction);
	connect(m_resetValuesAction, SIGNAL(triggered()), this, SLOT(resetValues()));
}

InvoluteGearContextMenu::~InvoluteGearContextMenu(){}

void InvoluteGearContextMenu::createSimpleGear() {
	SimpleGear_ptr simpleGear = SimpleGear_ptr(m_involuteGear->toSimpleGear());
	m_simpleGearListener.insert(simpleGear);
}

void InvoluteGearContextMenu::resetValues() {
	
}
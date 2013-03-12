#include "happah/gui/context-menus/ContextMenuControl.h"

ContextMenuControl::ContextMenuControl(QWidget* parent) : QStackedWidget(parent),
	m_contextMenu(new ContextMenu(this)),
	m_involuteGearContextMenu(new InvoluteGearContextMenu(this)) {

	addWidget(m_contextMenu);
	addWidget(m_involuteGearContextMenu);
}

ContextMenuControl::~ContextMenuControl() {}

ContextMenu* ContextMenuControl::getContextMenu() {
	return m_contextMenu;
}

InvoluteGearContextMenu* ContextMenuControl::getInvoluteGearContextMenu() {
	return m_involuteGearContextMenu;
}


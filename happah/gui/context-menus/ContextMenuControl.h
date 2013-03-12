#ifndef CONTEXTMENUCONTROL_H
#define CONTEXTMENUCONTROL_H

#include <QStackedWidget>
#include <QWidget>
#include "happah/gui/context-menus/ContextMenu.h"
#include "happah/gui/context-menus/InvoluteGearContextMenu.h"

class ContextMenuControl : public QStackedWidget {
Q_OBJECT

public:
	ContextMenuControl(QWidget* parent = 0);
	~ContextMenuControl();

	ContextMenu* getContextMenu();
	InvoluteGearContextMenu* getInvoluteGearContextMenu();

private:
	ContextMenu* m_contextMenu;
	InvoluteGearContextMenu* m_involuteGearContextMenu;
};

#endif //CONTEXTMENUCONTROL_H
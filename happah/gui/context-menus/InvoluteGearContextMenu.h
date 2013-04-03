#ifndef INVOLUTE_GEAR_CONTEXT_MENU_H
#define INVOLUTE_GEAR_CONTEXT_MENU_H

#include <QAction>

#include "happah/geometries/gears/InvoluteGear.h"
#include "happah/gui/context-menus/ContextMenu.h"
#include "happah/gui/GUIManager.h"

class InvoluteGearContextMenu : public ContextMenu {
Q_OBJECT

public:
	InvoluteGearContextMenu(GUIManager& guiManager, QWidget* parent);
	~InvoluteGearContextMenu();

	void setInvoluteGear(InvoluteGear_ptr involuteGear);

private:
	GUIManager& m_guiManager;
	InvoluteGear_ptr m_involuteGear;

private slots:
	void createSimpleGear();
	void generateDisc();

};
#endif // INVOLUTE_GEAR_CONTEXT_MENU_H

#ifndef INVOLUTE_GEAR_CONTEXT_MENU_H
#define INVOLUTE_GEAR_CONTEXT_MENU_H

#include "happah/geometries/gears/InvoluteGear.h"
#include "happah/gui/context-menus/ContextMenu.h"
#include "happah/gui/GUIManager.h"

class InvoluteGearContextMenu : public ContextMenu {
Q_OBJECT

public:
	InvoluteGearContextMenu(GUIManager& guiManager, QWidget* parent);
	~InvoluteGearContextMenu();

	void setInvoluteGear(InvoluteGear_ptr involuteGear, TriangleMesh_ptr involuteGearMesh);

private:
	GUIManager& m_guiManager;
	InvoluteGear_ptr m_involuteGear;
	TriangleMesh_ptr m_involuteGearMesh;

private slots:
	void createSimpleGear();
	void generateDisc();
	void createDiscGearGrind();

};
#endif // INVOLUTE_GEAR_CONTEXT_MENU_H

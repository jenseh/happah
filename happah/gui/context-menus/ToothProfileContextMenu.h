#ifndef TOOTHPROFILECONTEXTMENU_H
#define TOOTHPROFILECONTEXTMENU_H

#include "happah/geometries/gears/ToothProfile.h"
#include "happah/gui/context-menus/ContextMenu.h"
#include "happah/gui/GUIManager.h"

class ToothProfileContextMenu : public ContextMenu {
Q_OBJECT

public:
	ToothProfileContextMenu(GUIManager& guiManager, QWidget* parent);
	~ToothProfileContextMenu();

	void setToothProfile(ToothProfile_ptr toothProfile);

private:
	GUIManager& m_guiManager;
	ToothProfile_ptr m_toothProfile;

private slots:
	void createSimpleGear();
	void newBSplineCurve();
	void createMatingGear();
};

#endif // TOOTHPROFILECONTEXTMENU_H
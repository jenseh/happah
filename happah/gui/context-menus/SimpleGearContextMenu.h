#ifndef SIMPLEGEARCONTEXTMENU_H_
#define SIMPLEGEARCONTEXTMENU_H_

#include <QAction>
#include "happah/geometries/SimpleGear.h"
#include "happah/gui/GUIManager.h"
#include "happah/gui/context-menus/ContextMenu.h"

class SimpleGearContextMenu : public ContextMenu {
Q_OBJECT
public:
SimpleGearContextMenu(GUIManager& guiManager, QWidget* parent);
	~SimpleGearContextMenu();

	void setDisc(SimpleGear_ptr simpleGear);

private:
	GUIManager& m_guiManager;
	SimpleGear_ptr m_simpleGear;

private slots:
	void useSimpleGearInSumulation();

};


#endif /* SIMPLEGEARCONTEXTMENU_H_ */

#ifndef INVOLUTEGEARCONTEXTMENU_H
#define INVOLUTEGEARCONTEXTMENU_H

#include <QAction>
#include "happah/geometries/InvoluteGear.h"
#include "happah/gui/context-menus/ContextMenu.h"
#include "happah/gui/forms/SimpleGearListener.h"

class InvoluteGearContextMenu : public ContextMenu {
Q_OBJECT

public:
	InvoluteGearContextMenu(SimpleGearListener& simpleGearListener, QWidget *parent);
	~InvoluteGearContextMenu();

private:
	InvoluteGear* m_involuteGear;
	SimpleGearListener& m_simpleGearListener;

	QAction* m_resetValuesAction;
	QAction* m_toSimpleGearAction;

private slots:
	void createSimpleGear();
	void resetValues();

};
#endif //INVOLUTEGEARCONTEXTMENU_H

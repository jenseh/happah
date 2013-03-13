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

	void setInvoluteGear(InvoluteGear_ptr involuteGear);

private:
	InvoluteGear_ptr m_involuteGear;
	SimpleGearListener& m_simpleGearListener;
	QAction* m_createSimpleGearAction;

private slots:
	void createSimpleGear();

};
#endif //INVOLUTEGEARCONTEXTMENU_H

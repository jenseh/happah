#ifndef INVOLUTEGEARCONTEXTMENU_H
#define INVOLUTEGEARCONTEXTMENU_H

#include <QAction>
#include "happah/geometries/InvoluteGear.h"
#include "happah/gui/context-menus/ContextMenu.h"
#include "happah/gui/forms/InvoluteGearListener.h"
#include "happah/gui/forms/SimpleGearListener.h"

class InvoluteGearContextMenu : public ContextMenu {
Q_OBJECT

public:
	InvoluteGearContextMenu(InvoluteGearListener& involuteGearListener, SimpleGearListener& simpleGearListener, QWidget *parent);
	~InvoluteGearContextMenu();

	void setInvoluteGear(InvoluteGear_ptr involuteGear);

private:
	InvoluteGear_ptr m_involuteGear;
	InvoluteGearListener& m_involuteGearListener;
	SimpleGearListener& m_simpleGearListener;
	QAction* m_toSimpleGearAction;

private slots:
	void createSimpleGear();

};
#endif //INVOLUTEGEARCONTEXTMENU_H

#ifndef BSPLINECURVECONTEXTMENU_H
#define BSPLINECURVECONTEXTMENU_H

#include "happah/gui/context-menus/ContextMenu.h"
#include "happah/gui/GUIManager.h"

class BSplineCurveContextMenu : public ContextMenu {
Q_OBJECT

public:
	BSplineCurveContextMenu(GUIManager& guiManager, QWidget* parent);
	~BSplineCurveContextMenu();

	void setBSplineCurve(BSplineCurve_ptr bSplineCurve);

private:
	GUIManager& m_guiManager;
	BSplineCurve_ptr m_curve;

private slots:
	void createGearToothOfCurve();

};

#endif // BSPLINECURVECONTEXTMENU_H
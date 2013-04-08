#ifndef PLANE_CONTEXT_MENU_H
#define PLANE_CONTEXT_MENU_H

#include <QAction>
#include "happah/geometries/Plane.h"
#include "happah/gui/GUIManager.h"
#include "happah/gui/context-menus/ContextMenu.h"

class PlaneGUIStateNode;
typedef std::shared_ptr<PlaneGUIStateNode> PlaneGUIStateNode_ptr;

class PlaneContextMenu : public ContextMenu {
Q_OBJECT
public:
	PlaneContextMenu(GUIManager& guiManager, QWidget* parent);
	~PlaneContextMenu();

	void setPlane(Plane_ptr plane);

private:
	GUIManager& m_guiManager;
	Plane_ptr m_plane;

private slots:
	void setPlaneForBSpline();

};


#endif /* PLANE_CONTEXT_MENU_H */

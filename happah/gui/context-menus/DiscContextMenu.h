#ifndef DISCCONTEXTMENU_H_
#define DISCCONTEXTMENU_H_

#include <QAction>
#include "happah/geometries/Disc.h"
#include "happah/gui/GUIManager.h"
#include "happah/gui/context-menus/ContextMenu.h"


class DiscContextMenu : public ContextMenu {
Q_OBJECT
public:
	DiscContextMenu(GUIManager& guiManager, QWidget* parent);
	~DiscContextMenu();

	void setDisc(Disc_ptr disc, TriangleMesh_ptr discMesh);

private:
	GUIManager& m_guiManager;
	Disc_ptr m_disc;
	TriangleMesh_ptr m_discMesh;

private slots:
	void useDiscInSumulation();

};

#endif /* DISCCONTEXTMENU_H_ */
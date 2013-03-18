#ifndef DISCCONTEXTMENU_H_
#define DISCCONTEXTMENU_H_

#include <QAction>
#include "happah/geometries/Disc.h"
#include "happah/gui/GUIManager.h"
#include "happah/gui/context-menus/ContextMenu.h"

class DiscGUIStateNode;
typedef std::shared_ptr<DiscGUIStateNode> DiscGUIStateNode_ptr;

class DiscContextMenu : public ContextMenu {
Q_OBJECT
public:
	DiscContextMenu(GUIManager& guiManager, QWidget* parent);
	~DiscContextMenu();

	void setDisc(Disc_ptr disc);

private:
	GUIManager& m_guiManager;
	Disc_ptr m_disc;
	DiscGUIStateNode_ptr m_guiStateNode;

private slots:
	void useDiscInSumulation();

};

#endif /* DISCCONTEXTMENU_H_ */

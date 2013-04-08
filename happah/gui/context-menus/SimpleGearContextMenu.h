#ifndef SIMPLEGEARCONTEXTMENU_H_
#define SIMPLEGEARCONTEXTMENU_H_

#include <QAction>
#include "happah/geometries/gears/SimpleGear.h"
#include "happah/geometries/DiscGenerator.h"
#include "happah/gui/GUIManager.h"
#include "happah/gui/context-menus/ContextMenu.h"
#include "happah/simulations/DiscGearGrind.h"

class SimpleGearGUIStateNode;
typedef std::shared_ptr<SimpleGearGUIStateNode> SimpleGearGUIStateNode_ptr;

class SimpleGearContextMenu : public ContextMenu {
Q_OBJECT
public:
SimpleGearContextMenu(GUIManager& guiManager, QWidget* parent);
	~SimpleGearContextMenu();

	void setSimpleGear(SimpleGear_ptr simpleGear, TriangleMesh_ptr simpleGearMesh);

private:
	GUIManager& m_guiManager;
	SimpleGear_ptr m_simpleGear;
	TriangleMesh_ptr m_simpleGearMesh;

private slots:
	void generateDisc();
	void createDiscGearGrind();

};


#endif /* SIMPLEGEARCONTEXTMENU_H_ */

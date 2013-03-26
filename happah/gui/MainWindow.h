#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QKeyEvent>
#include <QMainWindow>

#include "happah/gui/GUIManager.h"
#include "happah/gui/SceneGraphExplorerListener.h"
#include "happah/gui/SceneGraphExplorerPanel.h"
#include "happah/gui/ViewportListener.h"
#include "happah/gui/context-menus/ContextMenu.h"
#include "happah/gui/context-menus/DiscContextMenu.h"
#include "happah/gui/context-menus/SimpleGearContextMenu.h"

class DrawManager;
class InvoluteGearContextMenu;
class ToolPanel;
class MainWindow: public QMainWindow {
Q_OBJECT

public:
	MainWindow(GUIManager& guiManager, ViewportListener& viewportListener, SceneGraphExplorerListener& sceneGraphExplorerListener, DrawManager& drawManager);
	virtual ~MainWindow();

	SceneGraphExplorerPanel* getSceneGraphExplorerPanel();
	ToolPanel* getToolPanel();

	ContextMenu* getDefaultContextMenu();
	DiscContextMenu* getDiscContextMenu();
	InvoluteGearContextMenu* getInvoluteGearContextMenu();
	SimpleGearContextMenu* getSimpleGearContextMenu();
	SimulationContextMenu* getSimulationContextMenu();

protected:
	void keyPressEvent(QKeyEvent* event);

private:
	static const int DEFAULT_WINDOW_HEIGHT = 800;
	static const int DEFAULT_WINDOW_WIDTH = 1200;

	SceneGraphExplorerPanel* m_sceneGraphExplorerPanel;
	ToolPanel* m_toolPanel;

	ContextMenu* m_defaultContextMenu;
	DiscContextMenu* m_discContextMenu;
	InvoluteGearContextMenu* m_involuteGearContextMenu;
	SimpleGearContextMenu* m_simpleGearContextMenu;
	SimulationContextMenu* m_simulationContextMenu;


};

#include "happah/gui/ToolPanel.h"

#endif

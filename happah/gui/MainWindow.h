#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QKeyEvent>
#include <QMainWindow>

#include "happah/gui/context-menus/ContextMenu.h"
#include "happah/gui/SceneGraphExplorerListener.h"

class DrawManager;
class GUIManager;
class InvoluteGearContextMenu;
class SceneGraphExplorerPanel;
class ToolPanel;
class MainWindow: public QMainWindow {
Q_OBJECT

public:
	MainWindow(GUIManager& guiManager, SceneGraphExplorerListener& sceneGraphExplorerListener, DrawManager& drawManager);
	virtual ~MainWindow();

	SceneGraphExplorerPanel* getSceneGraphExplorerPanel();
	ToolPanel* getToolPanel();

	ContextMenu* getDefaultContextMenu();
	InvoluteGearContextMenu* getInvoluteGearContextMenu();

protected:
	void keyPressEvent(QKeyEvent* event);

private:
	static const int DEFAULT_WINDOW_HEIGHT = 800;
	static const int DEFAULT_WINDOW_WIDTH = 1200;

	SceneGraphExplorerPanel* m_sceneGraphExplorerPanel;
	ToolPanel* m_toolPanel;

	ContextMenu* m_defaultContextMenu;
	InvoluteGearContextMenu* m_involuteGearContextMenu;

};

#include "happah/gui/ToolPanel.h"

#endif

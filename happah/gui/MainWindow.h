#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QKeyEvent>
#include <QMainWindow>

#include "happah/gui/GUIManager.h"
#include "happah/gui/SceneGraphExplorerListener.h"
#include "happah/gui/SceneGraphExplorerPanel.h"
#include "happah/gui/Viewport3DListener.h"
#include "happah/gui/context-menus/ContextMenu.h"

class DrawManager;
class InvoluteGearContextMenu;
class ToolPanel;
class MainWindow: public QMainWindow {
Q_OBJECT

public:
	MainWindow(GUIManager& guiManager, Viewport3DListener& viewport3DListener, SceneGraphExplorerListener& sceneGraphExplorerListener, DrawManager& drawManager);
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

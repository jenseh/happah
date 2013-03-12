#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QKeyEvent>
#include <QMainWindow>

#include "happah/gui/SceneGraphExplorerListener.h"
#include "happah/gui/context-menus/ContextMenuControl.h"

class DrawManager;
class GUIManager;
class SceneGraphExplorerPanel;
class ToolPanel;
class MainWindow: public QMainWindow {
Q_OBJECT

public:
	MainWindow(GUIManager& guiManager, SceneGraphExplorerListener& sceneGraphExplorerListener, DrawManager& drawManager);
	virtual ~MainWindow();

	ContextMenuControl* getContextMenu();
	SceneGraphExplorerPanel* getSceneGraphExplorerPanel();
	ToolPanel* getToolPanel();

protected:
	void keyPressEvent(QKeyEvent* event);

private:
	static const int DEFAULT_WINDOW_HEIGHT = 800;
	static const int DEFAULT_WINDOW_WIDTH = 1200;

	ContextMenuControl* m_contextMenuControl;
	SceneGraphExplorerPanel* m_sceneGraphExplorerPanel;
	ToolPanel* m_toolPanel;

};

#include "happah/gui/ToolPanel.h"

#endif

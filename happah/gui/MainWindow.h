#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QKeyEvent>
#include <QMainWindow>

#include "happah/gui/GUIManager.h"
#include "happah/gui/SceneGraphExplorerListener.h"
#include "happah/gui/SceneGraphExplorerPanel.h"
#include "happah/gui/ViewportListener.h"
#include "happah/gui/context-menus/BSplineCurveContextMenu.h"
#include "happah/gui/context-menus/ContextMenu.h"
#include "happah/gui/context-menus/DiscContextMenu.h"
#include "happah/gui/context-menus/PlaneContextMenu.h"
#include "happah/gui/context-menus/SimpleGearContextMenu.h"
#include "happah/gui/context-menus/ToothProfileContextMenu.h"

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

	BSplineCurveContextMenu* getBSplineCurveContextMenu();
	ContextMenu* getDefaultContextMenu();
	DiscContextMenu* getDiscContextMenu();
	InvoluteGearContextMenu* getInvoluteGearContextMenu();
	PlaneContextMenu* getPlaneContextMenu();
	SimpleGearContextMenu* getSimpleGearContextMenu();
	SimulationContextMenu* getSimulationContextMenu();
	ToothProfileContextMenu* getToothProfileContextMenu();
	TriangleMeshContextMenu* getTriangleMeshContextMenu();

protected:
	void keyPressEvent(QKeyEvent* event);

private:
	static const int DEFAULT_WINDOW_HEIGHT = 800;
	static const int DEFAULT_WINDOW_WIDTH = 1200;

	BSplineCurveContextMenu* m_bSplineCurveContextMenu;
	ContextMenu* m_defaultContextMenu;
	DiscContextMenu* m_discContextMenu;
	GUIManager& m_guiManager;
	InvoluteGearContextMenu* m_involuteGearContextMenu;
	PlaneContextMenu* m_planeContextMenu;
	SceneGraphExplorerPanel* m_sceneGraphExplorerPanel;
	SimpleGearContextMenu* m_simpleGearContextMenu;
	SimulationContextMenu* m_simulationContextMenu;
	ToolPanel* m_toolPanel;
	ToothProfileContextMenu* m_toothProfileContextMenu;
	TriangleMeshContextMenu* m_triangleMeshContextMenu;

private slots:
	void handleImportActionTriggeredEvent();

};

#include "happah/gui/ToolPanel.h"

#endif

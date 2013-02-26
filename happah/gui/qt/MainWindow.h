#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QKeyEvent>
#include <QListWidget>
#include <QMainWindow>
#include <QMenu>

#include "happah/HappahTypes.h"
#include "happah/gui/gl/DrawManager.h"
#include "happah/gui/qt/ComponentList.h"
#include "happah/gui/qt/EditorScene.h"
#include "happah/gui/qt/EditorSceneManager.h"
#include "happah/gui/qt/SceneManager3D.h"
#include "happah/gui/qt/ToolSelector.h"
#include "happah/scene/SceneManager.h"

class MainWindow: public QMainWindow {
Q_OBJECT

public:
	MainWindow(SceneManager& sceneManager, DrawManager& drawManager);
	virtual ~MainWindow();

	ComponentList* getComponentList();
	void keyPressEvent(QKeyEvent *event);

private:
	static const int DEFAULT_HEIGHT = 768;
	static const int DEFAULT_WIDTH = 1024;

	void createContainer();
	void createTools();

	ComponentList* m_componentList;
	QTabWidget* m_tabs;
	SceneManager& m_sceneManager;
	ToolSelector* m_toolSelector;
	QMenu* m_viewMenu;

	//2D components:
	QGraphicsView* m_view2D;
	EditorScene* m_scene;
	EditorSceneManager* m_editorSceneManager;
	//3D components:
	SceneManager3D* m_sceneManager3D;

private slots:
	void scaleView2D(int);
	void changeView2DTo(hpvec2 min, hpvec2 max);

};

#endif

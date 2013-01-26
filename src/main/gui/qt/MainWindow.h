#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QMainWindow>
#include <QKeyEvent>
#include <QMenu>
#include <QListWidget>

#include "ToolSelector.h"
#include "ComponentList.h"
#include "EditorScene.h"
#include "EditorSceneManager.h"
#include "SceneManager3D.h"

class MainWindow: public QMainWindow {
Q_OBJECT

public:
	static const int DEFAULT_WIDTH = 1024;
	static const int DEFAULT_HEIGHT = 768;

	MainWindow();
	virtual ~MainWindow();
	void keyPressEvent(QKeyEvent *event);

	ComponentList* getComponentList();

private:
	void createTools();
	void createContainer();
	//void createDockWindows();

	QMenu* m_viewMenu;
	ComponentList* m_componentList;
	QTabWidget* m_tabs;
	ToolSelector* m_toolSelector;
	//2D components:
	EditorScene* m_scene;
	EditorSceneManager* m_editorSceneManager;
	//3D components:
	SceneManager3D* m_sceneManager3D;

};

#endif

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
#include "../../core/SceneManager.h"

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

	QMenu* viewMenu_;
	ComponentList* m_componentList;
	ToolSelector* toolSelector_;
	EditorScene* scene_;
	EditorSceneManager* m_editorSceneManager;
    SceneManager* sceneManager;
    QTabWidget *m_tabs;
};

#endif

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QMainWindow>
#include <QKeyEvent>
#include <QMenu>
#include <QListWidget>

#include "ToolSelector.h"
#include "ComponentContainer.h"
#include "EditorScene.h"
#include "core/SceneManager.h"

class MainWindow: public QMainWindow {
Q_OBJECT

public:
	static const int DEFAULT_WIDTH = 1024;
	static const int DEFAULT_HEIGHT = 768;

	MainWindow();
	virtual ~MainWindow();
	void keyPressEvent(QKeyEvent *event);

	ComponentContainer* getComponentContainer();

private:
	void createTools();
	void createContainer();
	//void createDockWindows();

	QMenu* viewMenu_;
	ComponentContainer* componentContainer_;
	ToolSelector* toolSelector_;
	EditorScene* scene_;
    SceneManager* sceneManager;
};

#endif

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QMainWindow>
#include <QKeyEvent>
#include <QMenu>
#include <QListWidget>

#include "ToolSelector.h"
#include "ComponentContainer.h"
#include "EditorScene.h"

class MainWindow : public QMainWindow {
Q_OBJECT

private:
	QMenu* viewMenu;
	ComponentContainer* componentContainer;
	ToolSelector* toolSelector;
	EditorScene* scene;

public:
	static const int DEFAULT_WIDTH = 1024;
	static const int DEFAULT_HEIGHT = 768;

	MainWindow();
	virtual ~MainWindow();
	void keyPressEvent(QKeyEvent *event);

private:
	void createTools();
	void createContainer();
	//void createDockWindows();
};

#endif

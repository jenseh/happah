#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QKeyEvent>
#include <QMainWindow>

#include "happah/gui/DrawManager.h"
#include "happah/scene/SceneManager.h"

class MainWindow: public QMainWindow {
Q_OBJECT

public:
	MainWindow(SceneManager& sceneManager, DrawManager& drawManager);
	virtual ~MainWindow();

protected:
	void keyPressEvent(QKeyEvent* event);

private:
	static const int DEFAULT_WINDOW_HEIGHT = 800;
	static const int DEFAULT_WINDOW_WIDTH = 1200;

};

#endif

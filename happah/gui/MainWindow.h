#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QKeyEvent>
#include <QMainWindow>

#include "happah/gui/forms/InvoluteGearForm.h"

class DrawManager;
class GUIManager;
class SceneManager;
class ToolPanel;
class MainWindow: public QMainWindow {
Q_OBJECT

public:
	MainWindow(SceneManager& sceneManager, GUIManager& guiManager, DrawManager& drawManager);
	virtual ~MainWindow();

	InvoluteGearForm* getInvoluteGearForm();

protected:
	void keyPressEvent(QKeyEvent* event);

private:
	static const int DEFAULT_WINDOW_HEIGHT = 800;
	static const int DEFAULT_WINDOW_WIDTH = 1200;

	ToolPanel* m_toolPanel;

};

#include "happah/gui/ToolPanel.h"

#endif

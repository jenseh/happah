#ifndef HAPPAH_H_
#define HAPPAH_H_

#include <QApplication>

#include "happah/scene/SceneManager.h"
#include "happah/gui/DrawManager.h"
#include "happah/gui/MainWindow.h"

class Happah: public QApplication {
Q_OBJECT

public:
	Happah(int& argc, char** argv);
	virtual ~Happah();

private:
	SceneManager m_sceneManager;
	DrawManager m_drawManager;
	MainWindow m_mainWindow;

};

#endif

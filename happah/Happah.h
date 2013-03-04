#ifndef HAPPAH_H_
#define HAPPAH_H_

#include <QApplication>

#include "happah/scene/SceneManager.h"
#include "happah/gui/GUIManager.h"

class Happah : public QApplication {
Q_OBJECT

public:
	Happah(int& argc, char** argv);
	~Happah();

	int exec();

private:
	SceneManager m_sceneManager;
	GUIManager m_guiManager;

};

#endif

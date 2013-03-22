#ifndef HP_H_
#define HP_H_

#include <QApplication>

#include "happah/scene/SceneManager.h"
#include "happah/gui/DefaultGUIManager.h"

class Happah : public QApplication {
Q_OBJECT

public:
	Happah(int& argc, char** argv);
	~Happah();

	int exec();

private:
	SceneManager_ptr m_sceneManager;
	DefaultGUIManager m_defaultGUIManager;

};

#endif

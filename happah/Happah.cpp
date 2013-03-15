#include "happah/Happah.h"

Happah::Happah(int& argc, char** argv) 
	: QApplication(argc, argv), m_sceneManager(new SceneManager()), m_defaultGUIManager(m_sceneManager) {}

Happah::~Happah() {}

int Happah::exec() {
	if(m_defaultGUIManager.init())
		return QApplication::exec();
	else
		return 1;
}

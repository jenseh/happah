#include "happah/Happah.h"

Happah::Happah(int& argc, char** argv) 
	: QApplication(argc, argv), m_guiManager(m_sceneManager) {}

Happah::~Happah() {}

int Happah::exec() {
	if(m_guiManager.init())
		return QApplication::exec();
	else
		return 1;
}

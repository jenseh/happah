#include <GL/glew.h>
#include <QGLContext>
#include <QGLFormat>

#include "happah/Happah.h"
#include "happah/gui/MainWindow.h"

Happah::Happah(int& argc, char** argv) 
	: QApplication(argc, argv), m_drawManager(m_sceneManager), m_mainWindow(m_sceneManager, m_drawManager) {
	if (!m_drawManager.initGL()) {
		fprintf(stderr, "Draw manager initialization failed.\n");
		return;
	}
	m_mainWindow.show();
}

Happah::~Happah() {}


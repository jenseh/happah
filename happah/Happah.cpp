#include "happah/Happah.h"
#include "happah/gui/qt/MainWindow.h"

Happah::Happah(int& argc, char** argv) : QApplication(argc, argv) {
	m_window.show();
}

Happah::~Happah() {}


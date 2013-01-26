#include "Happah.h"
#include "gui/qt/MainWindow.h"

Happah::Happah(int & argc, char ** argv) :
		QApplication(argc, argv) {
	m_window.show();
}

Happah::~Happah() {
}


#include "Happah.h"
#include "gui/qt/MainWindow.h"

Happah::Happah(int & argc, char ** argv) :
		QApplication(argc, argv) {
	window_.show();
}

Happah::~Happah() {
}


#include "Happah.h"
#include "MainWindow.h"

Happah::Happah(int & argc, char ** argv) :
		QApplication(argc, argv) {
	window_.show();
}

Happah::~Happah() {
}


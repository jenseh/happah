#ifndef HAPPAH_H_
#define HAPPAH_H_

#include <QApplication>

#include "MainWindow.h"

class Happah: public QApplication {
Q_OBJECT
private:
	MainWindow _window;
public:
	Happah(int & argc, char ** argv);
	virtual ~Happah();
};

#endif

#ifndef HAPPAH_H_
#define HAPPAH_H_

#include <QApplication>

#include "happah/gui/qt/MainWindow.h"

class Happah: public QApplication {
Q_OBJECT

public:
	Happah(int & argc, char ** argv);
	virtual ~Happah();

private:
	MainWindow m_window;

};

#endif

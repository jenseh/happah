#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QMainWindow>

class MainWindow: public QMainWindow {
Q_OBJECT
public:
	static const int DEFAULT_WIDTH = 1024;
	static const int DEFAULT_HEIGHT = 768;

	MainWindow();
	virtual ~MainWindow();
};

#endif

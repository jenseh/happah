#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include "render.h"
#include "menu.h"

int main(int argc,char *argv[]) {

	QApplication app(argc,argv);
	QWidget window;
	window.resize(800,600);
	window.setWindowTitle("Happah Geometry Module");

	MenuClass myMenu(&window);
	myMenu.setGeometry(0,0,100,200);




	RenderClass render(&window);
	render.setGeometry(0,0,600,600);




	window.show();
	return app.exec();


}

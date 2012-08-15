#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include "render.h"

int main(int argc,char *argv[]) {

	QApplication app(argc,argv);
	QWidget window;
	window.resize(800,600);
	window.setWindowTitle("Happah Geometry Module");

	QPushButton create("Create Circle", &window);


	create.setGeometry(600,0,200,40);
	RenderClass render(&window);


	render.setGeometry(0,0,600,600);


	render.show();
	return app.exec();


}

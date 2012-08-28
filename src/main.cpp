
#include <QApplication>
#include <QtGui>
#include <QWidget>
#include "happah.h"
#include "render.h"
#include "menu.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Happah window;

    window.resize(800,600);
    window.setWindowTitle("QT OpenGL Project");
    RenderClass render(&window);
    MenuClass menu(&window);

    render.setGeometry(0,0,600,600);
    menu.setGeometry(600,0,200,600);
    window.show();
    return app.exec();
}

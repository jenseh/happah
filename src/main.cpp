
#include <QApplication>
#include <QtGui>

#include <QWidget>
#include <QGLWidget>
#include <QGLBuffer>
#include <QGLFormat>
#include "happah.h"
#include "render.h"
#include "menu.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Happah window;
    window.resize(800,600);
    window.setWindowTitle("Happah Project");


    // Setup QGL Format for Core profile
    QGLFormat glFormat;
    glFormat.setVersion(4,2);
    glFormat.setProfile(QGLFormat::CompatibilityProfile);
    glFormat.setSampleBuffers(true); // multisampling
    glFormat.setDoubleBuffer(true);
    glFormat.setDepth(true);

    RenderClass render(glFormat,&window);
    MenuClass menu(&window);

    render.setGeometry(0,0,600,600);
    menu.setGeometry(600,0,200,600);
    window.show();
    return app.exec();
}

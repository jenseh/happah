
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
    window.resize(1024,768);
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

    render.setGeometry(0,0,1024,768);
    menu.setGeometry(1024,0,0,0);
    window.show();
    return app.exec();
}

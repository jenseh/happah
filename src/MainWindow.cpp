#include <QGLFormat>

#include "MainWindow.h"
#include "Viewport3D.h"

MainWindow::MainWindow() {
	resize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	setWindowTitle("Happah");

	QGLFormat glFormat;
	glFormat.setVersion(4, 2);
	glFormat.setProfile(QGLFormat::CompatibilityProfile);
	glFormat.setSampleBuffers(true);
	glFormat.setDoubleBuffer(true);
	glFormat.setDepth(true);

	Viewport3D* viewport3D = new Viewport3D(glFormat, this);
	viewport3D->setGeometry(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
	setCentralWidget(viewport3D);
}

MainWindow::~MainWindow() {
}


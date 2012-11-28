//#include <QGLFormat>
#include <QApplication>
#include <QMenuBar>
#include <QDockWidget>
#include <QTabWidget>
#include <QWidget>
#include <QGraphicsView>

#include "MainWindow.h"
#include "SplineTool.h"
#include "BSplineTool.h"
#include "qt/qgl/QglViewport3D.h"
#include "Component.h"

MainWindow::MainWindow() {
	resize(DEFAULT_WIDTH + 470, DEFAULT_HEIGHT + 70);
	setWindowTitle("Happah");

	QAction *quitAction = new QAction("&Quit", this);
	quitAction->setShortcut(tr("CTRL+Q"));

	QMenu *file;
	file = menuBar()->addMenu("&File");
	file->addAction(quitAction);
	connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

	viewMenu_ = menuBar()->addMenu("&View");

	QGLFormat glFormat;
	glFormat.setVersion(3, 3);
	glFormat.setProfile(QGLFormat::CompatibilityProfile);
	glFormat.setSampleBuffers(true);
	glFormat.setDoubleBuffer(true);
	glFormat.setDepth(true);

	QTabWidget *tabs = new QTabWidget(this);

	// Setting up OpenGl 3D-viewport
	QWidget* viewportWidget = new QWidget();
	QglViewPort3D* viewport3D = new QglViewPort3D(glFormat, viewportWidget,
			this);
	viewport3D->setGeometry(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
	tabs->addTab(viewportWidget, "3D-View");

	// Setting up 2D Editor
	scene_ = new EditorScene(this);
	scene_->setSceneRect(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
	QGraphicsView* view2D = new QGraphicsView(scene_);
	tabs->addTab(view2D, "2D-View");

	setCentralWidget(tabs);

	createTools();
	createContainer();

	connect(toolSelector_, SIGNAL(emitComponent(Component*)),
			componentContainer_, SLOT(addComponent(Component*)));

//createDockWindows();
}

void MainWindow::createTools() {

// Tool selector
	QDockWidget* dock = new QDockWidget(tr("Tools"), this);

	toolSelector_ = new ToolSelector(dock);

	SplineTool* splineTool = new SplineTool();
	toolSelector_->addTool(splineTool);

	BSplineTool* bSplineTool = new BSplineTool();
	toolSelector_->addTool(bSplineTool);

	dock->setWidget(toolSelector_);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	addDockWidget(Qt::LeftDockWidgetArea, dock);
	viewMenu_->addAction(dock->toggleViewAction());

// Option docking-window to control current tool
	dock = new QDockWidget(tr("Tool Settings"), this);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	addDockWidget(Qt::LeftDockWidgetArea, dock);
	viewMenu_->addAction(dock->toggleViewAction());
	dock->setWidget(toolSelector_->getSettingsWidget());

}

void MainWindow::createContainer() {

// List of objects in scene
	QDockWidget* dock = new QDockWidget(tr("Objects"), this);
	componentContainer_ = new ComponentContainer(scene_, dock);
	dock->setWidget(componentContainer_);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	addDockWidget(Qt::RightDockWidgetArea, dock);
	viewMenu_->addAction(dock->toggleViewAction());
}

MainWindow::~MainWindow() {
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
	if (event->key() == Qt::Key_Escape) {
		qApp->quit();
	}
}

ComponentContainer* MainWindow::getComponentContainer() {
	return componentContainer_;
}

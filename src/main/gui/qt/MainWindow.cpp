#include <QApplication>
#include <QMenuBar>
#include <QDockWidget>
#include <QTabWidget>
#include <QWidget>
#include <QGraphicsView>

#include "MainWindow.h"
#include "SplineTool.h"
#include "BSplineTool.h"
#include "InvoluteSpurGearTool.h"
#include "../../core/SceneManager.h"
#include "../gl/GlViewport3D.h"

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

    m_tabs = new QTabWidget(this);

    // Setting up logic
    SceneManager *sceneManager = new SceneManager();

	// Setting up OpenGl 3D-viewport
	QWidget* viewportWidget = new QWidget();
	GlViewport3D* viewport3D = new GlViewport3D(sceneManager, glFormat, viewportWidget,
			this);
	viewport3D->setGeometry(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    m_tabs->addTab(viewportWidget, "3D-View");

	// Setting up 2D Editor
	scene_ = new EditorScene(this);
	scene_->setSceneRect(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
	QGraphicsView* view2D = new QGraphicsView(scene_);
    m_tabs->addTab(view2D, "2D-View");

	setCentralWidget(m_tabs);
	createTools();
	createContainer();

	m_sceneManager3D = new SceneManager3D(sceneManager, m_componentList);
	m_editorSceneManager = new EditorSceneManager( scene_, m_componentList );
	//3D scene
	connect(toolSelector_, SIGNAL(emitDrawable(Drawable*)),
	        m_sceneManager3D, SLOT(addDrawable(Drawable*)));
	connect(toolSelector_, SIGNAL(changed()),
			m_sceneManager3D, SLOT(update()));
	connect(m_componentList, SIGNAL(deleteCurrent()),
	        m_sceneManager3D, SLOT(deleteCurrentDrawable()));
	//editor scene
	connect( scene_, SIGNAL(rightClickedAt( QPointF )),
	        toolSelector_, SLOT(rightClickAt( QPointF )) );
	connect( scene_, SIGNAL(leftClickedAt( QPointF )),
	        toolSelector_, SLOT(leftClickAt( QPointF )) );
	connect(toolSelector_, SIGNAL(emitDrawable( Drawable2D* )),
	        m_editorSceneManager, SLOT(addDrawable( Drawable2D* )) );
	connect(toolSelector_, SIGNAL(changed()), scene_, SLOT(update()));
	connect(m_componentList, SIGNAL(deleteCurrent()),
	        m_editorSceneManager, SLOT(deleteCurrentDrawable()) );
	//everything
	connect(m_componentList, SIGNAL(deleteCurrent()),
	        toolSelector_, SLOT(finalise()) );


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

	InvoluteSpurGearTool* invGearTool = new InvoluteSpurGearTool();
	toolSelector_->addTool(invGearTool);

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
	QWidget* baseWidget = new QWidget( dock );
	dock->setWidget(baseWidget);
	
	QVBoxLayout* vbox = new QVBoxLayout( );
	baseWidget->setLayout(vbox);

	m_componentList = new ComponentList( );
	vbox->addWidget(m_componentList);
	
	QPushButton* btn = new QPushButton( "Delete" );
	connect( btn, SIGNAL(clicked()), m_componentList, SLOT(deleteButtonPressed()) );
	vbox->addWidget(btn);

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
    QApplication::sendEvent(m_tabs->currentWidget(), event);
    QMainWindow::keyPressEvent(event);
}

ComponentList* MainWindow::getComponentList() {
	return m_componentList;
}

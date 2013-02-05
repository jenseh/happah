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

	m_viewMenu = menuBar()->addMenu("&View");

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
	m_scene = new EditorScene(this);
	m_scene->setSceneRect(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
	QGraphicsView* view2D = new QGraphicsView(m_scene);
    m_tabs->addTab(view2D, "2D-View");

	setCentralWidget(m_tabs);
	createTools();
	createContainer();

	m_sceneManager3D = new SceneManager3D(sceneManager, m_componentList);
	m_editorSceneManager = new EditorSceneManager( m_scene, m_componentList );
	//3D scene
	connect(m_toolSelector, SIGNAL(emitDrawable(Drawable*)),
	        m_sceneManager3D, SLOT(addDrawable(Drawable*)));
	connect(m_toolSelector, SIGNAL(changed()),
			m_sceneManager3D, SLOT(update()));
	connect(m_componentList, SIGNAL(deleteCurrent()),
	        m_sceneManager3D, SLOT(deleteCurrentDrawable()));
	//editor scene
	connect( m_scene, SIGNAL(rightClickedAt( QPointF )),
		m_toolSelector, SLOT(rightClickAt( QPointF )) );
	connect( m_scene, SIGNAL(leftClickedAt( QPointF )),
		m_toolSelector, SLOT(leftClickAt( QPointF )) );
	connect(m_toolSelector, SIGNAL(emitDrawable( Drawable2D* )),
	        m_editorSceneManager, SLOT(addDrawable( Drawable2D* )) );
	connect(m_toolSelector, SIGNAL(changed()), m_scene, SLOT(update()));
	connect(m_componentList, SIGNAL(deleteCurrent()),
	        m_editorSceneManager, SLOT(deleteCurrentDrawable()) );
	//everything
	connect(m_componentList, SIGNAL(deleteCurrent()),
		m_toolSelector, SLOT(finalise()) );


//createDockWindows();
}

void MainWindow::createTools() {

// Tool selector
	QDockWidget* dock = new QDockWidget(tr("Tools"), this);

	m_toolSelector = new ToolSelector(dock);

	SplineTool* splineTool = new SplineTool();
	m_toolSelector->addTool(splineTool);

	BSplineTool* bSplineTool = new BSplineTool();
	m_toolSelector->addTool(bSplineTool);

	InvoluteSpurGearTool* invGearTool = new InvoluteSpurGearTool();
	m_toolSelector->addTool(invGearTool);

	dock->setWidget(m_toolSelector);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	addDockWidget(Qt::LeftDockWidgetArea, dock);
	m_viewMenu->addAction(dock->toggleViewAction());

// Option docking-window to control current tool
	dock = new QDockWidget(tr("Tool Settings"), this);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	addDockWidget(Qt::LeftDockWidgetArea, dock);
	m_viewMenu->addAction(dock->toggleViewAction());
	dock->setWidget(m_toolSelector->getSettingsWidget());

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
	m_viewMenu->addAction(dock->toggleViewAction());
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
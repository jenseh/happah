#include <QApplication>
#include <QMenuBar>
#include <QDockWidget>
#include <QTabWidget>
#include <QWidget>
#include <QGraphicsView>
#include <string>

#include "happah/gui/qt/MainWindow.h"
#include "happah/gui/qt/SplineTool.h"
#include "happah/gui/qt/BSplineTool.h"
#include "happah/gui/qt/InvoluteSpurGearTool.h"
#include "happah/gui/qt/SimpleGearTool.h"
#include "happah/gui/qt/DiscGearGrindTool.h"
#include "happah/scene/SceneManager.h"
#include "happah/gui/gl/GlViewport3D.h"
#include "../RenderItem3D.h"

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
    m_sceneManager = new SceneManager();

	// Setting up OpenGl 3D-viewport
	QWidget* viewportWidget = new QWidget();
    GlViewport3D* viewport3D = new GlViewport3D(m_sceneManager, glFormat, viewportWidget,
			this);
	viewport3D->setGeometry(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    m_tabs->addTab(viewportWidget, "3D-View");

	// Setting up 2D Editor
	m_scene = new EditorScene(this);
	//m_scene->setSceneRect(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
	m_scene->setSceneRect(-2, -2, 4, 4);
	m_view2D = new QGraphicsView(m_scene);
    m_tabs->addTab(m_view2D, "2D-View");

    setCentralWidget(m_tabs);
    createContainer();

    m_sceneManager3D = new SceneManager3D(m_sceneManager, m_componentList);
    createTools();

    m_editorSceneManager = new EditorSceneManager( m_scene, m_componentList );
	//3D scene
	connect( m_toolSelector, SIGNAL( emitDrawable( RenderItem3D* )),
	        m_sceneManager3D, SLOT( addDrawable( RenderItem3D* )));
	connect( m_toolSelector, SIGNAL( changed() ),
			m_sceneManager3D, SLOT( update() ));
	connect( m_componentList, SIGNAL( deleteCurrent( std::string )),
	        m_sceneManager3D, SLOT( deleteCurrentDrawable( std::string ) ));
	connect(m_sceneManager3D, SIGNAL( updateTool( RenderItem3D* )),
			m_toolSelector, SLOT( activateTool( RenderItem3D* )));
	//editor scene
	connect( m_scene, SIGNAL( rightClickedAt( QPointF )),
		m_toolSelector, SLOT( rightClickAt( QPointF )) );
	connect( m_scene, SIGNAL( leftClickedAt( QPointF )),
		m_toolSelector, SLOT( leftClickAt( QPointF )) );
	connect( m_scene, SIGNAL( scaleScene( int )), this, SLOT( scaleView2D( int ) ));
	connect( m_toolSelector, SIGNAL( changeViewTo( hpvec2, hpvec2 )),
		this, SLOT( changeView2DTo( hpvec2, hpvec2 ) ));
	connect( m_toolSelector, SIGNAL( emitDrawable( Drawable2D* )),
		 m_editorSceneManager, SLOT(addDrawable( Drawable2D* )) );
	connect( m_toolSelector, SIGNAL( changed()), m_scene, SLOT( update() ));
	connect( m_componentList, SIGNAL( deleteCurrent( std::string )),
	        m_editorSceneManager, SLOT( deleteCurrentDrawable( std::string )) );
	connect(m_editorSceneManager, SIGNAL( updateTool( Drawable2D* )),
			m_toolSelector, SLOT( activateTool( Drawable2D* )));
	//everything
	//connect( m_componentList, SIGNAL( deleteCurrent( std::string ) ),
	//	m_toolSelector, SLOT( finalise( std::string ) )); I don't think we need that, as by deleting the toolselector already calls finalise
	connect( m_toolSelector, SIGNAL( deleteCurrentComponent() ),
		m_componentList, SLOT( deleteCurrentComponent() ));


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

	SimpleGearTool* simpleGearTool = new SimpleGearTool();
	m_toolSelector->addTool(simpleGearTool);

    DiscGearGrindTool* discGearGrindTool = new DiscGearGrindTool(m_sceneManager3D);
	m_toolSelector->addTool(discGearGrindTool);
    m_sceneManager->registerListener(discGearGrindTool);

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

void MainWindow::scaleView2D( int factor ) {
	//as to read in QtDocu most often QGraphicsSceneWheelEvent::delta() will be a multiple of 120
	//positive values imply the wheel was turned to front (away from user)
	//negative values imply the wheel was turned toward the user
	m_view2D->setAttribute(Qt::WA_StaticContents, true);
	m_view2D->setTransformationAnchor(QGraphicsView::ViewportAnchor(2));
	if (factor > 0)
		m_view2D->scale(0.9f, 0.9f);
	else if (factor < 0)
		m_view2D->scale(1.1f, 1.1f);
}

void MainWindow::changeView2DTo( hpvec2 min, hpvec2 max ) {
	m_view2D->fitInView(min.x, min.y, max.x - min.x, max.y - min.y, Qt::KeepAspectRatio);
}

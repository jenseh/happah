#include <QApplication>
#include <QDockWidget>
#include <QGraphicsView>
#include <QMenuBar>
#include <QTabWidget>
#include <QWidget>
#include <string>

#include "happah/gui/RenderItem3D.h"
#include "happah/gui/gl/GlViewport3D.h"
#include "happah/gui/qt/MainWindow.h"
#include "happah/gui/qt/tools/BSplineTool.h"
#include "happah/gui/qt/tools/DiscGearGrindTool.h"
#include "happah/gui/qt/tools/InvoluteSpurGearTool.h"
#include "happah/gui/qt/tools/SimpleGearTool.h"
#include "happah/gui/qt/tools/SplineTool.h"

MainWindow::MainWindow(SceneManager& sceneManager, DrawManager& drawManager)
	: m_sceneManager(sceneManager) {
	resize(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
	setWindowTitle("Happah");

	QMenu* file = menuBar()->addMenu("&File");
	QAction* quitAction = new QAction("&Quit", this);
	quitAction->setShortcut(tr("CTRL+Q"));
	connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
	file->addAction(quitAction);
	m_viewMenu = menuBar()->addMenu("&View");

	m_tabs = new QTabWidget(this);
	GlViewport3D* viewport3D = new GlViewport3D(drawManager, this);
	m_tabs->addTab(viewport3D, "3D-View");
	m_scene = new EditorScene(this);
	m_scene->setSceneRect(-2, -2, 4, 4);
	m_view2D = new QGraphicsView(m_scene);
	m_tabs->addTab(m_view2D, "2D-View");

	setCentralWidget(m_tabs);
	createContainer();

	m_sceneManager3D = new SceneManager3D(&m_sceneManager, m_componentList);
	createTools();

	m_editorSceneManager = new EditorSceneManager( m_scene, m_componentList );
	connect(m_toolSelector, SIGNAL(emitDrawable(RenderItem3D*)), m_sceneManager3D, SLOT(addDrawable(RenderItem3D*)));
	connect(m_toolSelector, SIGNAL(changed()), m_sceneManager3D, SLOT(update()));
	connect(m_componentList, SIGNAL(deleteCurrent(std::string)), m_sceneManager3D, SLOT(deleteCurrentDrawable(std::string)));
	connect(m_sceneManager3D, SIGNAL(updateTool(RenderItem3D*)), m_toolSelector, SLOT(activateTool(RenderItem3D*)));
	connect(m_scene, SIGNAL(rightClickedAt(QPointF)), m_toolSelector, SLOT(rightClickAt(QPointF)));
	connect(m_scene, SIGNAL(leftClickedAt(QPointF)), m_toolSelector, SLOT(leftClickAt(QPointF)));
	connect(m_scene, SIGNAL(scaleScene(int)), this, SLOT(scaleView2D(int)));
	connect(m_toolSelector, SIGNAL(changeViewTo(hpvec2, hpvec2)), this, SLOT(changeView2DTo(hpvec2, hpvec2)));
	connect(m_toolSelector, SIGNAL(emitDrawable(Drawable2D*)), m_editorSceneManager, SLOT(addDrawable(Drawable2D*)));
	connect(m_toolSelector, SIGNAL(changed()), m_scene, SLOT(update()));
	connect(m_componentList, SIGNAL(deleteCurrent(std::string)), m_editorSceneManager, SLOT(deleteCurrentDrawable(std::string)));
	connect(m_editorSceneManager, SIGNAL(updateTool(Drawable2D*)), m_toolSelector, SLOT(activateTool(Drawable2D*)));
	connect(m_toolSelector, SIGNAL(deleteCurrentComponent()), m_componentList, SLOT(deleteCurrentComponent()));
}

MainWindow::~MainWindow() {}

void MainWindow::createTools() {
	QDockWidget* dock = new QDockWidget(tr("Tools"), this);

	m_toolSelector = new ToolSelector(dock);

	SplineTool* splineTool = new SplineTool();
	m_toolSelector->addTool(splineTool);

	BSplineTool* bSplineTool = new BSplineTool();
	m_toolSelector->addTool(bSplineTool);

	InvoluteSpurGearTool* invGearTool = new InvoluteSpurGearTool(m_sceneManager);
	m_toolSelector->addTool(invGearTool);

	SimpleGearTool* simpleGearTool = new SimpleGearTool();
	m_toolSelector->addTool(simpleGearTool);

	DiscGearGrindTool* discGearGrindTool = new DiscGearGrindTool(m_sceneManager3D);
	m_toolSelector->addTool(discGearGrindTool);
	m_sceneManager.registerListener(discGearGrindTool);

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

void MainWindow::keyPressEvent(QKeyEvent *event) {
	if (event->key() == Qt::Key_Escape) {
		qApp->quit();
    }
    QApplication::sendEvent(m_tabs->currentWidget(), event);
    QMainWindow::keyPressEvent(event);
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

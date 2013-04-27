#include <QAction>
#include <QApplication>
#include <QMenu>
#include <QWidget>

#include "happah/gui/MainWindow.h"
#include "happah/gui/Viewport.h"

MainWindow::MainWindow(GUIManager& guiManager, 
	ViewportListener& viewportListener,
	SceneGraphExplorerListener& sceneGraphExplorerListener,
	DrawManager& drawManager
) : m_sceneGraphExplorerPanel(new SceneGraphExplorerPanel(sceneGraphExplorerListener, this)),
	m_toolPanel(new ToolPanel(guiManager, this)) {
	
	resize(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
	setWindowTitle("Happah");

	QMenu* file = menuBar()->addMenu("&File");
	QAction* quitAction = new QAction("&Quit", this);
	quitAction->setShortcut(tr("CTRL+Q"));
	connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
	file->addAction(quitAction);
	QAction* importAction = new QAction("&Import", this);
	importAction->setShortcut(tr("CTRL+I"));
	connect(importAction, SIGNAL(triggered()), this, SLOT(importFile()));
	file->addAction(importAction);

	QWidget* centralWidget = new QWidget(this);
	QHBoxLayout* centralWidgetLayout = new QHBoxLayout();
	centralWidget->setLayout(centralWidgetLayout);
	centralWidgetLayout->addWidget(m_toolPanel);
	centralWidgetLayout->addWidget(new Viewport(viewportListener, drawManager, this), 1);
	centralWidgetLayout->addWidget(m_sceneGraphExplorerPanel);

	m_guiManager = &guiManager;

	m_bSplineCurveContextMenu = new BSplineCurveContextMenu(guiManager, this);
	m_defaultContextMenu = new ContextMenu(this);
	m_discContextMenu = new DiscContextMenu(guiManager, this);
	m_involuteGearContextMenu = new InvoluteGearContextMenu(guiManager, this);
	m_planeContextMenu = new PlaneContextMenu(guiManager, this);
	m_simpleGearContextMenu = new SimpleGearContextMenu(guiManager, this);
	m_simulationContextMenu = new SimulationContextMenu(guiManager, this);
	m_toothProfileContextMenu = new ToothProfileContextMenu(guiManager, this);
	m_triangleMeshContextMenu = new TriangleMeshContextMenu(guiManager, this);

	setCentralWidget(centralWidget);
}

MainWindow::~MainWindow() {}

SceneGraphExplorerPanel* MainWindow::getSceneGraphExplorerPanel() {
	return m_sceneGraphExplorerPanel;
}

ToolPanel* MainWindow::getToolPanel() {
	return m_toolPanel;
}

BSplineCurveContextMenu* MainWindow::getBSplineCurveContextMenu() {
	return m_bSplineCurveContextMenu;
}

ContextMenu* MainWindow::getDefaultContextMenu() {
	return m_defaultContextMenu;
}

DiscContextMenu* MainWindow::getDiscContextMenu() {
	return m_discContextMenu;
}

InvoluteGearContextMenu* MainWindow::getInvoluteGearContextMenu() {
	return m_involuteGearContextMenu;
}

PlaneContextMenu* MainWindow::getPlaneContextMenu() {
	return m_planeContextMenu;
}

SimpleGearContextMenu* MainWindow::getSimpleGearContextMenu() {
	return m_simpleGearContextMenu;
}

SimulationContextMenu* MainWindow::getSimulationContextMenu() {
	return m_simulationContextMenu;
}

ToothProfileContextMenu* MainWindow::getToothProfileContextMenu() {
	return m_toothProfileContextMenu;
}

TriangleMeshContextMenu* MainWindow::getTriangleMeshContextMenu() {
	return m_triangleMeshContextMenu;
}

void MainWindow::importFile() {
	QString fileName("");
	QString selectedFilter("");
	/*
		use QFileDialog object instead of static method QFileDialog::getOpenFileName.
		because there exist a memory leak bug for the static use on some qt versions
	*/
	QFileDialog dialog(this);
	dialog.setNameFilter(tr("Wavefront 3D Object (*.obj)"));
	//dialog.setDirectory("");
	dialog.setWindowTitle("Import File...");
	if (dialog.exec() == QDialog::Accepted)
	{
		fileName = dialog.selectedFiles().first();
		selectedFilter = dialog.selectedNameFilter();
	}

	if (selectedFilter == "Wavefront 3D Object (*.obj)") {
		std::cout << "call createTriangleMeshFromObjFile(fileName) in guiManager" << endl;
		//m_guiManager
	}
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
	if(event->key() == Qt::Key_Escape)
		qApp->quit();
	QMainWindow::keyPressEvent(event);
}

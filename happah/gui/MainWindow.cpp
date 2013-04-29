#include <fstream>
#include <QAction>
#include <QApplication>
#include <QMenu>
#include <QWidget>

#include "happah/gui/MainWindow.h"
#include "happah/gui/Viewport.h"
#include "happah/gui/widgets/FileDialog.h"
#include "happah/io/WavefrontGeometryReaderOBJ.h"

using namespace std;

MainWindow::MainWindow(GUIManager& guiManager, 
	ViewportListener& viewportListener,
	SceneGraphExplorerListener& sceneGraphExplorerListener,
	DrawManager& drawManager
) : m_guiManager(guiManager), m_sceneGraphExplorerPanel(new SceneGraphExplorerPanel(sceneGraphExplorerListener, this)),
	m_toolPanel(new ToolPanel(guiManager, this)) {
	
	resize(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
	setWindowTitle("Happah");

	QMenu* file = menuBar()->addMenu("&File");
	QAction* importAction = new QAction("&Import...", this);
	importAction->setShortcut(tr("CTRL+I"));
	connect(importAction, SIGNAL(triggered()), this, SLOT(handleImportActionTriggeredEvent()));
	file->addAction(importAction);
	QAction* quitAction = new QAction("&Quit", this);
	quitAction->setShortcut(tr("CTRL+Q"));
	connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
	file->addAction(quitAction);

	QWidget* centralWidget = new QWidget(this);
	QHBoxLayout* centralWidgetLayout = new QHBoxLayout();
	centralWidget->setLayout(centralWidgetLayout);
	centralWidgetLayout->addWidget(m_toolPanel);
	centralWidgetLayout->addWidget(new Viewport(viewportListener, drawManager, this), 1);
	centralWidgetLayout->addWidget(m_sceneGraphExplorerPanel);

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

void MainWindow::handleImportActionTriggeredEvent() {
	FileDialog fileDialog("Import...", this);
	fileDialog.setNameFilters(FileDialog::WAVEFRONT_TRIANGLE_MESH_3D);
	fileDialog.setFileMode(QFileDialog::ExistingFile);
	if(fileDialog.exec() == QDialog::Accepted) {
		QString path = fileDialog.selectedFiles().first();
		hpuint contentType = FileDialog::getContentType(path);
		if(contentType != 0) {
			switch(contentType) {
			case FileDialog::WAVEFRONT_TRIANGLE_MESH_3D: {
				TriangleMesh* triangleMesh;
				ifstream file(path.toStdString().c_str());
				WavefrontGeometryReaderOBJ::read(file, triangleMesh);
				if(triangleMesh != 0)
					m_guiManager.insert(TriangleMesh_ptr(triangleMesh));
				return;
			}
			default:
				return;
			}
		}
	}
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
	if(event->key() == Qt::Key_Escape)
		qApp->quit();
	QMainWindow::keyPressEvent(event);
}

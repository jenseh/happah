#include <QAction>
#include <QApplication>
#include <QMenu>
#include <QWidget>

#include "happah/gui/MainWindow.h"
#include "happah/gui/Viewport3D.h"

MainWindow::MainWindow(GUIManager& guiManager, 
	Viewport3DListener& viewport3DListener,
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

	QWidget* centralWidget = new QWidget(this);
	QHBoxLayout* centralWidgetLayout = new QHBoxLayout();
	centralWidget->setLayout(centralWidgetLayout);
	centralWidgetLayout->addWidget(m_toolPanel);
	centralWidgetLayout->addWidget(new Viewport3D(viewport3DListener, drawManager, this), 1);
	centralWidgetLayout->addWidget(m_sceneGraphExplorerPanel);

	m_defaultContextMenu = new ContextMenu(this);
	m_involuteGearContextMenu = new InvoluteGearContextMenu(guiManager, this);
	m_discContextMenu = new DiscContextMenu(guiManager, this);
	m_simpleGearContextMenu = new SimpleGearContextMenu(guiManager, this);
	m_simulationContextMenu = new SimulationContextMenu(guiManager, this);

	setCentralWidget(centralWidget);
}

MainWindow::~MainWindow() {}

SceneGraphExplorerPanel* MainWindow::getSceneGraphExplorerPanel() {
	return m_sceneGraphExplorerPanel;
}

ToolPanel* MainWindow::getToolPanel() {
	return m_toolPanel;
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

SimpleGearContextMenu* MainWindow::getSimpleGearContextMenu() {
	return m_simpleGearContextMenu;
}

SimulationContextMenu* MainWindow::getSimulationContextMenu() {
	return m_simulationContextMenu;
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
	if (event->key() == Qt::Key_Escape)
		qApp->quit();
	QMainWindow::keyPressEvent(event);
}

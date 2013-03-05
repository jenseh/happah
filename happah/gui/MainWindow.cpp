#include <QAction>
#include <QApplication>
#include <QMenu>
#include <QWidget>

#include "happah/gui/MainWindow.h"
#include "happah/gui/SceneGraphExplorerPanel.h"
#include "happah/gui/Viewport3D.h"

MainWindow::MainWindow(SceneManager& sceneManager, GUIManager& guiManager, DrawManager& drawManager)
	: m_toolPanel(new ToolPanel(guiManager, this)) {
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
	centralWidgetLayout->addWidget(new Viewport3D(drawManager, this), 1);
	centralWidgetLayout->addWidget(new SceneGraphExplorerPanel(sceneManager, this));

	setCentralWidget(centralWidget);
}

MainWindow::~MainWindow() {}

InvoluteGearForm* MainWindow::getInvoluteGearForm() {
	return m_toolPanel->getInvoluteGearForm();
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
	if (event->key() == Qt::Key_Escape)
		qApp->quit();
	QMainWindow::keyPressEvent(event);
}

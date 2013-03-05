#include <QPushButton>
#include <QVBoxLayout>

#include "happah/gui/SceneGraphExplorerPanel.h"

SceneGraphExplorerPanel::SceneGraphExplorerPanel(SceneManager& sceneManager, QWidget* parent)
	: QWidget(parent), m_listWidget(new QListWidget(this)), m_sceneManager(sceneManager) {
	m_sceneManager.registerListener(this);

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(m_listWidget);
	layout->addWidget(new QPushButton("Delete"));
	setLayout(layout);
}

SceneGraphExplorerPanel::~SceneGraphExplorerPanel() {}

void SceneGraphExplorerPanel::sceneChanged() {
	m_listWidget->clear();
	m_sceneManager.accept(*this);
}

void SceneGraphExplorerPanel::visit(InvoluteGearGUIStateNode_ptr involuteGearGUIStateNode) {
	m_listWidget->addItem(QString(involuteGearGUIStateNode->getName().c_str()));
}

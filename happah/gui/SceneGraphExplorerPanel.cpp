#include <QList>
#include <QPushButton>
#include <QVBoxLayout>
#include <vector>

using namespace std;

#include "happah/gui/SceneGraphExplorerPanel.h"

SceneGraphExplorerPanel::SceneGraphExplorerPanel(GUIManager& guiManager, QWidget* parent)
	: QWidget(parent), m_deleteButton(new QPushButton("Delete", this)), m_listWidget(new QListWidget(this)), m_guiManager(guiManager) {
	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(m_listWidget);
	layout->addWidget(m_deleteButton);
	setLayout(layout);

	connect(m_listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(handleItemDoubleClickedEvent(QListWidgetItem*)));
	connect(m_deleteButton, SIGNAL(clicked()), this, SLOT(handleDeleteButtonClickedEvent()));
}

SceneGraphExplorerPanel::~SceneGraphExplorerPanel() {}

void SceneGraphExplorerPanel::addItem(const QString& label, GUIStateNode_ptr guiStateNode) {
	m_guiStateNodes.push_back(guiStateNode);
	m_listWidget->addItem(label);
}

void SceneGraphExplorerPanel::clear() {
	m_listWidget->clear();
	m_guiStateNodes.clear();
}

void SceneGraphExplorerPanel::handleDeleteButtonClickedEvent() {
	QList<QListWidgetItem*> selectedItems = m_listWidget->selectedItems();
	vector<GUIStateNode_ptr> selectedGUIStateNodes;
	selectedGUIStateNodes.reserve(selectedItems.size());
	foreach(QListWidgetItem* item, selectedItems) {
		int index = m_listWidget->row(item);
		selectedGUIStateNodes.push_back(m_guiStateNodes[index]);
	}
	m_guiManager.handleGUIStateNodesDeletedEvent(selectedGUIStateNodes);
}

void SceneGraphExplorerPanel::handleItemDoubleClickedEvent(QListWidgetItem* item) {
	int index = m_listWidget->row(item);
	m_guiManager.handleGUIStateNodeSelectedEvent(m_guiStateNodes[index]);
}

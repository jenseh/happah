#include <QList>
#include <QPushButton>
#include <QVBoxLayout>
#include <vector>

using namespace std;

#include "happah/gui/SceneGraphExplorerPanel.h"

SceneGraphExplorerPanel::SceneGraphExplorerPanel(SceneGraphExplorerListener& sceneGraphExplorerListener, QWidget* parent)
	: QWidget(parent), m_deleteButton(new QPushButton("Delete", this)), m_listWidget(new QListWidget(this)), m_sceneGraphExplorerListener(sceneGraphExplorerListener) {
	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(m_listWidget);
	layout->addWidget(m_deleteButton);
	setLayout(layout);

	connect(m_listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(handleItemDoubleClickedEvent(QListWidgetItem*)));
	connect(m_deleteButton, SIGNAL(clicked()), this, SLOT(handleDeleteButtonClickedEvent()));
}

SceneGraphExplorerPanel::~SceneGraphExplorerPanel() {}

void SceneGraphExplorerPanel::insert(GUIStateNode_ptr guiStateNode) {
	int index = m_listWidget->count();
	m_listWidget->addItem(QString(guiStateNode->getName().c_str()));
	QListWidgetItem* item = m_listWidget->item(index);
	m_guiStateNodesByItem[item] = guiStateNode;
	m_itemsByGUIStateNode[guiStateNode] = item;
}

void SceneGraphExplorerPanel::handleDeleteButtonClickedEvent() {
	QList<QListWidgetItem*> selectedItems = m_listWidget->selectedItems();
	vector<GUIStateNode_ptr> selectedGUIStateNodes;
	selectedGUIStateNodes.reserve(selectedItems.size());
	foreach(QListWidgetItem* item, selectedItems)
		selectedGUIStateNodes.push_back(m_guiStateNodesByItem[item]);
	m_sceneGraphExplorerListener.handleGUIStateNodesDeletedEvent(selectedGUIStateNodes);
}

void SceneGraphExplorerPanel::handleItemDoubleClickedEvent(QListWidgetItem* item) {
	m_sceneGraphExplorerListener.handleGUIStateNodeSelectedEvent(m_guiStateNodesByItem[item]);
}

void SceneGraphExplorerPanel::remove(GUIStateNode_ptr guiStateNode) {
	QListWidgetItem* item = m_itemsByGUIStateNode[guiStateNode];
	m_guiStateNodesByItem.erase(item);
	m_itemsByGUIStateNode.erase(guiStateNode);
	delete item;
}

void SceneGraphExplorerPanel::update(GUIStateNode_ptr guiStateNode) {
	QListWidgetItem* item = m_itemsByGUIStateNode[guiStateNode];
	item->setText(QString(guiStateNode->getName().c_str()));
}

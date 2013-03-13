#include <QActionGroup>
#include <QCursor>
#include <QList>
#include <QMenu>
#include <QPoint>
#include <QPushButton>
#include <QVBoxLayout>
#include <vector>

using namespace std;

#include "happah/gui/context-menus/ContextMenu.h"
#include "happah/gui/SceneGraphExplorerPanel.h"

SceneGraphExplorerPanel::SceneGraphExplorerPanel(SceneGraphExplorerListener& sceneGraphExplorerListener, QWidget* parent)
	: QWidget(parent), m_deleteButton(new QPushButton("Delete", this)), m_listWidget(new QListWidget(this)), m_sceneGraphExplorerListener(sceneGraphExplorerListener) {
	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(m_listWidget);
	layout->addWidget(m_deleteButton);
	setLayout(layout);

	setContextMenuPolicy (Qt::DefaultContextMenu);

	connect(m_listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(handleItemClickedEvent(QListWidgetItem*)));
	connect(m_deleteButton, SIGNAL(clicked()), this, SLOT(handleDeleteButtonClickedEvent()));
}

SceneGraphExplorerPanel::~SceneGraphExplorerPanel() {}

void SceneGraphExplorerPanel::contextMenuEvent (QContextMenuEvent* event) {

	QPoint ppp = QCursor::pos();
	QPoint globalPoint = event->globalPos();
	QListWidgetItem* selectedItem = m_listWidget->itemAt(m_listWidget->mapFromGlobal(globalPoint));
	GUIStateNode_ptr selectedGUIStateNode = m_guiStateNodesByItem[selectedItem];

	if(selectedGUIStateNode && selectedGUIStateNode->getContextMenu()) {
		ContextMenu* contextMenu = selectedGUIStateNode->getContextMenu();
		QAction* action = contextMenu->exec(ppp);
	}
}

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

void SceneGraphExplorerPanel::handleItemClickedEvent(QListWidgetItem* item) {
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

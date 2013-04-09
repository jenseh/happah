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
	: 		QWidget(parent), m_createDiscGearGrindButton(new QPushButton("Create disc gear grind", this)),
			m_deleteButton(new QPushButton("Delete", this)), m_listWidget(new QListWidget(this)),
			m_sceneGraphExplorerListener(sceneGraphExplorerListener) {
	m_listWidget->setSelectionMode(QAbstractItemView::MultiSelection );

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(m_listWidget);
	layout->addWidget(m_createDiscGearGrindButton);
	layout->addWidget(m_deleteButton);
	setLayout(layout);

	setContextMenuPolicy (Qt::DefaultContextMenu);

	connect(m_listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(handleItemClickedEvent(QListWidgetItem*)));
	connect(m_createDiscGearGrindButton, SIGNAL(clicked()), this, SLOT(handleCreateDiscGearGrindButtonClickedEvent()));
	connect(m_deleteButton, SIGNAL(clicked()), this, SLOT(handleDeleteButtonClickedEvent()));

	m_createDiscGearGrindButton->setEnabled(false);
}

SceneGraphExplorerPanel::~SceneGraphExplorerPanel() {}

void SceneGraphExplorerPanel::contextMenuEvent (QContextMenuEvent* event) {

	QPoint globalPoint = event->globalPos();
	QListWidgetItem* selectedItem = m_listWidget->itemAt(m_listWidget->mapFromGlobal(globalPoint));
	GUIStateNode_ptr selectedGUIStateNode = m_guiStateNodesByItem[selectedItem];

	if(selectedGUIStateNode != NULL && selectedGUIStateNode->getContextMenu() != NULL ) {
		ContextMenu* contextMenu = selectedGUIStateNode->getContextMenu();
		QAction* action = contextMenu->exec(globalPoint);
	}
}

template<class T> bool SceneGraphExplorerPanel::getSelected(std::shared_ptr<T>& element) {
	foreach(QListWidgetItem* item, m_listWidget->selectedItems()) {
		element = dynamic_pointer_cast<T>(m_guiStateNodesByItem[item]);
		if(element)
			return true;
	}
	return false;
}

void SceneGraphExplorerPanel::insert(GUIStateNode_ptr guiStateNode) {
	int index = m_listWidget->count();
	m_listWidget->addItem(QString(guiStateNode->getName().c_str()));
	QListWidgetItem* item = m_listWidget->item(index);
	m_guiStateNodesByItem[item] = guiStateNode;
	m_itemsByGUIStateNode[guiStateNode] = item;
}

void SceneGraphExplorerPanel::handleCreateDiscGearGrindButtonClickedEvent() {
	DiscGUIStateNode_ptr discGUIStateNode;
	SurfaceOfRevolution_ptr disc;
	SimpleGear_ptr gear;
	if( getSelected<DiscGUIStateNode>(discGUIStateNode) ){
		InvoluteGearGUIStateNode_ptr gearGUIStateNode;
		if( getSelected<InvoluteGearGUIStateNode>(gearGUIStateNode) ) {
			gear = SimpleGear_ptr(gearGUIStateNode->getInvoluteGear()->toSimpleGear());
		} else {
			SimpleGearGUIStateNode_ptr gearGUIStateNode;
			if( getSelected<SimpleGearGUIStateNode>(gearGUIStateNode) ) {
				gear = gearGUIStateNode->getSimpleGear();
			}else{
				return;
			}
		}
		disc = discGUIStateNode->getSurfaceOfRevolution();
		m_sceneGraphExplorerListener.createDiscGearGrind(disc, gear);
	}
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
	// Check selection for DiscGearGrind
	m_createDiscGearGrindButton->setEnabled(false);
	if( m_listWidget->selectedItems().size() == 2 ) {
		DiscGUIStateNode_ptr disc;
		if( getSelected<DiscGUIStateNode>(disc) ) {
			SimpleGearGUIStateNode_ptr simpleGear;
			InvoluteGearGUIStateNode_ptr involuteGear;
			if( getSelected<SimpleGearGUIStateNode>(simpleGear) || getSelected<InvoluteGearGUIStateNode>(involuteGear)) {
				m_createDiscGearGrindButton->setEnabled(true);
			}
		}
	}
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

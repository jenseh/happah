#ifndef SCENE_GRAPH_EXPLORER_PANEL_H
#define SCENE_GRAPH_EXPLORER_PANEL_H

#include <QListWidget>
#include <QPushButton>
#include <QString>
#include <QWidget>
#include <unordered_map>
#include <vector>
#include <QContextMenuEvent>

using namespace std;

#include "happah/gui/SceneGraphExplorerListener.h"

class SceneGraphExplorerPanel : public QWidget {
Q_OBJECT

public:
	SceneGraphExplorerPanel(SceneGraphExplorerListener& sceneGraphExplorerListener, QWidget* parent = 0);
	~SceneGraphExplorerPanel();
	
	void insert(GUIStateNode_ptr guiStateNode);
	void remove(GUIStateNode_ptr guiStateNode);
	void update(GUIStateNode_ptr guiStateNode);

private:
	QPushButton* m_createDiscGearGrindButton;
	QPushButton* m_createWormGearGrindButton;
	QPushButton* m_deleteButton;
	unordered_map<QListWidgetItem*, GUIStateNode_ptr> m_guiStateNodesByItem;
	unordered_map<GUIStateNode_ptr, QListWidgetItem*> m_itemsByGUIStateNode;
	QListWidget* m_listWidget;
	SceneGraphExplorerListener& m_sceneGraphExplorerListener;
	void contextMenuEvent (QContextMenuEvent* event);
	template<class T> bool getSelected(shared_ptr<T>& element);


private slots:
void handleCreateDiscGearGrindButtonClickedEvent();
void handleCreateWormGearGrindButtonClickedEvent();
void handleDeleteButtonClickedEvent();
void handleItemClickedEvent(QListWidgetItem* item);

};

#endif //SCENE_GRAPH_EXPLORER_PANEL_H

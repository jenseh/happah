#ifndef SCENE_GRAPH_EXPLORER_PANEL_H
#define SCENE_GRAPH_EXPLORER_PANEL_H

#include <QListWidget>
#include <QPushButton>
#include <QString>
#include <QWidget>
#include <vector>

using namespace std;

#include "happah/gui/GUIManager.h"

class SceneGraphExplorerPanel : public QWidget {
Q_OBJECT

public:
	SceneGraphExplorerPanel(GUIManager& guiManager, QWidget* parent = 0);
	~SceneGraphExplorerPanel();
	
	void addItem(const QString& label, GUIStateNode_ptr guiStateNode);
	void clear();

private:
	QPushButton* m_deleteButton;
	GUIManager& m_guiManager;
	vector<GUIStateNode_ptr> m_guiStateNodes;
	QListWidget* m_listWidget;

private slots:
	void handleDeleteButtonClickedEvent();
	void handleItemDoubleClickedEvent(QListWidgetItem* item);

};

#endif //SCENE_GRAPH_EXPLORER_PANEL_H

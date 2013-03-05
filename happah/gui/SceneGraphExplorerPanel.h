#ifndef SCENE_GRAPH_EXPLORER_PANEL_H
#define SCENE_GRAPH_EXPLORER_PANEL_H

#include <QListWidget>
#include <QWidget>

class SceneGraphExplorerPanel : public QWidget {

public:
	SceneGraphExplorerPanel(QWidget* parent = 0);
	~SceneGraphExplorerPanel();

private:
	QListWidget* m_listWidget;

};

#endif //SCENE_GRAPH_EXPLORER_PANEL_H

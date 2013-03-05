#ifndef SCENE_GRAPH_EXPLORER_PANEL_H
#define SCENE_GRAPH_EXPLORER_PANEL_H

#include <QListWidget>
#include <QWidget>

#include "happah/scene/GUIVisitor.h"
#include "happah/scene/SceneListener.h"
#include "happah/scene/SceneManager.h"

class SceneGraphExplorerPanel : public QWidget, public GUIVisitor, public SceneListener {

public:
	SceneGraphExplorerPanel(SceneManager& m_sceneManager, QWidget* parent = 0);
	~SceneGraphExplorerPanel();

	void sceneChanged();
	void visit(InvoluteGearGUIStateNode_ptr involuteGearGUIStateNode);

private:
	QListWidget* m_listWidget;
	SceneManager& m_sceneManager;

};

#endif //SCENE_GRAPH_EXPLORER_PANEL_H

#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include <QListWidgetItem>
#include <unordered_map>

using namespace std;

class GUIManager;

#include "happah/geometries/InvoluteGear.h"
#include "happah/geometries/Mesh.h"
#include "happah/gui/DrawManager.h"
#include "happah/gui/MainWindow.h"
#include "happah/gui/SceneGraphExplorerPanel.h"
#include "happah/gui/ToolPanel.h"
#include "happah/gui/forms/InvoluteGearListener.h"
#include "happah/scene/SceneManager.h"

class GUIManager : public GUIVisitor, public SceneListener, public InvoluteGearListener {

public:
	GUIManager(SceneManager& sceneManager);
	~GUIManager();

	void handleGUIStateNodesDeletedEvent(vector<GUIStateNode_ptr>& guiStateNodes);
	void handleGUIStateNodeSelectedEvent(GUIStateNode_ptr guiStateNode);
	bool init();
	void insert(InvoluteGear_ptr involuteGear);
	void sceneChanged();
	void update(InvoluteGear_ptr involuteGear);
	void visit(InvoluteGearGUIStateNode_ptr involuteGearGUIStateNode);

private:
	int m_counter;
	DrawManager m_drawManager;
	unordered_map<shared_ptr<void>, GUIStateNode_ptr> m_guiStateNodes;
	MainWindow m_mainWindow;
	SceneGraphExplorerPanel* m_sceneGraphExplorerPanel;
	SceneManager& m_sceneManager;
	ToolPanel* m_toolPanel;

};


#endif // GUI_MANAGER_H

#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include <QListWidgetItem>
#include <unordered_map>

using namespace std;

class GUIManager;

#include "happah/geometries/InvoluteGear.h"
#include "happah/geometries/Mesh.h"
#include "happah/geometries/Plane.h"
#include "happah/gui/DrawManager.h"
#include "happah/gui/MainWindow.h"
#include "happah/gui/SceneGraphExplorerPanel.h"
#include "happah/gui/ToolPanel.h"
#include "happah/gui/forms/InvoluteGearListener.h"
#include "happah/gui/forms/SimpleGearListener.h"
#include "happah/scene/SceneManager.h"

class GUIManager : public GUIVisitor, public SceneListener, public InvoluteGearListener, public SimpleGearListener {

public:
	GUIManager(SceneManager_ptr sceneManager);
	~GUIManager();

	void handleGUIStateNodesDeletedEvent(vector<GUIStateNode_ptr>& guiStateNodes);
	void handleGUIStateNodeSelectedEvent(GUIStateNode_ptr guiStateNode);
	void handleSubtreeInsertedEvent(Node_ptr root);
	void handleSubtreesInsertedEvent(vector<Node_ptr>& roots);
	void handleSubtreeRemovedEvent(Node_ptr root);
	void handleSubtreesRemovedEvent(vector<Node_ptr>& roots);
	void handleSubtreeUpdatedEvent(Node_ptr root);
	void handleSubtreesUpdatedEvent(vector<Node_ptr>& roots);
	bool init();
	void insert(InvoluteGear_ptr involuteGear);
	void insert(Plane_ptr plane);
	void insert(SimpleGear_ptr simpleGear);
	void update(InvoluteGear_ptr involuteGear);
	void update(SimpleGear_ptr simpleGear);
	void visit(InvoluteGearGUIStateNode_ptr involuteGearGUIStateNode);
	void visit(PlaneGUIStateNode_ptr planeGUIStateNode);
	void visit(SimpleGearGUIStateNode_ptr simpleGearGUIStateNode);

private:
	int m_counter;
	DrawManager m_drawManager;
	unordered_map<shared_ptr<void>, GUIStateNode_ptr> m_guiStateNodes;
	MainWindow m_mainWindow;
	SceneGraphExplorerPanel* m_sceneGraphExplorerPanel;
	SceneManager_ptr m_sceneManager;
	ToolPanel* m_toolPanel;

	template<class G, class S, class F>
	void doInsert3D(shared_ptr<G> geometry, const char* label, F* form);
	template<class G>
	void doUpdate3D(shared_ptr<G> geometry);
	void sceneChanged();

};


#endif // GUI_MANAGER_H

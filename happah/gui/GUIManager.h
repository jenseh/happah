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
#include "happah/gui/SceneGraphExplorerListener.h"
#include "happah/gui/SceneGraphExplorerPanel.h"
#include "happah/gui/ToolPanel.h"
#include "happah/gui/context-menus/ContextMenu.h"
#include "happah/gui/context-menus/ContextMenuControl.h"
#include "happah/gui/forms/InvoluteGearListener.h"
#include "happah/gui/forms/SimpleGearListener.h"
#include "happah/gui/forms/SimulationListener.h"
#include "happah/gui/forms/DiscListener.h"
#include "happah/gui/forms/WormListener.h"
#include "happah/scene/SceneManager.h"
#include "happah/gui/Viewport3DListener.h"

class GUIManager : public InvoluteGearListener, public SimpleGearListener, public DiscListener, public WormListener, public PlaneListener, public Viewport3DListener, public SimulationListener {

public:
	GUIManager(SceneManager_ptr sceneManager);
	~GUIManager();

	void handleMouseClickEvent(Ray ray);
	bool init();
	void insert(InvoluteGear_ptr involuteGear);
	void insert(Plane_ptr plane);
	void insert(SimpleGear_ptr simpleGear);
	void insert(SimulationResult simulationResult);
	void insert(Disc_ptr disc);
	void insert(Worm_ptr worm);
	void update(InvoluteGear_ptr involuteGear);
	void update(Plane_ptr plane);
	void update(SimpleGear_ptr simpleGear);
	void update(SimulationResult simulationResult);
	void update(Disc_ptr disc);
	void update(Worm_ptr worm);

private:
	class DefaultSceneGraphExplorerListener : public SceneGraphExplorerListener {
	public:
		DefaultSceneGraphExplorerListener(GUIManager& guiManager);
		~DefaultSceneGraphExplorerListener();

		void handleGUIStateNodesDeletedEvent(vector<GUIStateNode_ptr>& guiStateNodes);
		void handleGUIStateNodeSelectedEvent(GUIStateNode_ptr guiStateNode);		

	private:
		GUIManager& m_guiManager;

	};

	class DefaultSceneListener : public SceneListener {
	public:
		DefaultSceneListener(GUIManager& guiManager);
		~DefaultSceneListener();

		void handleSubtreeInsertedEvent(Node_ptr root);
		void handleSubtreesInsertedEvent(vector<Node_ptr>& roots);
		void handleSubtreeRemovedEvent(Node_ptr root);
		void handleSubtreesRemovedEvent(vector<Node_ptr>& roots);
		void handleSubtreeUpdatedEvent(Node_ptr root);
		void handleSubtreesUpdatedEvent(vector<Node_ptr>& roots);

	private:
		GUIManager& m_guiManager;
	};


	class SubtreesRemovedEventHandler : public GUIVisitor {
	public:
		SubtreesRemovedEventHandler(GUIManager& guiManager);
		~SubtreesRemovedEventHandler();

		void visit(GUIStateNode_ptr guiStateNode);

	private:
		GUIManager& m_guiManager;

	};

	class SubtreesInsertedEventHandler : public GUIVisitor {
	public:
		SubtreesInsertedEventHandler(GUIManager& guiManager);
		~SubtreesInsertedEventHandler();

		void visit(GUIStateNode_ptr guiStateNode);

	private:
		GUIManager& m_guiManager;

	};

	class SubtreesUpdatedEventHandler : public GUIVisitor {
	public:
		SubtreesUpdatedEventHandler(GUIManager& guiManager);
		~SubtreesUpdatedEventHandler();

		void visit(GUIStateNode_ptr guiStateNode);

	private:
		GUIManager& m_guiManager;

	};

	int m_counter;
	ContextMenuControl* m_contextMenuControl;
	DrawManager m_drawManager;
	unordered_map<shared_ptr<void>, GUIStateNode_ptr> m_guiStateNodes;
	DefaultSceneGraphExplorerListener m_sceneGraphExplorerListener;
	MainWindow m_mainWindow;
	SceneGraphExplorerPanel* m_sceneGraphExplorerPanel;
	DefaultSceneListener m_sceneListener;
	SceneManager_ptr m_sceneManager;
	SubtreesInsertedEventHandler m_subtreesInsertedEventHandler;
	SubtreesRemovedEventHandler m_subtreesRemovedEventHandler;
	SubtreesUpdatedEventHandler m_subtreesUpdatedEventHandler;
	ToolPanel* m_toolPanel;

	template<class G, class S, class F, class M>
	void doInsert3D(shared_ptr<G> geometry, const char* label, F* form, M* contextMenu = NULL);
	template<class G>
	void doUpdate3D(shared_ptr<G> geometry);

};

#endif // GUI_MANAGER_H


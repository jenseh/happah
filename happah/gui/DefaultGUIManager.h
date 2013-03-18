#ifndef DEFAULT_GUI_MANAGER_H
#define DEFAULT_GUI_MANAGER_H

#include <QListWidgetItem>
#include <unordered_map>

using namespace std;

#include "happah/gui/DrawManager.h"
#include "happah/gui/GUIManager.h"
#include "happah/gui/MainWindow.h"
#include "happah/gui/SceneGraphExplorerListener.h"
#include "happah/gui/SceneGraphExplorerPanel.h"
#include "happah/gui/ToolPanel.h"
#include "happah/gui/Viewport3DListener.h"
#include "happah/gui/context-menus/ContextMenu.h"
#include "happah/scene/SceneManager.h"

class DefaultGUIManager : public GUIManager {

public:
	DefaultGUIManager(SceneManager_ptr sceneManager);
	~DefaultGUIManager();

	bool init();
	void insert(InvoluteGear_ptr involuteGear);
	void insert(Plane_ptr plane);
	void insert(SimpleGear_ptr simpleGear);
	void insert(DiscGearGrindResult simulationResult);
	void insert(Disc_ptr disc);
	void insert(Worm_ptr worm);
	void update(DiscGearGrindResult simulationResult);
	void update(InvoluteGear_ptr involuteGear);
	void update(Plane_ptr plane);
	void update(SimpleGear_ptr simpleGear);
	void update(Disc_ptr disc);
	void update(Worm_ptr worm);

private:
	class DefaultSceneGraphExplorerListener : public SceneGraphExplorerListener {
	public:
		DefaultSceneGraphExplorerListener(DefaultGUIManager& defaultGUIManager);
		~DefaultSceneGraphExplorerListener();

		void handleGUIStateNodesDeletedEvent(vector<GUIStateNode_ptr>& guiStateNodes);
		void handleGUIStateNodeSelectedEvent(GUIStateNode_ptr guiStateNode);

	private:
		DefaultGUIManager& m_defaultGUIManager;

	};

	class DefaultSceneListener : public SceneListener {
	public:
		DefaultSceneListener(DefaultGUIManager& defaultGUIManager);
		~DefaultSceneListener();

		void handleSubtreeInsertedEvent(Node_ptr root);
		void handleSubtreesInsertedEvent(vector<Node_ptr>& roots);
		void handleSubtreeRemovedEvent(Node_ptr root);
		void handleSubtreesRemovedEvent(vector<Node_ptr>& roots);
		void handleSubtreeUpdatedEvent(Node_ptr root);
		void handleSubtreesUpdatedEvent(vector<Node_ptr>& roots);

	private:
		DefaultGUIManager& m_defaultGUIManager;
	};

	class DefaultViewport3DListener : public Viewport3DListener {
	public:
		DefaultViewport3DListener(DefaultGUIManager& defaultGUIManager);
		~DefaultViewport3DListener();

		void handleMouseClickEvent(Ray& ray);

	private:
		DefaultGUIManager& m_defaultGUIManager;
	};

	class SubtreesRemovedEventHandler : public GUIVisitor {
	public:
		SubtreesRemovedEventHandler(DefaultGUIManager& defaultGUIManager);
		~SubtreesRemovedEventHandler();

		void visit(GUIStateNode_ptr guiStateNode);

	private:
		DefaultGUIManager& m_defaultGUIManager;

	};

	class SubtreesInsertedEventHandler : public GUIVisitor {
	public:
		SubtreesInsertedEventHandler(DefaultGUIManager& defaultGUIManager);
		~SubtreesInsertedEventHandler();

		void visit(GUIStateNode_ptr guiStateNode);

	private:
		DefaultGUIManager& m_defaultGUIManager;

	};

	class SubtreesUpdatedEventHandler : public GUIVisitor {
	public:
		SubtreesUpdatedEventHandler(DefaultGUIManager& defaultGUIManager);
		~SubtreesUpdatedEventHandler();

		void visit(GUIStateNode_ptr guiStateNode);

	private:
		DefaultGUIManager& m_defaultGUIManager;

	};

	int m_counter;
	DrawManager m_drawManager;
	unordered_map<shared_ptr<void>, GUIStateNode_ptr> m_guiStateNodes;
	DefaultSceneGraphExplorerListener m_sceneGraphExplorerListener;
	DefaultViewport3DListener m_viewport3DListener;
	MainWindow m_mainWindow;
	SceneGraphExplorerPanel* m_sceneGraphExplorerPanel;
	DefaultSceneListener m_sceneListener;
	SceneManager_ptr m_sceneManager;
	SubtreesInsertedEventHandler m_subtreesInsertedEventHandler;
	SubtreesRemovedEventHandler m_subtreesRemovedEventHandler;
	SubtreesUpdatedEventHandler m_subtreesUpdatedEventHandler;
	ToolPanel* m_toolPanel;


	template<class G, class S>
	void doInsert3D(shared_ptr<G> geometry, shared_ptr<S> guiStateNode);
	template<class G, class S, class F>
	void doInsert3D(shared_ptr<G> geometry, const char* label, F* form);
	template<class G, class S, class F, class M>
	void doInsert3D(shared_ptr<G> geometry, const char* label, F* form, M* contextMenu);

	template<class G>
	void doUpdate3D(shared_ptr<G> geometry);

	string toFinalLabel(const char* label);

};

#endif // DEFAULT_GUI_MANAGER_H


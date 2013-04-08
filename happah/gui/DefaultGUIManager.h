#ifndef DEFAULT_GUI_MANAGER_H
#define DEFAULT_GUI_MANAGER_H

#include <QListWidgetItem>
#include <QThread>
#include <unordered_map>

using namespace std;

#include "happah/gui/DrawManager.h"
#include "happah/gui/GUIManager.h"
#include "happah/gui/DiscGearGrindWorker.h"
#include "happah/gui/MainWindow.h"
#include "happah/gui/SceneGraphExplorerListener.h"
#include "happah/gui/SceneGraphExplorerPanel.h"
#include "happah/gui/ToolPanel.h"
#include "happah/gui/ViewportListener.h"
#include "happah/gui/context-menus/ContextMenu.h"
#include "happah/scene/RayIntersectionVisitor.h"
#include "happah/scene/SceneManager.h"

class DefaultGUIManager : public GUIManager {

public:
	DefaultGUIManager(SceneManager_ptr sceneManager);
	~DefaultGUIManager();

	void createDiscGearGrind(SimpleGear_ptr gear);
	void generateDisc(CylindricalGear_ptr cylindricalGear);
	bool init();
	void insert(BSplineCurve_ptr bSplineCurve, hpuint drawMode = HP_TRIANGLE_MESH);
	void insert(BSplineCurve_ptr bSplineCurve, Plane_ptr plane, hpuint drawMode = HP_TRIANGLE_MESH);
    void insert(SurfaceOfRevolution_ptr disc,hpuint drawMode = HP_TRIANGLE_MESH);
	//void insert(DiscGearGrindResult simulationResult);
    void insert(DiscGearGrind_ptr discGearGrind);
	void insert(InvoluteGear_ptr involuteGear,hpuint drawMode = HP_TRIANGLE_MESH);
	void insert(Plane_ptr plane, BSplineCurve_ptr curve);
	void insert(Plane_ptr plane, hpuint drawMode = HP_TRIANGLE_MESH);
	void insert(SimpleGear_ptr simpleGear,hpuint drawMode = HP_TRIANGLE_MESH);
	void insert(SpherePatch_ptr spherePatch,hpuint drawMode = HP_TRIANGLE_MESH);
	void insert(Worm_ptr worm,hpuint drawMode = HP_TRIANGLE_MESH);
	void update(BSplineCurve_ptr bSplineCurve);
    //void update(DiscGearGrindResult simulationResult);
    void update(SurfaceOfRevolution_ptr disc);
	void update(InvoluteGear_ptr involuteGear);
	void update(Plane_ptr plane);
	void update(SimpleGear_ptr simpleGear);
	void update(SpherePatch_ptr spherePatch);
	void update(Worm_ptr worm);
	void useForBSpline(Plane_ptr plane);
	void useInSimulation(SurfaceOfRevolution_ptr disc,TriangleMesh_ptr discMesh);
	void useInSimulation(SimpleGear_ptr gear, TriangleMesh_ptr gearMesh);
	void visitScene(SceneVisitor& visitor);
	void visitScene(SimulationVisitor& visitor);
	const SceneManager_ptr getSceneManager();
	virtual Plane_ptr getParentPlane(BSplineCurve_ptr bSplineCurve);

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

	class DefaultViewportListener : public ViewportListener {
	public:
		DefaultViewportListener(DefaultGUIManager& defaultGUIManager);
		~DefaultViewportListener();

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
	DefaultViewportListener m_viewportListener;
	MainWindow m_mainWindow;
	SceneGraphExplorerPanel* m_sceneGraphExplorerPanel;
	DefaultSceneListener m_sceneListener;
	SceneManager_ptr m_sceneManager;
	SubtreesInsertedEventHandler m_subtreesInsertedEventHandler;
	SubtreesRemovedEventHandler m_subtreesRemovedEventHandler;
	SubtreesUpdatedEventHandler m_subtreesUpdatedEventHandler;
	ToolPanel* m_toolPanel;


	template<class G, class S>
	void doInsert2D(shared_ptr<G> geometry, shared_ptr<S> guiStateNode);
	template<class G, class S, class F>
	void doInsert2D(shared_ptr<G> geometry, const char* label, F* form);
	template<class G, class S, class F, class M>
	void doInsert2D(shared_ptr<G> geometry, const char* label, F* form, M* contextMenu);
	template<class G, class S>
	void doInsert1D(shared_ptr<G> geometry, shared_ptr<S> guiStateNode);
	template<class G, class S, class F>
	void doInsert1D(shared_ptr<G> geometry, const char* label, F* form);
	template<class G, class S, class F, class M>
	void doInsert1D(shared_ptr<G> geometry, const char* label, F* form, M* contextMenu);
	template<class G, class S>
	void doInsert0D(shared_ptr<G> geometry, shared_ptr<S> guiStateNode);
	template<class G, class S, class F>
	void doInsert0D(shared_ptr<G> geometry, const char* label, F* form);
	template<class G, class S, class F, class M>
	void doInsert0D(shared_ptr<G> geometry, const char* label, F* form, M* contextMenu);
	template<class G>
	void doUpdate2D(shared_ptr<G> geometry);

	string toFinalLabel(const char* label);

};

#endif // DEFAULT_GUI_MANAGER_H


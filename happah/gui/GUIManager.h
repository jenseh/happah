#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include "happah/geometries/InvoluteSpurGear.h"
#include "happah/geometries/TriangleMesh.h"
#include "happah/gui/DrawManager.h"
#include "happah/gui/MainWindow.h"
#include "happah/scene/SceneManager.h"

class GUIManager {
public:
	GUIManager(SceneManager& sceneManager);
	~GUIManager();

	bool init();
	void insert(InvoluteGear_ptr involuteGear);
	void update(InvoluteGear_ptr involuteGear);

private:
	DrawManager m_drawManager;
	TriangleMesh_ptr m_lastInvoluteGearMesh;
	MainWindow m_mainWindow;
	SceneManager& m_sceneManager;

};


#endif // GUI_MANAGER_H

#ifndef TRIANGLE_MESH_CONTEXT_MENU_H
#define TRIANGLE_MESH_CONTEXT_MENU_H

#include "happah/geometries/TriangleMesh.h"
#include "happah/gui/context-menus/ContextMenu.h"
#include "happah/gui/GUIManager.h"

class TriangleMeshContextMenu : public ContextMenu {
Q_OBJECT

public:
	TriangleMeshContextMenu(GUIManager& guiManager, QWidget* parent);
	~TriangleMeshContextMenu();

	void setTriangleMesh(TriangleMesh3D_ptr triangleMesh);

private:
	GUIManager& m_guiManager;
	TriangleMesh3D_ptr m_triangleMesh;

private slots:
	void createRayCloud();

};
#endif //TRIANGLE_MESH_CONTEXT_MENU_H

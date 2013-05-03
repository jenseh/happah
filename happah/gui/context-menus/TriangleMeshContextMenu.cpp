#include <QAction>

#include "happah/HappahTypes.h"
#include "happah/gui/context-menus/TriangleMeshContextMenu.h"

TriangleMeshContextMenu::TriangleMeshContextMenu(GUIManager& guiManager, QWidget* parent = 0) : ContextMenu(parent), m_guiManager(guiManager) {
	QAction* createRayCloudAction = new QAction(tr("Create ray cloud"), this);
	addAction(createRayCloudAction);
	connect(createRayCloudAction, SIGNAL(triggered()), this, SLOT(createRayCloud()) );
}

TriangleMeshContextMenu::~TriangleMeshContextMenu() {}

void TriangleMeshContextMenu::createRayCloud() {
	RayCloud3D* rayCloud = m_triangleMesh->getVerticesAndNormals();
	//TODO: m_guiManager.
}

void TriangleMeshContextMenu::setTriangleMesh(TriangleMesh3D_ptr triangleMesh) {
	m_triangleMesh = triangleMesh;
}

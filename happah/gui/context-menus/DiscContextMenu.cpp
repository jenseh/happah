#include "DiscContextMenu.h"

DiscContextMenu::DiscContextMenu(
	GUIManager& guiManager,
	QWidget* parent
) : ContextMenu(parent),
	m_guiManager(guiManager) {

	QAction* useDiscInSumulationAction = new QAction(tr("Use in simulation"), this);
	addAction(useDiscInSumulationAction);
	connect(useDiscInSumulationAction, SIGNAL(triggered()), this, SLOT(useDiscInSumulation()));
}

DiscContextMenu::~DiscContextMenu(){}

void DiscContextMenu::useDiscInSumulation() {
	m_guiManager.useInSimulation(m_disc, m_discMesh);

}

void DiscContextMenu::setDisc(SurfaceOfRevolution_ptr disc, TriangleMesh_ptr discMesh) {
	m_disc = disc;
	m_discMesh = discMesh;
}

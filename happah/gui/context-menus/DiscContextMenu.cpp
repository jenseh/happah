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
	m_guiManager.useInSimulation(m_disc);

}

void DiscContextMenu::setDisc(Disc_ptr disc) {
	m_disc = disc;
}

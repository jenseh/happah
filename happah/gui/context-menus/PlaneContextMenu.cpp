#include "PlaneContextMenu.h"

PlaneContextMenu::PlaneContextMenu
	(GUIManager& guiManager, QWidget* parent )
	: ContextMenu(parent), m_guiManager(guiManager)
{

	QAction* usePlaneForBSpline = new QAction(tr("Use for BSplineCurve"), this);
	addAction(usePlaneForBSpline);
	connect( usePlaneForBSpline, SIGNAL(triggered()), this, SLOT(setPlaneForBSpline()) );
}

PlaneContextMenu::~PlaneContextMenu(){}

void PlaneContextMenu::setPlaneForBSpline(){
	m_guiManager.useForBSpline(m_plane);
}

void PlaneContextMenu::setPlane(Plane_ptr plane) {
	m_plane = plane;
}

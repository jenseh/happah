#include <QMessageBox>

#include "happah/gui/context-menus/BSplineCurveContextMenu.h"

BSplineCurveContextMenu::BSplineCurveContextMenu(
	GUIManager& guiManager,
	QWidget* parent
) : ContextMenu(parent),
	m_guiManager(guiManager) {

	QAction* toGearAction = new QAction(tr("Take curve as tooth of a gear"), this);
	addAction(toGearAction);
	connect(toGearAction, SIGNAL(triggered()), this, SLOT(createGearToothOfCurve()));

}

BSplineCurveContextMenu::~BSplineCurveContextMenu() {}

void BSplineCurveContextMenu::setBSplineCurve(BSplineCurve_ptr curve) {
	m_curve = curve;
}

void BSplineCurveContextMenu::createGearToothOfCurve() {

	if(!m_curve->getClamped()) {
		QMessageBox messageBox;
		messageBox.setText("The chosen Curve is not clamped!");
		messageBox.setInformativeText(
			"When your curve is not clamped to first and last control points you may get a resulting gear that may look againt your expectations. Do you really want to take this curve as tooth?");
		messageBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);

		messageBox.setDefaultButton(QMessageBox::Cancel);
		int answer = messageBox.exec();
		if(answer == QMessageBox::Cancel)
			return;
	}
	ToothProfile* toothProfile = new ToothProfile(*m_curve);
	ToothProfile_ptr toothP = ToothProfile_ptr(toothProfile);
	m_guiManager.insert(toothP, 0x00000006);
}

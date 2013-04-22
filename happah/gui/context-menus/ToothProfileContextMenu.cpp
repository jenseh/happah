#include <memory>
#include <QAction>

#include "happah/gui/context-menus/ToothProfileContextMenu.h"
#include "happah/geometries/BSplineCurve.h"
#include "happah/geometries/gears/SimpleGear.h"

ToothProfileContextMenu::ToothProfileContextMenu(GUIManager& guiManager, QWidget* parent) 
  : ContextMenu(parent),
	m_guiManager(guiManager) {

	QAction* createSimpleGearAction = new QAction(tr("Create a 3D gear of profile"), this);
	addAction(createSimpleGearAction);
	connect(createSimpleGearAction, SIGNAL(triggered()), this, SLOT(createSimpleGear()));

	QAction* newBSplineCurveAction = new QAction(tr("Edit one tooth of gear"), this);
	addAction(newBSplineCurveAction);
	connect(newBSplineCurveAction, SIGNAL(triggered()), this, SLOT(newBSplineCurve()));

}
ToothProfileContextMenu::~ToothProfileContextMenu() {}

void ToothProfileContextMenu::createSimpleGear() {
	SimpleGear_ptr simpleGear = SimpleGear_ptr(new SimpleGear(*m_toothProfile, 0.0f, 2.0f));
	m_guiManager.insert(simpleGear, 0x00000001); //Attention please: ToothProfiles are connected!
}

void ToothProfileContextMenu::newBSplineCurve() {
	BSplineCurve<hpvec3>* curve = new BSplineCurve<hpvec3>(m_toothProfile->getCurve());
	BSplineCurve_ptr bSplineCurve = BSplineCurve_ptr(curve);
	m_guiManager.insert(bSplineCurve, 0x00000006);
}

void ToothProfileContextMenu::setToothProfile(ToothProfile_ptr toothProfile) {
	m_toothProfile = toothProfile;
}

#include <memory>
#include <QAction>

#include "happah/gui/context-menus/ToothProfileContextMenu.h"
#include "happah/geometries/BSplineCurve.h"
#include "happah/geometries/gears/MatingGearConstructor.h"
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

	QAction* createMatingGearAction = new QAction(tr("Construct a mating gear"), this);
	addAction(createMatingGearAction);
	connect(createMatingGearAction, SIGNAL(triggered()), this, SLOT(createMatingGear()));


}
ToothProfileContextMenu::~ToothProfileContextMenu() {}

void ToothProfileContextMenu::createMatingGear() {
	MatingGearConstructor matingGearConstructor;
	hpreal radius = 0.5f * m_toothProfile->getRootRadius() + 0.5f * m_toothProfile->getTipRadius();
	matingGearConstructor.constructMatingTo(*m_toothProfile, radius, m_toothProfile->getNumberOfTeeth(), 30, 5.0f);
	std::list< BSplineCurve<hpvec2>* >* informationCurves = matingGearConstructor.getInformationSplines();
	for(std::list< BSplineCurve<hpvec2>* >::iterator it = informationCurves->begin(), end = informationCurves->end(); it != end; ++it) {
		BSplineCurve2D_ptr curve = BSplineCurve2D_ptr((*it)); //TODO: insert with 2D?
		m_guiManager.insert(curve, HP_LINE_MESH | HP_POINT_CLOUD );
//		delete *it;
	}
}

void ToothProfileContextMenu::createSimpleGear() {
	SimpleGear_ptr simpleGear = SimpleGear_ptr(new SimpleGear(*m_toothProfile, 0.0f, 2.0f));
	m_guiManager.insert(simpleGear, HP_TRIANGLE_MESH ); //Attention please: ToothProfiles are connected!
}

void ToothProfileContextMenu::newBSplineCurve() {
	BSplineCurve<hpvec2>* curve = new BSplineCurve<hpvec2>();
	m_toothProfile->getCurve(*curve);
	BSplineCurve2D_ptr bSplineCurve = BSplineCurve2D_ptr(curve);
	m_guiManager.insert(bSplineCurve, HP_LINE_MESH | HP_POINT_CLOUD );
}

void ToothProfileContextMenu::setToothProfile(ToothProfile_ptr toothProfile) {
	m_toothProfile = toothProfile;
}

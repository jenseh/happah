#include <memory>
#include <vector>
#include <QAction>

#include "happah/gui/context-menus/ToothProfileContextMenu.h"
#include "happah/geometries/BSplineCurve.h"
#include "happah/geometries/gears/matinggear/MatingGearConstructor.h"
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

	// MatingGearConstructor matingGearConstructor;
	// hpreal radius = 0.5f * m_toothProfile->getRootRadius() + 0.5f * m_toothProfile->getTipRadius();
	// matingGearConstructor.constructMatingTo(*m_toothProfile, radius, m_toothProfile->getNumberOfTeeth(), 30, 5.0f, 0.5f);
	// std::list< MatingGearInformationPart* >* informationCurves = matingGearConstructor.getInformationSplines();
	// // std::list<char*>* informationNames = matingGearConstructor.getInformationSplineNames();
	// // std::list<char*>::iterator nameIt = informationNames->begin();

	// std::vector<hpcolor> splineColors(informationCurves->size());
	// hpreal adaption = (255.0f * 3) / splineColors.size();
	// for(hpuint counter = 0; counter < splineColors.size(); ++counter) {
	// 	hpuint adaptedCounter = (counter * adaption);
	// 	hpuint red, green, blue;
	// 	if(adaptedCounter / 256 <= 0) {
	// 		red = adaptedCounter;
	// 		green = 255 - adaptedCounter / 2;
	// 		blue = 255 - adaptedCounter / 2;
	// 	} else if (adaptedCounter / 256 <= 1) {
	// 		red = 255 - (adaptedCounter - 256) / 2;
	// 		green = adaptedCounter - 256;
	// 		blue = 255 - (adaptedCounter - 256) / 2;
	// 	} else {
	// 		red = 255 - (adaptedCounter - 512) / 2;
	// 		green = 255 - (adaptedCounter - 512) / 2;
	// 		blue = adaptedCounter - 512;
	// 	}
	// 	hpcolor color = hpcolor(red, green, blue, 255) * (1.0f / 255.0f);
	// 	splineColors[counter] = color;
	// }
	// hpuint counter = 0;
	// for(std::list< MatingGearInformationPart* >::iterator it = informationCurves->begin(), end = informationCurves->end(); it != end; ++it) {
	// 	BSplineCurve2D_ptr curve2d = (*it)->getCurve(); //TODO: insert with 2D?
	// 	m_guiManager.insert(curve2d, (*it)->getName(), splineColors[counter], HP_LINE_MESH | HP_POINT_CLOUD);
	// 	// delete *it;
	// 	++counter;
	// }
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

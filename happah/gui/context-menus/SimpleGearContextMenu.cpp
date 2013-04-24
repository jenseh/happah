#include "SimpleGearContextMenu.h"
#include "happah/geometries/BSplineCurve.h"
#include "happah/geometries/gears/ToothProfile.h"

SimpleGearContextMenu::SimpleGearContextMenu(
	GUIManager& guiManager,
	QWidget* parent
) : ContextMenu(parent),
	m_guiManager(guiManager) {

	QAction* createDiscGearGrind = new QAction(tr("Create disc gear grind"), this);
	addAction(createDiscGearGrind);
	connect(createDiscGearGrind, SIGNAL(triggered()), this, SLOT(createDiscGearGrind()));

	QAction* generateDiscAction = new QAction(tr("Generate disc"), this);
	addAction(generateDiscAction);
	connect(generateDiscAction, SIGNAL(triggered()), this, SLOT(generateDisc()));

	QAction* createCurveOfProfileAction = new QAction(tr("Create curve of the profile"), this);
	addAction(createCurveOfProfileAction);
	connect(createCurveOfProfileAction, SIGNAL(triggered()), this, SLOT(createCurveOfProfile()));

	QAction* createToothProfileAction = new QAction(tr("Create curve as tooth profile"), this);
	addAction(createToothProfileAction);
	connect(createToothProfileAction, SIGNAL(triggered()), this, SLOT(createToothProfile()));

}

SimpleGearContextMenu::~SimpleGearContextMenu() {}

void SimpleGearContextMenu::createDiscGearGrind() {
	// Make a copy for both threads
	SimpleGear_ptr simpleGear = SimpleGear_ptr(new SimpleGear(*m_simpleGear));
	m_guiManager.createDiscGearGrind(simpleGear);
}

void SimpleGearContextMenu::createCurveOfProfile() {
	BSplineCurve<hpvec2>* profile = new BSplineCurve<hpvec2>();
	m_simpleGear->getTraverseProfile(0.0f, *profile);
	BSplineCurve2D_ptr gearProfile = BSplineCurve2D_ptr(profile);
	m_guiManager.insert(gearProfile, HP_LINE_MESH | HP_POINT_CLOUD );
}

void SimpleGearContextMenu::createToothProfile() {
	ToothProfile* profile = new ToothProfile(m_simpleGear->getToothProfile());
	ToothProfile_ptr toothProfile = ToothProfile_ptr(profile);
	m_guiManager.insert(toothProfile, HP_LINE_MESH | HP_POINT_CLOUD );
}

void SimpleGearContextMenu::generateDisc() {
	m_guiManager.generateDisc(m_simpleGear);
}

void SimpleGearContextMenu::setSimpleGear(SimpleGear_ptr simpleGear, TriangleMesh_ptr simpleGearMesh) {
	m_simpleGear = simpleGear;
	m_simpleGearMesh = simpleGearMesh;
}

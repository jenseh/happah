#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include <iostream>
#include "happah/geometries/gears/SimpleGear.h"
#include "happah/geometries/BSplineCurve.h"
#include "happah/gui/forms/ToothProfileForm.h"

using namespace std;

ToothProfileForm::ToothProfileForm(GUIManager& guiManager, QWidget* parent)
	: Form(parent), m_guiManager(guiManager), m_pointMoving(-1) {

	QPushButton* show3dGearButton = new QPushButton("Show gear in 3D");
	connect(show3dGearButton, SIGNAL(clicked()), this, SLOT(toSimpleGear()));

	QPushButton* matingGearButton = new QPushButton("Construct mating gear");
	connect(matingGearButton, SIGNAL(clicked()), this, SLOT(showMatingGear()));

	QPushButton* matingStepButton = new QPushButton("Next mating gear step");
	connect(matingStepButton, SIGNAL(clicked()), this, SLOT(showNextMatingStep()));

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(show3dGearButton);
	layout->addWidget(matingGearButton);
	layout->addWidget(matingStepButton);
	this->setLayout(layout);
}

ToothProfileForm::~ToothProfileForm() {

}


ToothProfile_ptr ToothProfileForm::getToothProfile() {
	return m_toothProfile;
}

void ToothProfileForm::reset() {
	BSplineCurve curve;
	m_toothProfile = ToothProfile_ptr(new ToothProfile(curve));
}

void ToothProfileForm::setToothProfile(ToothProfile_ptr toothProfile) {
	m_toothProfile = toothProfile;
}

// void BSplineTool::addCurveOptions() {
// 	QPushButton* toGear = new QPushButton("Take as tooth of a gear");
// 	connect(toGear, SIGNAL(clicked()), this, SLOT(toGearCurve()));
// 	m_options->addWidget(toGear);
// }
// void BSplineTool::toGearCurve() {
// 	BSplineGearCurve* gearCurve = new BSplineGearCurve(*m_currentCurve);
// 	deleteCurrentAndEmitNew(gearCurve);
// 	m_currentCurve = gearCurve;
// 	emit changed();
// }

void ToothProfileForm::toSimpleGear() {
	// SimpleGear* gear = new SimpleGear(new BSplineGearCurve(*m_currentCurve), 0.0f, 0.2f);
	// TriangleMesh* gearMesh = gear->toTriangleMesh();
	// gearMesh->setMaterial(0.25f, 0.5f, 1.0f, 10.0f); //ka, kd, ks, phong
	// RenderItem3D* item3d = new RenderItem3D(gear, gearMesh, m_currentCurve->getName());
	// deleteCurrentAndEmitNew(item3d);
}
void ToothProfileForm::showMatingGear() {
	// BSplineGearCurve* gearCurve = new BSplineGearCurve(*m_currentCurve);
	// std::cerr << "BSplineTool::showMatingGear 1" << std::endl;
	// MatingGear* matingGear = new MatingGear(gearCurve, gearCurve->getMiddleLength(), gearCurve->getToothCount(), 30);
	// std::cerr << "BSplineTool::showMatingGear 1" << std::endl;
	// std::vector<BSplineCurve*> gearComponents = matingGear->getBSplines();
	// std::cerr << "BSplineTool::showMatingGear 1" << std::endl;
	// for(unsigned int i = 0; i < gearComponents.size(); ++i) {
	// 	usleep(8000);
	// 	emitComponent(gearComponents[i]);
	// 	std::cerr << "sleep over" << std::endl;
	// }
}

void ToothProfileForm::showNextMatingStep() {
	// BSplineGearCurve* gearCurve = new BSplineGearCurve(*m_currentCurve);
	// MatingGear* matingGear = new MatingGear(gearCurve, gearCurve->getMiddleLength(), gearCurve->getToothCount(), 30);
	// if(gearComponents.empty())
	// gearComponents = matingGear->getBSplines();
	// emitComponent(gearComponents[m_step]);
	// if(++m_step == gearComponents.size())
	// 	deleteOptions();
}

void ToothProfileForm::handleRay(Ray& ray) {
	// hpvec3 intersecPoint;
	// if( m_plane->intersect( ray, intersecPoint ) ) {
	// 	m_controlPointInput->setValue( intersecPoint );
	// 	addPoint();
	// }
}

void ToothProfileForm::handleMove(Ray& ray) {
	// if(m_pointMoving < 0) {
	// 	hpreal minDistance = 1000000.0f;
	// 	int nearestPointIndex = -1;
	// 	for(hpuint i = 0; i < m_curve->getNumberOfControlPoints(); ++i) {
	// 		hpvec3 controlPoint = m_curve->getControlPoint( i );
	// 		hpreal distance = ray.distanceToPoint( controlPoint );
	// 		if( distance < minDistance ) {
	// 			minDistance = distance;
	// 			nearestPointIndex = i;
	// 		}
	// 	}
	// 	m_pointMoving = nearestPointIndex;
	// }
	// if( m_pointMoving >= 0 ) {
	// 	hpvec3 intersecPoint;
	// 	if( m_plane->intersect( ray, intersecPoint ) ) {
	// 		m_curve->setControlPoint( m_pointMoving, intersecPoint );
	// 		m_guiManager.update( m_curve );
	// 	}
	// }
}

void ToothProfileForm::handleMoveStop() {
	// m_pointMoving = -1;
}
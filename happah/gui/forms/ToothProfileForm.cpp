#include <QLabel>
#include <QVBoxLayout>

#include <iostream>
#include <list>
#include "happah/geometries/gears/MatingGearConstructor.h"
#include "happah/geometries/gears/SimpleGear.h"
#include "happah/geometries/BSplineCurve.h"
#include "happah/gui/forms/ToothProfileForm.h"

using namespace std;

ToothProfileForm::ToothProfileForm(GUIManager& guiManager, QWidget* parent)
	: Form(parent), m_currentPointIndex(-1), m_guiManager(guiManager), m_errorColor(hpcolor(1.0f, 0.0f, 0.0f, 0.5f)) {

	QPushButton* show3dGearButton = new QPushButton("Show gear in 3D");
	connect(show3dGearButton, SIGNAL(clicked()), this, SLOT(toSimpleGear()));

	QPushButton* matingGearButton = new QPushButton("Construct mating gear");
	connect(matingGearButton, SIGNAL(clicked()), this, SLOT(createMatingGear()));

	m_matingStepButton = new QPushButton("Next mating gear step");
	connect(m_matingStepButton, SIGNAL(clicked()), this, SLOT(showNextMatingStep()));

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(show3dGearButton);
	layout->addWidget(matingGearButton);
	layout->addWidget(m_matingStepButton);
	this->setLayout(layout);

	reset();
}

ToothProfileForm::~ToothProfileForm() {

}


ToothProfile_ptr ToothProfileForm::getToothProfile() {
	return m_toothProfile;
}

void ToothProfileForm::reset() {
	m_toothProfile = ToothProfile_ptr(new ToothProfile());
	m_plane = Plane_ptr(m_toothProfile->getPlaneToothProfileLiesIn());
	m_informationCurves = nullptr; //new std::list< MatingGearInformationPart* >();
	m_splineColors = nullptr; //std::vector<hpcolor>();
	m_matingStepButton->setEnabled(true);
}

void ToothProfileForm::setToothProfile(ToothProfile_ptr toothProfile) {
	m_toothProfile = toothProfile;
}

void ToothProfileForm::toSimpleGear() {
	// SimpleGear* gear = new SimpleGear(new BSplineGearCurve(*m_currentCurve), 0.0f, 0.2f);
	// TriangleMesh* gearMesh = gear->toTriangleMesh();
	// gearMesh->setMaterial(0.25f, 0.5f, 1.0f, 10.0f); //ka, kd, ks, phong
	// RenderItem3D* item3d = new RenderItem3D(gear, gearMesh, m_currentCurve->getName());
	// deleteCurrentAndEmitNew(item3d);
}
void ToothProfileForm::createMatingGear() {
	// for(unsigned int i = 0; i < gearComponents.size(); ++i) {
	// 	usleep(8000);
	// 	emitComponent(gearComponents[i]);
	// 	std::cerr << "sleep over" << std::endl;
	// }
	if(!m_informationCurves || !m_splineColors)
		constructMatingGear();

	hpuint counter = 0;
	for(std::list< MatingGearInformationPart* >::iterator it = m_informationCurves->begin(), end = m_informationCurves->end(); it != end; ++it) {
		BSplineCurve2D_ptr curve2d = (*it)->getCurve(); //TODO: insert with 2D?
		m_guiManager.insert(curve2d, (*it)->getName(), (*m_splineColors)[counter], HP_LINE_MESH | HP_POINT_CLOUD);

		++counter;
	}
}

void ToothProfileForm::constructMatingGear() {
	MatingGearConstructor matingGearConstructor;
	hpreal radius = 0.5f * m_toothProfile->getRootRadius() + 0.5f * m_toothProfile->getTipRadius();
	matingGearConstructor.constructMatingTo(*m_toothProfile, radius, m_toothProfile->getNumberOfTeeth(), 30, 5.0f, 0.5f);

	m_informationCurves = matingGearConstructor.getInformationSplines();
	m_splineColors = new std::vector<hpcolor>(m_informationCurves->size());

	hpreal adaption = (255.0f * 3) / m_splineColors->size();
	for(hpuint counter = 0; counter < m_splineColors->size(); ++counter) {
		hpuint adaptedCounter = (counter * adaption);
		hpuint red, green, blue;
		if(adaptedCounter / 256 <= 0) {
			red = adaptedCounter;
			green = 255 - adaptedCounter / 2;
			blue = 255 - adaptedCounter / 2;
		} else if (adaptedCounter / 256 <= 1) {
			red = 255 - (adaptedCounter - 256) / 2;
			green = adaptedCounter - 256;
			blue = 255 - (adaptedCounter - 256) / 2;
		} else {
			red = 255 - (adaptedCounter - 512) / 2;
			green = 255 - (adaptedCounter - 512) / 2;
			blue = adaptedCounter - 512;
		}
		hpcolor color = hpcolor(red, green, blue, 255) * (1.0f / 255.0f);
		(*m_splineColors)[counter] = color;
	}
}

void ToothProfileForm::showNextMatingStep() {
	hpcolor halfVisible = hpcolor(1.0f, 1.0f, 0.8f, 0.5f);
	if(!m_informationCurves || !m_splineColors) {
		constructMatingGear();
		m_stepCounter = 0;
		m_stepIterator = m_informationCurves->begin();
	}
	if(m_stepIterator == m_informationCurves->end() || m_stepCounter == m_splineColors->size()) {
		m_matingStepButton->setEnabled(false);
	} else {

		BSplineCurve2D_ptr curve2d = (*m_stepIterator)->getCurve();

		if((*m_stepIterator)->getError() == ErrorCode::NO_CUT_WITH_REFERENCE_RADIUS) {
			m_guiManager.insert(curve2d, (*m_stepIterator)->getName(), m_errorColor * halfVisible, HP_LINE_MESH | HP_POINT_CLOUD);
			++m_stepCounter;
			++m_stepIterator;

		} else {
			BSplineCurve2D_ptr curve2d = (*m_stepIterator)->getCurve();
			char* name = (*m_stepIterator)->getName();
			MatingGearPart part = (*m_stepIterator)->getPart();
			hpcolor color = (*m_splineColors)[m_stepCounter];
			++m_stepCounter;
			++m_stepIterator;
			
			switch(part) {
				case MatingGearPart::MATING_REFERENCE_CIRCLE:
					m_guiManager.insert(curve2d, name, color, HP_LINE_MESH);
					return;
				case MatingGearPart::ORIGIN_REFERENCE_CIRCLE:
					m_guiManager.insert(curve2d, name, color * halfVisible, HP_LINE_MESH);
					return;
				case MatingGearPart::MATING_NORMAL:
					m_guiManager.insert(curve2d, name, color, HP_LINE_MESH | HP_POINT_CLOUD);
					return;
				case MatingGearPart::ORIGIN_NORMAL:
					m_guiManager.insert(curve2d, name, color * halfVisible, HP_LINE_MESH | HP_POINT_CLOUD);
					return;
				case MatingGearPart::MATING_TOOTH_PROFILE:
					m_guiManager.insert(curve2d, name, color, HP_LINE_MESH | HP_POINT_CLOUD);
					return;
				case MatingGearPart::ORIGIN_TOOTH_PROFILE:
					m_guiManager.insert(curve2d, name, color * halfVisible, HP_LINE_MESH | HP_POINT_CLOUD);
					return;
			}
		}
	}
}

void ToothProfileForm::handleRay(Ray& ray) {
	// hpvec3 intersecPoint;
	// if(m_plane->intersect(ray, intersecPoint)) {
	// 	m_controlPointInput->setValue( intersecPoint );
	// 	addPoint();
	// }
}

void ToothProfileForm::handleDrag(Ray& ray) {
	hpvec3 intersectionPoint;
	if(m_plane->intersect(ray, intersectionPoint)) {
		m_toothProfile->setPointOfGear(m_currentPointIndex, intersectionPoint);
		m_guiManager.update(m_toothProfile);
		emit toothProfileChanged(m_toothProfile);
	}
}

void ToothProfileForm::handleSelection() {
	emit selected(this);
	m_currentPointIndex = -1;
}

void ToothProfileForm::handleSelection(int pointIndex) {
	emit selected(this);
	m_currentPointIndex = pointIndex;
}
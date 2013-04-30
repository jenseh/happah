#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>

#include <iostream>
#include <list>
#include "happah/geometries/gears/SimpleGear.h"
#include "happah/geometries/gears/matinggear/MatingGearConstructionInformationPart.h"
#include "happah/geometries/BSplineCurve.h"
#include "happah/gui/forms/ToothProfileForm.h"

using namespace std;

ToothProfileForm::ToothProfileForm(GUIManager& guiManager, QWidget* parent)
	: Form(parent), m_currentPointIndex(-1), m_guiManager(guiManager) {

	m_toSimpleGearButton = new QPushButton("3D gear of 2D profile");
	connect(m_toSimpleGearButton, SIGNAL(clicked()), this, SLOT(toSimpleGear()));

	m_matingGearButton = new QPushButton("Construct mating gear");
	connect(m_matingGearButton, SIGNAL(clicked()), this, SLOT(constructMatingGear()));

	m_showMatingGearButton = new QPushButton("Show mating gear");
	connect(m_showMatingGearButton, SIGNAL(clicked()), this, SLOT(showMatingGear()));

	m_showNextMatingStepButton = new QPushButton("Next mating gear step");
	connect(m_showNextMatingStepButton, SIGNAL(clicked()), this, SLOT(showNextMatingStep()));

	m_matingRadiusSpinBox = new QDoubleSpinBox(this);
	m_matingRadiusSpinBox->setDecimals(3);
	QLabel* matingRadiusLabel = new QLabel(tr("Reference radius"));
	matingRadiusLabel->setToolTip(tr("Define the reference radius of the original gear, with which the mating gear construction should be done."));

	m_matingNTeethSpinBox = new QSpinBox(this);
	QLabel* matingNTeethLabel = new QLabel(tr("Number of teeth"));
	matingNTeethLabel->setToolTip(tr("Specify the number of teeth the mating gear should have."));

	m_matingConstrMaxAngleBox = new QDoubleSpinBox(this);
	m_matingConstrMaxAngleBox->setDecimals(3);
	m_matingConstrMaxAngleBox->setSuffix(tr(" degree"));
	m_matingConstrMaxAngleBox->setRange(0.1f, 20.0f);
	m_matingConstrMaxAngleBox->setSingleStep(0.1f);
	QLabel* matingConstrMaxAngleLabel = new QLabel(tr("Max angle"));
	matingConstrMaxAngleLabel->setToolTip(tr("The maximum angle in degrees used for the construction of the mating gear. The smaller the angle is, the more accurate the gear will be sampled, but also the more costly!"));

	m_matingConstrSamplRateBox = new QSpinBox(this);
	m_matingConstrSamplRateBox->setRange(5, 200);
	QLabel* matingConstrSamplRateLabel = new QLabel(tr("Sampling Rate"));
	matingConstrSamplRateLabel->setToolTip(tr("The sampling rate used in the construction of the mating gear. For bigger values a better accurancy is achieved, but with adverse effect on calculation time."));

	m_matingDarkenNormalsBox = new QCheckBox(tr("Darken normals"), this);
	connect(m_matingDarkenNormalsBox, SIGNAL(stateChanged(int)), this, SLOT(changeNormalsVisiblity(int)));

	m_matingNormalsLengthBox = new QDoubleSpinBox(this);
	m_matingNormalsLengthBox->setDecimals(3);
	m_matingNormalsLengthBox->setMinimum(0.0f);
	m_matingNormalsLengthBox->setSingleStep(0.25f);
	QLabel* matingNormalsLength = new QLabel(tr("Length of normals"));
	connect(m_matingNormalsLengthBox, SIGNAL(valueChanged(double)), this, SLOT(changeNormalLength(double)));

	QGridLayout* gridLayout = new QGridLayout(this);
	gridLayout->setHorizontalSpacing(0);
	gridLayout->setVerticalSpacing(2);
	gridLayout->setRowStretch(10, 2);

	gridLayout->addWidget(matingRadiusLabel,          1, 0);
	gridLayout->addWidget(m_matingRadiusSpinBox,      1, 1, Qt::AlignTop);
	
	gridLayout->addWidget(matingNTeethLabel,          2, 0);
	gridLayout->addWidget(m_matingNTeethSpinBox,      2, 1, Qt::AlignTop);
	
	gridLayout->addWidget(matingConstrMaxAngleLabel,  3, 0);
	gridLayout->addWidget(m_matingConstrMaxAngleBox,  3, 1, Qt::AlignTop);
	
	gridLayout->addWidget(matingConstrSamplRateLabel, 4, 0);
	gridLayout->addWidget(m_matingConstrSamplRateBox, 4, 1, Qt::AlignTop);
	
	gridLayout->addWidget(m_matingGearButton,         5, 0, Qt::AlignTop);
	gridLayout->addWidget(m_showMatingGearButton,     6, 0, Qt::AlignTop);
	gridLayout->addWidget(m_showNextMatingStepButton,         7, 0, Qt::AlignTop);

	gridLayout->addWidget(m_matingDarkenNormalsBox,     8, 0, Qt::AlignTop);

	gridLayout->addWidget(matingNormalsLength,        9, 0);
	gridLayout->addWidget(m_matingNormalsLengthBox,   9, 1, Qt::AlignTop);
	
	QGroupBox* matingCollection = new QGroupBox(tr("Mating gear construction options"));
	matingCollection->setAlignment(Qt::AlignLeft);
	matingCollection->setLayout(gridLayout);

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(m_toSimpleGearButton);
	layout->addWidget(matingCollection);
	this->setLayout(layout);

	m_matingWidgetList.push_back(m_matingGearButton);
	m_matingWidgetList.push_back(m_matingRadiusSpinBox);
	m_matingWidgetList.push_back(m_matingNTeethSpinBox);
	m_matingWidgetList.push_back(m_matingConstrSamplRateBox);
	m_matingWidgetList.push_back(m_matingConstrMaxAngleBox);
	m_matingWidgetList.push_back(m_matingNormalsLengthBox);
	m_matingWidgetList.push_back(m_matingDarkenNormalsBox);

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
	m_toSimpleGearButton->setEnabled(false);
	//Mating gear things:
	m_matingGearInformation = nullptr;
	setAllMatingWidgetsEnabled(false);
	m_matingConstrMaxAngleBox->setValue(5.0f);
	m_matingNormalsLengthBox->setValue(1.0f);
	m_matingConstrSamplRateBox->setValue(30);
	m_matingDarkenNormalsBox->setChecked(false);
}

void ToothProfileForm::setAllMatingWidgetsEnabled(bool enable) {
	m_showMatingGearButton->setEnabled(enable);
	m_showNextMatingStepButton->setEnabled(enable);
	setMatingWidgetsEnabled(enable);
}

void ToothProfileForm::setMatingWidgetsEnabled(bool enable) {
	for(std::vector<QWidget*>::iterator it = m_matingWidgetList.begin(), end = m_matingWidgetList.end(); it != end; ++it) {
		(*it)->setEnabled(enable);
	}
}

void ToothProfileForm::setToothProfile(ToothProfile_ptr toothProfile) {
	m_toothProfile = toothProfile;
	m_plane = Plane_ptr(m_toothProfile->getPlaneToothProfileLiesIn());
	m_toSimpleGearButton->setEnabled(true);

	if(m_toothProfile->hasMatingGear()) {
		updateFormWithMatingGearInformation();
	} else {

		hpuint nTeeth = m_toothProfile->getNumberOfTeeth();
		hpreal radius = 0.5f * m_toothProfile->getRootRadius() + 0.5f * m_toothProfile->getTipRadius();
		hpreal minRadius = MatingGearConstructor::getMinRadiusForOriginGear(*m_toothProfile, nTeeth);

		if(radius >= minRadius) {
			m_matingRadiusSpinBox->setValue(radius);
			m_matingRadiusSpinBox->setMinimum(MatingGearConstructor::getMinRadiusForOriginGear(*m_toothProfile, nTeeth));

			m_matingNTeethSpinBox->setValue(nTeeth);
			m_matingNTeethSpinBox->setMinimum(MatingGearConstructor::getMinNumberOfTeethForMatingGear(*m_toothProfile, radius));

			setMatingWidgetsEnabled(true);
		}
	}
}

void ToothProfileForm::toSimpleGear() {
	SimpleGear_ptr simpleGear = SimpleGear_ptr(new SimpleGear(*m_toothProfile, 0.0f, 2.0f));
	m_guiManager.insert(simpleGear, HP_TRIANGLE_MESH );
}

void ToothProfileForm::updateFormWithMatingGearInformation() {
	m_toothProfile->updateMatingGearConstructor();
	MatingGearConstructor* constructor = m_toothProfile->getMatingGearConstructor();
	m_matingGearInformation = constructor->getInformation();

	m_matingRadiusSpinBox->setValue(constructor->getMatingGearReferenceRadius());
	m_matingRadiusSpinBox->setMinimum(
		MatingGearConstructor::getMinRadiusForOriginGear(*m_toothProfile, 10)); //TODO: as soon as real mating toothprofile is available: replace this fake number 10 with correct value from toothprofile!!!!!!!

	m_matingNTeethSpinBox->setValue(10); //TODO: as soon as real mating toothprofile is available: replace this fake number 10 with correct value from toothprofile!!!!!!!
	m_matingNTeethSpinBox->setMinimum(
		MatingGearConstructor::getMinNumberOfTeethForMatingGear(*m_toothProfile,constructor->getMatingGearReferenceRadius()));

	setAllMatingWidgetsEnabled(true);
}

void ToothProfileForm::constructMatingGear() {
	if(!m_toothProfile->hasMatingGear()) {
		m_toothProfile->constructMatingGear(
			m_matingRadiusSpinBox->value(),
			m_matingNTeethSpinBox->value(),
			m_matingConstrMaxAngleBox->value(),
			m_matingConstrSamplRateBox->value());
	}
	updateFormWithMatingGearInformation();
}

void ToothProfileForm::darkenNormals() {
	// for(auto it : m_informationCurves) {
	// 	if((*m_partIterator)->getPart() == ORIGIN_NORMAL ||
	// 		(*m_partIterator)->getPart() == MATING_NORMAL) {
	// 		BSplineCurve2D_ptr curve2d = (*m_partIterator)->getCurve();
	// 		m_guiManager.update(curve2d, darkenColor);
	// 	}
	// }
}

void ToothProfileForm::showMatingGear() {
	BothGearInformation* both = m_matingGearInformation->getReferenceCircles();
	m_guiManager.insert(both->originPart.curve, both->originPart.name, both->originPart.color, both->originPart.drawModes);
	if(both->hasTwoParts)
		m_guiManager.insert(both->matingPart.curve, both->matingPart.name, both->matingPart.color, both->matingPart.drawModes);

	both = m_matingGearInformation->getToothProfiles();
	m_guiManager.insert(both->originPart.curve, both->originPart.name, both->originPart.color, both->originPart.drawModes);
	if(both->hasTwoParts)
		m_guiManager.insert(both->matingPart.curve, both->matingPart.name, both->matingPart.color, both->matingPart.drawModes);
	
	std::vector<BothGearInformation*>* normals = m_matingGearInformation->getNormals();
	for(std::vector<BothGearInformation*>::iterator it = normals->begin(), end = normals->end(); it != end; ++it) {
		m_guiManager.insert((*it)->originPart.curve, (*it)->originPart.name, (*it)->originPart.color, (*it)->originPart.drawModes);
		if((*it)->hasTwoParts)
			m_guiManager.insert((*it)->matingPart.curve, (*it)->matingPart.name, (*it)->matingPart.color, (*it)->matingPart.drawModes);
	}
}

void ToothProfileForm::changeNormalsVisiblity(int state) {
	bool visible = true;
	if(state == Qt::Checked)
		visible = false;
	cerr << "ToothProfileForm::changeNormalsVisiblity() called " << visible << endl;
	m_matingGearInformation->setDarkingOfNormals(visible);
	updateNormals();
}

void ToothProfileForm::changeNormalLength(double length) {
	if(m_matingGearInformation != nullptr) {
		m_matingGearInformation->setNormalLength(length);
		updateNormals();
	}
}

void ToothProfileForm::updateNormals() {
	std::vector<BothGearInformation*>* normals = m_matingGearInformation->getNormals();
	for(std::vector<BothGearInformation*>::iterator it = normals->begin(), end = normals->end(); it != end; ++it) {
		m_guiManager.update((*it)->originPart.curve, (*it)->originPart.color);
		if((*it)->hasTwoParts)
			m_guiManager.update((*it)->matingPart.curve, (*it)->matingPart.color);
	}
}

void ToothProfileForm::showNextMatingStep() {
	// hpcolor halfVisible = hpcolor(1.0f, 1.0f, 0.8f, 0.5f);
	// if(!m_informationCurves || !m_splineColors) {
	// 	constructMatingGear();
	// 	m_stepCounter = 0;
	// 	m_partIterator = m_informationCurves->begin();
	// }
	// if(m_partIterator == m_informationCurves->end() || m_stepCounter == m_splineColors->size()) {
	// 	m_showNextMatingStepButton->setEnabled(false);
	// } else {

	// 	BSplineCurve2D_ptr curve2d = (*m_partIterator)->getCurve();

	// 	if((*m_partIterator)->getError() == ErrorCode::NO_CUT_WITH_REFERENCE_RADIUS) {
	// 		m_guiManager.insert(curve2d, (*m_partIterator)->getName(), m_errorColor * halfVisible, HP_LINE_MESH | HP_POINT_CLOUD);
	// 		++m_stepCounter;
	// 		++m_partIterator;

	// 	} else {
	// 		BSplineCurve2D_ptr curve2d = (*m_partIterator)->getCurve();
	// 		char* name = (*m_partIterator)->getName();
	// 		MatingGearPart part = (*m_partIterator)->getPart();
	// 		hpcolor color = (*m_splineColors)[m_stepCounter];
	// 		++m_stepCounter;
	// 		++m_partIterator;
			
	// 		switch(part) {
	// 			case MatingGearPart::MATING_REFERENCE_CIRCLE:
	// 				m_guiManager.insert(curve2d, name, color, HP_LINE_MESH);
	// 				return;
	// 			case MatingGearPart::ORIGIN_REFERENCE_CIRCLE:
	// 				m_guiManager.insert(curve2d, name, color * halfVisible, HP_LINE_MESH);
	// 				return;
	// 			case MatingGearPart::MATING_NORMAL:
	// 				m_guiManager.insert(curve2d, name, color, HP_LINE_MESH | HP_POINT_CLOUD);
	// 				return;
	// 			case MatingGearPart::ORIGIN_NORMAL:
	// 				m_guiManager.insert(curve2d, name, color * halfVisible, HP_LINE_MESH | HP_POINT_CLOUD);
	// 				return;
	// 			case MatingGearPart::MATING_TOOTH_PROFILE:
	// 				m_guiManager.insert(curve2d, name, color, HP_LINE_MESH | HP_POINT_CLOUD);
	// 				return;
	// 			case MatingGearPart::ORIGIN_TOOTH_PROFILE:
	// 				m_guiManager.insert(curve2d, name, color * halfVisible, HP_LINE_MESH | HP_POINT_CLOUD);
	// 				return;
	// 		}
	// 	}
	// }
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
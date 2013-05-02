#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>

#include <iostream>
#include <list>
#include "happah/geometries/gears/SimpleGear.h"
#include "happah/geometries/BSplineCurve.h"
#include "happah/gui/forms/ToothProfileForm.h"

using namespace std;

ToothProfileForm::ToothProfileForm(GUIManager& guiManager, QWidget* parent)
	: Form(parent), m_currentPointIndex(-1), m_guiManager(guiManager) {

	m_toSimpleGearButton = new QPushButton("3D gear of 2D profile");
	connect(m_toSimpleGearButton, SIGNAL(clicked()), this, SLOT(toSimpleGear()));

	//Mating gear option:
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

	m_matingNormalsLengthBox = new QDoubleSpinBox(this);
	m_matingNormalsLengthBox->setDecimals(3);
	m_matingNormalsLengthBox->setMinimum(0.0f);
	m_matingNormalsLengthBox->setSingleStep(0.25f);
	QLabel* matingNormalsLength = new QLabel(tr("Length of normals"));
	connect(m_matingNormalsLengthBox, SIGNAL(valueChanged(double)), this, SLOT(changeNormalLength(double)));

	m_matingGearButton = new QPushButton("Construct mating gear");
	connect(m_matingGearButton, SIGNAL(clicked()), this, SLOT(constructMatingGear()));

	m_showMatingGearButton = new QPushButton("Show mating gear");
	connect(m_showMatingGearButton, SIGNAL(clicked()), this, SLOT(showMatingGear()));

	m_showReferenceCirclesButton = new QPushButton("Show reference circles");
	connect(m_showReferenceCirclesButton, SIGNAL(clicked()), this, SLOT(showReferenceCircles()));

	m_showNextNormalButton = new QPushButton("Next mating normal");
	connect(m_showNextNormalButton, SIGNAL(clicked()), this, SLOT(showNextNormal()));

	m_showAllNormalsButton = new QPushButton("All mating normals");
	connect(m_showAllNormalsButton, SIGNAL(clicked()), this, SLOT(showAllNormals()));

	m_showAngularPitchButton = new QPushButton("Show angular pitches");
	connect(m_showAngularPitchButton, SIGNAL(clicked()), this, SLOT(showAngularPitches()));

	m_matingDarkenNormalsBox = new QCheckBox(tr("Darken normals"), this);
	connect(m_matingDarkenNormalsBox, SIGNAL(stateChanged(int)), this, SLOT(changeNormalsVisiblity(int)));

	QGridLayout* gridLayout = new QGridLayout(this);
	gridLayout->setHorizontalSpacing(0);
	gridLayout->setVerticalSpacing(2);
	gridLayout->setRowStretch(12, 2);

	gridLayout->addWidget(matingRadiusLabel,          1, 0);
	gridLayout->addWidget(m_matingRadiusSpinBox,      1, 1, Qt::AlignTop);
	
	gridLayout->addWidget(matingNTeethLabel,          2, 0);
	gridLayout->addWidget(m_matingNTeethSpinBox,      2, 1, Qt::AlignTop);
	
	gridLayout->addWidget(matingConstrMaxAngleLabel,  3, 0);
	gridLayout->addWidget(m_matingConstrMaxAngleBox,  3, 1, Qt::AlignTop);
	
	gridLayout->addWidget(matingConstrSamplRateLabel, 4, 0);
	gridLayout->addWidget(m_matingConstrSamplRateBox, 4, 1, Qt::AlignTop);

	gridLayout->addWidget(matingNormalsLength,        5, 0);
	gridLayout->addWidget(m_matingNormalsLengthBox,   5, 1, Qt::AlignTop);

	gridLayout->addWidget(m_matingGearButton,         6, 0, 1, 2, Qt::AlignTop);
	gridLayout->addWidget(m_showReferenceCirclesButton,7,0, 1, 2, Qt::AlignTop);
	gridLayout->addWidget(m_showMatingGearButton,     8, 0, 1, 2, Qt::AlignTop);
	gridLayout->addWidget(m_showNextNormalButton,     9, 0, 1, 2, Qt::AlignTop);
	gridLayout->addWidget(m_showAllNormalsButton,    10, 0, 1, 2, Qt::AlignTop);
	gridLayout->addWidget(m_showAngularPitchButton,  11, 0, 1, 2, Qt::AlignTop);

	gridLayout->addWidget(m_matingDarkenNormalsBox,  12, 0, Qt::AlignTop);

	
	QGroupBox* matingCollection = new QGroupBox(tr("Mating gear construction options"));
	matingCollection->setAlignment(Qt::AlignLeft);
	matingCollection->setLayout(gridLayout);

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(m_toSimpleGearButton);
	layout->addWidget(matingCollection);
	this->setLayout(layout);

	m_matingStartWidgetList.push_back(m_matingGearButton);
	m_matingStartWidgetList.push_back(m_matingRadiusSpinBox);
	m_matingStartWidgetList.push_back(m_matingNTeethSpinBox);
	m_matingStartWidgetList.push_back(m_matingConstrSamplRateBox);
	m_matingStartWidgetList.push_back(m_matingConstrMaxAngleBox);
	m_matingStartWidgetList.push_back(m_matingNormalsLengthBox);
	m_matingStartWidgetList.push_back(m_matingDarkenNormalsBox);

	m_matingGearAvailableWidgetList.push_back(m_showMatingGearButton);
	m_matingGearAvailableWidgetList.push_back(m_showNextNormalButton);
	m_matingGearAvailableWidgetList.push_back(m_showAllNormalsButton);
	m_matingGearAvailableWidgetList.push_back(m_showReferenceCirclesButton);
	m_matingGearAvailableWidgetList.push_back(m_showAngularPitchButton);

	reset();

	connect(this, SIGNAL(toothProfileChanged(ToothProfile_ptr)), this, SLOT(updateMatingGearConstructor(ToothProfile_ptr)));
}

ToothProfileForm::~ToothProfileForm() {
}

void ToothProfileForm::updateMatingGearConstructor(ToothProfile_ptr) {
	if(m_matingGearInformation != nullptr) {
		m_toothProfile->updateMatingGearConstructor();
		updateFormExistingMatingGear();
	} else {
		updateFormNoExistingMatingGear();
	}
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
	for(std::vector<QWidget*>::iterator it = m_matingGearAvailableWidgetList.begin(), end = m_matingGearAvailableWidgetList.end(); it != end; ++it) {
		(*it)->setEnabled(enable);
	}
	setMatingWidgetsEnabled(enable);
}

void ToothProfileForm::setMatingWidgetsEnabled(bool enable) {
	for(std::vector<QWidget*>::iterator it = m_matingStartWidgetList.begin(), end = m_matingStartWidgetList.end(); it != end; ++it) {
		(*it)->setEnabled(enable);
	}
}

void ToothProfileForm::setToothProfile(ToothProfile_ptr toothProfile) {
	m_toothProfile = toothProfile;
	m_plane = Plane_ptr(m_toothProfile->getPlaneToothProfileLiesIn());
	m_toSimpleGearButton->setEnabled(true);

	if(m_toothProfile->hasMatingGear()) {
		updateFormExistingMatingGear();
	} else {
		updateFormNoExistingMatingGear();
	}
}

void ToothProfileForm::toSimpleGear() {
	SimpleGear_ptr simpleGear = SimpleGear_ptr(new SimpleGear(*m_toothProfile, 0.0f, 2.0f));
	m_guiManager.insert(simpleGear, HP_TRIANGLE_MESH );
}

void ToothProfileForm::updateFormNoExistingMatingGear() {
	hpuint nTeeth = m_toothProfile->getNumberOfTeeth();
	hpreal avgRadius = 0.5f * m_toothProfile->getRootRadius() + 0.5f * m_toothProfile->getTipRadius();
	hpreal minRadius = MatingGearConstructor::getMinRadiusForOriginGear(*m_toothProfile, nTeeth);

	if(avgRadius >= minRadius) {
		m_matingRadiusSpinBox->setValue(avgRadius);
		m_matingRadiusSpinBox->setMinimum(MatingGearConstructor::getMinRadiusForOriginGear(*m_toothProfile, nTeeth));

		m_matingNTeethSpinBox->setValue(nTeeth);
		m_matingNTeethSpinBox->setMinimum(MatingGearConstructor::getMinNumberOfTeethForMatingGear(*m_toothProfile, avgRadius));

		setMatingWidgetsEnabled(true);
	}
}

void ToothProfileForm::updateFormExistingMatingGear() {
	MatingGearConstructor* constructor = m_toothProfile->getMatingGearConstructor();
	m_matingGearInformation = constructor->getInformation();

	m_matingRadiusSpinBox->setValue(constructor->getMatingGearReferenceRadius());
	m_matingRadiusSpinBox->setMinimum(
		MatingGearConstructor::getMinRadiusForOriginGear(*m_toothProfile, m_toothProfile->getNumberOfTeeth())); //TODO: as soon as real mating toothprofile is available: replace this fake number 10 with correct value from toothprofile!!!!!!!

	m_matingNTeethSpinBox->setValue(m_toothProfile->getNumberOfTeeth()); //TODO: as soon as real mating toothprofile is available: replace this fake number 10 with correct value from toothprofile!!!!!!!
	m_matingNTeethSpinBox->setMinimum(
		MatingGearConstructor::getMinNumberOfTeethForMatingGear(*m_toothProfile,constructor->getMatingGearReferenceRadius()));

	setAllMatingWidgetsEnabled(true);

	if(!m_matingGearInformation->areFurtherNormalsAvailable()) {
		m_showMatingGearButton->setEnabled(false);
		m_showNextNormalButton->setEnabled(false);
		m_showAllNormalsButton->setEnabled(false);
	}
}

void ToothProfileForm::constructMatingGear() {
	if(!m_toothProfile->hasMatingGear()) {
		// cerr << "ToothProfileForm::constructMatingGear(): has found no MatingGearConstructor until now" << endl;
		// cerr << "                                         radius will be: " << m_matingRadiusSpinBox->value() << endl;
		new MatingGearConstructor(
			m_toothProfile,
			m_matingRadiusSpinBox->value(),
			m_matingNTeethSpinBox->value(),
			m_matingConstrMaxAngleBox->value(),
			m_matingConstrSamplRateBox->value());
		updateFormExistingMatingGear();
	} else {
		m_toothProfile->updateMatingGearConstructor();
		updateFormExistingMatingGear();
	}
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

void ToothProfileForm::showAngularPitches() {
	insertGearInformation(m_matingGearInformation->getAngularPitches());
}

void ToothProfileForm::showMatingGear() {

	ToothProfile_ptr matingToothProfile = m_toothProfile->getMatingGearConstructor()->getMatingToothProfile();
	m_guiManager.insert(matingToothProfile, HP_LINE_MESH | HP_POINT_CLOUD);

	insertGearInformation(m_matingGearInformation->getReferenceCircles());
	insertGearInformation(m_matingGearInformation->getToothProfiles());

	if(m_matingGearInformation->areFurtherNormalsAvailable()) {
		std::vector<BothGearInformation*>* normals = m_matingGearInformation->getNormals();
		for(std::vector<BothGearInformation*>::iterator it = normals->begin(), end = normals->end(); it != end; ++it) {
			insertGearInformation(*it);
		}
	}
	m_showMatingGearButton->setEnabled(false);
	m_showNextNormalButton->setEnabled(false);
}

void ToothProfileForm::showReferenceCircles() {
	insertGearInformation(m_matingGearInformation->getReferenceCircles());
	m_showReferenceCirclesButton->setEnabled(false);
}

void ToothProfileForm::changeNormalsVisiblity(int state) {
	if(m_matingGearInformation != nullptr) {
		bool visible = true;
		if(state == Qt::Checked)
			visible = false;
		m_matingGearInformation->setDarkingOfNormals(visible);
		updateNormals();
	}
}

void ToothProfileForm::changeNormalLength(double length) {
	if(m_matingGearInformation != nullptr) {
		m_matingGearInformation->setNormalLength(length);
		// updateNormals();
	}
}

void ToothProfileForm::updateNormals() {
	if(m_matingGearInformation != nullptr) {
		std::vector<BothGearInformation*>* normals = m_matingGearInformation->getNormals();
		for(std::vector<BothGearInformation*>::iterator it = normals->begin(), end = normals->end(); it != end; ++it) {
			updateGearInformation(*it);
		}
	}
}

void ToothProfileForm::showAllNormals() {
	for(;m_matingGearInformation->areFurtherNormalsAvailable();)
		insertGearInformation(m_matingGearInformation->getNextNormal());
	m_showNextNormalButton->setEnabled(false);
	m_showAllNormalsButton->setEnabled(false);
}

void ToothProfileForm::showNextNormal() {
	if(m_matingGearInformation->areFurtherNormalsAvailable())
		insertGearInformation(m_matingGearInformation->getNextNormal());
	if(!m_matingGearInformation->areFurtherNormalsAvailable())
		m_showNextNormalButton->setEnabled(false);
}

void ToothProfileForm::handleRay(Ray& ray) {
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

void ToothProfileForm::insertGearInformation(BothGearInformation* gearPart) {
	m_guiManager.insert(gearPart->originPart.curve, gearPart->originPart.name, gearPart->originPart.color, gearPart->originPart.drawModes);
	if(gearPart->hasTwoParts)
		m_guiManager.insert(gearPart->matingPart.curve, gearPart->matingPart.name, gearPart->matingPart.color, gearPart->matingPart.drawModes);
}

void ToothProfileForm::updateGearInformation(BothGearInformation* gearPart) {
	m_guiManager.update(gearPart->originPart.curve, gearPart->originPart.color);
	if(gearPart->hasTwoParts)
		m_guiManager.update(gearPart->matingPart.curve, gearPart->matingPart.color);
}

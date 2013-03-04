#include <QPushButton>
#include <QVBoxLayout>

#include "happah/gui/forms/InvoluteGearForm.h"

InvoluteGearForm::InvoluteGearForm(GUIManager& guiManager, QWidget* parent)
	: QWidget(parent), 
		m_bottomClearanceSlider(new GearSlider(tr("bottom clearance"))),
		m_faceWidthSlider(new GearSlider(tr("facewidth"))),
		m_filletRadiusSlider(new GearSlider(tr("fillet radius"))),
		m_gear(new InvoluteSpurGear()), 
		m_gearInScene(false), 
		m_guiManager(guiManager),
		m_helixAngleSlider(new GearSlider(tr("helix angle"))),
		m_moduleSlider(new GearSlider(tr("module"))),
		m_pressureAngleSlider(new GearSlider(tr("pressure angle"))),
		m_toothCountSlider(new GearSlider(tr("number of teeth"), false)) {
	QPushButton* createButton  = new QPushButton("create gear");

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(m_toothCountSlider);
	layout->addWidget(m_moduleSlider);
	layout->addWidget(m_faceWidthSlider);
	layout->addWidget(m_pressureAngleSlider);
	layout->addWidget(m_bottomClearanceSlider);
	layout->addWidget(m_filletRadiusSlider);
	layout->addWidget(m_helixAngleSlider);
	layout->addWidget(createButton);
	setLayout(layout);

	connect(createButton, SIGNAL(clicked()), this, SLOT(createGear()));
	connect(m_toothCountSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeToothCount(hpreal)));
	connect(m_moduleSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeModule(hpreal)));
	connect(m_faceWidthSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeFacewidth(hpreal)));
	connect(m_pressureAngleSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changePressureAngle(hpreal)));
	connect(m_bottomClearanceSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeBottomClearance(hpreal)));
	connect(m_filletRadiusSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeFilletRadius(hpreal)));
	connect(m_helixAngleSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeHelixAngle(hpreal)));

	updateRanges();
}

InvoluteGearForm::~InvoluteGearForm() {}

void InvoluteGearForm::createGear() {
	m_guiManager.insert(m_gear);
	m_gearInScene = true;
}

void InvoluteGearForm::updateGear() {
	if(m_gearInScene)
		m_guiManager.update(m_gear);
}

void InvoluteGearForm::updateRanges() {
	uint* toothCounts = m_gear->getPossibleToothCounts();
	hpreal* modules = m_gear->getPossibleModules();
	hpreal* pressureAngles = m_gear->getPossiblePressureAngles();
	hpreal* bottomClearances = m_gear->getPossibleBottomClearances();
	hpreal* filletRadien = m_gear->getPossibleFilletRadien();
	hpreal epsilon = 0.0001f;

	m_toothCountSlider->setSliderValues(m_gear->getToothCount(), toothCounts[0], toothCounts[1]);
	m_moduleSlider->setSliderValues(m_gear->getModule(), modules[0], modules[1]);
	m_faceWidthSlider->setSliderValues(m_gear->getFacewidth(), 0.0f, m_gear->getReferenceRadius() * 2.0f);
	m_pressureAngleSlider->setSliderValues(m_gear->getPressureAngle(), pressureAngles[0], pressureAngles[1]);
	m_bottomClearanceSlider->setSliderValues(m_gear->getBottomClearance(), bottomClearances[0], bottomClearances[1]);
	m_filletRadiusSlider->setSliderValues(m_gear->getFilletRadius(), filletRadien[0], filletRadien[1]);
	m_helixAngleSlider->setSliderValues(m_gear->getHelixAngle(), -(epsilon + M_PI / 2.0f), epsilon + M_PI / 2.0f );
}

void InvoluteGearForm::changeToothCount(hpreal toothCount) {
	if (m_gear->setToothCount(toothCount)) {
		updateRanges();
		updateGear();
	}
}
void InvoluteGearForm::changeModule(hpreal module) {
	if (m_gear->setModule(module)) {
		updateRanges();
		updateGear();
	}
}
void InvoluteGearForm::changeFacewidth(hpreal facewidth) {
	if (m_gear->setFacewidth(facewidth)) {
		updateGear();
	}
}
void InvoluteGearForm::changePressureAngle(hpreal angle) {
	if (m_gear->setPressureAngle(angle)) {
		updateRanges();
		updateGear();
	}
}
void InvoluteGearForm::changeBottomClearance(hpreal bottomClearance) {
	if (m_gear->setBottomClearance(bottomClearance)) {
		updateRanges();
		updateGear();
	}
}
void InvoluteGearForm::changeFilletRadius(hpreal radius) {
	if (m_gear->setFilletRadius(radius)) {
		updateRanges();
		updateGear();
	}
}
void InvoluteGearForm::changeHelixAngle(hpreal angle) {
	if (m_gear->setHelixAngle(angle)) {
		updateRanges();
		updateGear();
	}
}


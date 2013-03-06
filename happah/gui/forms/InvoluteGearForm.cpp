#include <QPushButton>
#include <QVBoxLayout>

#include "happah/gui/forms/InvoluteGearForm.h"

InvoluteGearForm::InvoluteGearForm(InvoluteGearListener& involuteGearListener, QWidget* parent)
	: Form(parent), 
		m_bottomClearanceSlider(new GearSlider(tr("bottom clearance"))),
		m_faceWidthSlider(new GearSlider(tr("facewidth"))),
		m_filletRadiusSlider(new GearSlider(tr("fillet radius"))),
		m_involuteGear(new InvoluteGear()), 
		m_involuteGearInserted(false), 
		m_involuteGearListener(involuteGearListener),
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

	connect(createButton, SIGNAL(clicked()), this, SLOT(createInvoluteGear()));
	connect(m_bottomClearanceSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeBottomClearance(hpreal)));
	connect(m_faceWidthSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeFacewidth(hpreal)));
	connect(m_filletRadiusSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeFilletRadius(hpreal)));
	connect(m_helixAngleSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeHelixAngle(hpreal)));
	connect(m_moduleSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeModule(hpreal)));
	connect(m_pressureAngleSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changePressureAngle(hpreal)));
	connect(m_toothCountSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeToothCount(hpreal)));

	updateRanges();
}

InvoluteGearForm::~InvoluteGearForm() {}

void InvoluteGearForm::changeBottomClearance(hpreal bottomClearance) {
	if (m_involuteGear->setBottomClearance(bottomClearance)) {
		updateRanges();
		updateInvoluteGear();
	}
}

void InvoluteGearForm::changeFacewidth(hpreal facewidth) {
	if (m_involuteGear->setFacewidth(facewidth)) {
		updateInvoluteGear();
	}
}

void InvoluteGearForm::changeFilletRadius(hpreal radius) {
	if (m_involuteGear->setFilletRadius(radius)) {
		updateRanges();
		updateInvoluteGear();
	}
}

void InvoluteGearForm::changeHelixAngle(hpreal angle) {
	if (m_involuteGear->setHelixAngle(angle)) {
		updateRanges();
		updateInvoluteGear();
	}
}

void InvoluteGearForm::changeModule(hpreal module) {
	if (m_involuteGear->setModule(module)) {
		updateRanges();
		updateInvoluteGear();
	}
}

void InvoluteGearForm::changePressureAngle(hpreal angle) {
	if (m_involuteGear->setPressureAngle(angle)) {
		updateRanges();
		updateInvoluteGear();
	}
}

void InvoluteGearForm::changeToothCount(hpreal toothCount) {
	if (m_involuteGear->setToothCount(toothCount)) {
		updateRanges();
		updateInvoluteGear();
	}
}

void InvoluteGearForm::createInvoluteGear() {
	if(m_involuteGearInserted)
		m_involuteGear = InvoluteGear_ptr(new InvoluteGear(*m_involuteGear));
	m_involuteGearListener.insert(m_involuteGear);
	m_involuteGearInserted = true;
}

void InvoluteGearForm::setInvoluteGear(InvoluteGear_ptr involuteGear) {
	m_involuteGear = involuteGear;
	m_involuteGearInserted = true;
	
	updateRanges();
}

void InvoluteGearForm::updateInvoluteGear() {
	if(m_involuteGearInserted)
		m_involuteGearListener.update(m_involuteGear);
}

void InvoluteGearForm::updateRanges() {
	uint* toothCounts = m_involuteGear->getPossibleToothCounts();
	hpreal* modules = m_involuteGear->getPossibleModules();
	hpreal* pressureAngles = m_involuteGear->getPossiblePressureAngles();
	hpreal* bottomClearances = m_involuteGear->getPossibleBottomClearances();
	hpreal* filletRadien = m_involuteGear->getPossibleFilletRadien();
	hpreal epsilon = 0.0001f;

	m_toothCountSlider->setSliderValues(m_involuteGear->getToothCount(), toothCounts[0], toothCounts[1]);
	m_moduleSlider->setSliderValues(m_involuteGear->getModule(), modules[0], modules[1]);
	m_faceWidthSlider->setSliderValues(m_involuteGear->getFacewidth(), 0.0f, m_involuteGear->getReferenceRadius() * 2.0f);
	m_pressureAngleSlider->setSliderValues(m_involuteGear->getPressureAngle(), pressureAngles[0], pressureAngles[1]);
	m_bottomClearanceSlider->setSliderValues(m_involuteGear->getBottomClearance(), bottomClearances[0], bottomClearances[1]);
	m_filletRadiusSlider->setSliderValues(m_involuteGear->getFilletRadius(), filletRadien[0], filletRadien[1]);
	m_helixAngleSlider->setSliderValues(m_involuteGear->getHelixAngle(), -(epsilon + M_PI / 2.0f), epsilon + M_PI / 2.0f );
}


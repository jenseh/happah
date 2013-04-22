#include <QPushButton>
#include <QVBoxLayout>

#include "happah/gui/forms/InvoluteGearForm.h"

InvoluteGearForm::InvoluteGearForm(GUIManager& guiManager, QWidget* parent)
	: Form(parent), 
		m_boreRadiusSlider(new LabeledRealValuedSlider(tr("bore radius"))),
		m_bottomClearanceSlider(new LabeledRealValuedSlider(tr("bottom clearance"))),
		m_faceWidthSlider(new LabeledRealValuedSlider(tr("face width"))),
		m_filletRadiusSlider(new LabeledRealValuedSlider(tr("fillet radius"))),
		m_guiManager(guiManager),
		m_involuteGear(new InvoluteGear()), 
		m_involuteGearInserted(false), 
		m_helixAngleSlider(new LabeledRealValuedSlider(tr("helix angle"))),
		m_moduleSlider(new LabeledRealValuedSlider(tr("module"))),
		m_pressureAngleSlider(new LabeledRealValuedSlider(tr("pressure angle"))),
		m_nTeethSlider(new LabeledIntegerSlider(tr("number of teeth"))) {
	QPushButton* createButton = new QPushButton("create gear");

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(m_nTeethSlider);
	layout->addWidget(m_moduleSlider);
	layout->addWidget(m_faceWidthSlider);
	layout->addWidget(m_pressureAngleSlider);
	layout->addWidget(m_bottomClearanceSlider);
	layout->addWidget(m_filletRadiusSlider);
	layout->addWidget(m_helixAngleSlider);
	layout->addWidget(m_boreRadiusSlider);
	layout->addWidget(createButton);
	setLayout(layout);

	connect(createButton, SIGNAL(clicked()), this, SLOT(createInvoluteGear()));
	connect(m_boreRadiusSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeBoreRadius(hpreal)));
	connect(m_bottomClearanceSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeBottomClearance(hpreal)));
	connect(m_faceWidthSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeFaceWidth(hpreal)));
	connect(m_filletRadiusSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeFilletRadius(hpreal)));
	connect(m_helixAngleSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeHelixAngle(hpreal)));
	connect(m_moduleSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeModule(hpreal)));
	connect(m_nTeethSlider, SIGNAL(valueChanged(int)), this, SLOT(changeNumberOfTeeth(int)));
	connect(m_pressureAngleSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changePressureAngle(hpreal)));

	setSliderValues();
}

InvoluteGearForm::~InvoluteGearForm() {}

void InvoluteGearForm::changeBoreRadius(hpreal boreRadius) {
	if(m_involuteGear->setBoreRadius(boreRadius)) {
		updateRanges();
		updateInvoluteGear();
	} else {
		hpreal* boreRadii = m_involuteGear->getPossibleBoreRadii();
		m_boreRadiusSlider->setSliderValues(m_involuteGear->getBoreRadius(), boreRadii[0], boreRadii[1]);
	}
}

void InvoluteGearForm::changeBottomClearance(hpreal bottomClearance) {
	if(m_involuteGear->setBottomClearance(bottomClearance)) {
		updateRanges();
		updateInvoluteGear();
	} else {
		hpreal* bottomClearances = m_involuteGear->getPossibleBottomClearances();
		m_bottomClearanceSlider->setSliderValues(m_involuteGear->getBottomClearance(), bottomClearances[0], bottomClearances[1]);
	}
}

void InvoluteGearForm::changeFaceWidth(hpreal faceWidth) {
	if(m_involuteGear->setFaceWidth(faceWidth)) {
		updateInvoluteGear();
	} else {
		m_faceWidthSlider->setSliderValues(m_involuteGear->getFaceWidth(), 0.0f, m_involuteGear->getReferenceRadius() * 2.0f);
	}
}

void InvoluteGearForm::changeFilletRadius(hpreal radius) {
	if(m_involuteGear->setFilletRadius(radius)) {
		updateRanges();
		updateInvoluteGear();
	} else {
		hpreal* filletRadii = m_involuteGear->getPossibleFilletRadii();
		m_filletRadiusSlider->setSliderValues(m_involuteGear->getFilletRadius(), filletRadii[0], filletRadii[1]);
	}
}

void InvoluteGearForm::changeHelixAngle(hpreal angle) {
	if(m_involuteGear->setHelixAngle(angle)) {
		updateRanges();
		updateInvoluteGear();
	} else {
		hpreal* helixAngles = m_involuteGear->getPossibleHelixAngles();
		m_helixAngleSlider->setSliderValues(m_involuteGear->getHelixAngle(), helixAngles[0], helixAngles[1]);
	}
}

void InvoluteGearForm::changeModule(hpreal module) {
	if(m_involuteGear->setModule(module)) {
		updateRanges();
		updateInvoluteGear();
	} else {
		hpreal* modules = m_involuteGear->getPossibleModules();
		m_moduleSlider->setSliderValues(m_involuteGear->getModule(), modules[0], modules[1]);
	}
}

void InvoluteGearForm::changePressureAngle(hpreal angle) {
	if(m_involuteGear->setPressureAngle(angle)) {
		updateRanges();
		updateInvoluteGear();
	} else {
		hpreal* pressureAngles = m_involuteGear->getPossiblePressureAngles();
		m_pressureAngleSlider->setSliderValues(m_involuteGear->getPressureAngle(), pressureAngles[0], pressureAngles[1]);
	}
}

void InvoluteGearForm::changeNumberOfTeeth(int nTeeth) {
	if(m_involuteGear->setNumberOfTeeth(nTeeth)) {
		updateRanges();
		updateInvoluteGear();
	} else {
		hpuint* nTeeth = m_involuteGear->getPossibleNumbersOfTeeth();
		m_nTeethSlider->setSliderValues(m_involuteGear->getNumberOfTeeth(), nTeeth[0], nTeeth[1]);
	}
}

void InvoluteGearForm::createInvoluteGear() {
	if(m_involuteGearInserted)
		m_involuteGear = InvoluteGear_ptr(new InvoluteGear(*m_involuteGear));
	m_guiManager.insert(m_involuteGear,HP_TRIANGLE_MESH);
	m_involuteGearInserted = true;
}

InvoluteGear_ptr InvoluteGearForm::getInvoluteGear() const {
	return m_involuteGear;
}

void InvoluteGearForm::reset() {
	m_involuteGear = InvoluteGear_ptr(new InvoluteGear());
	m_involuteGearInserted = false;

	setSliderValues();
}

void InvoluteGearForm::setInvoluteGear(InvoluteGear_ptr involuteGear) {
	m_involuteGear = involuteGear;
	m_involuteGearInserted = true;
	
	setSliderValues();
}

void InvoluteGearForm::updateInvoluteGear() {
	if(m_involuteGearInserted)
		m_guiManager.update(m_involuteGear);
}

void InvoluteGearForm::updateRanges() {
	hpuint* nTeeth = m_involuteGear->getPossibleNumbersOfTeeth();
	hpreal* modules = m_involuteGear->getPossibleModules();
	hpreal* pressureAngles = m_involuteGear->getPossiblePressureAngles();
	hpreal* bottomClearances = m_involuteGear->getPossibleBottomClearances();
	hpreal* filletRadii = m_involuteGear->getPossibleFilletRadii();
	hpreal* boreRadii = m_involuteGear->getPossibleBoreRadii();
	hpreal* helixAngles = m_involuteGear->getPossibleHelixAngles();

	m_nTeethSlider->setRange(nTeeth[0], nTeeth[1]);
	m_moduleSlider->setRange(modules[0], modules[1]);
	m_faceWidthSlider->setRange(0.0f, m_involuteGear->getReferenceRadius() * 2.0f);
	m_pressureAngleSlider->setRange(pressureAngles[0], pressureAngles[1]);
	m_bottomClearanceSlider->setRange(bottomClearances[0], bottomClearances[1]);
	m_filletRadiusSlider->setRange(filletRadii[0], filletRadii[1]);
	m_helixAngleSlider->setRange(helixAngles[0], helixAngles[1]);
	m_boreRadiusSlider->setRange(boreRadii[0], boreRadii[1]);
}

void InvoluteGearForm::setSliderValues() {
	hpuint* nTeeth = m_involuteGear->getPossibleNumbersOfTeeth();
	hpreal* modules = m_involuteGear->getPossibleModules();
	hpreal* pressureAngles = m_involuteGear->getPossiblePressureAngles();
	hpreal* bottomClearances = m_involuteGear->getPossibleBottomClearances();
	hpreal* filletRadii = m_involuteGear->getPossibleFilletRadii();
	hpreal* boreRadii = m_involuteGear->getPossibleBoreRadii();
	hpreal* helixAngles = m_involuteGear->getPossibleHelixAngles();

	m_nTeethSlider->setSliderValues(m_involuteGear->getNumberOfTeeth(), nTeeth[0], nTeeth[1]);
	m_moduleSlider->setSliderValues(m_involuteGear->getModule(), modules[0], modules[1]);
	m_faceWidthSlider->setSliderValues(m_involuteGear->getFaceWidth(), 0.0f, m_involuteGear->getReferenceRadius() * 2.0f);
	m_pressureAngleSlider->setSliderValues(m_involuteGear->getPressureAngle(), pressureAngles[0], pressureAngles[1]);
	m_bottomClearanceSlider->setSliderValues(m_involuteGear->getBottomClearance(), bottomClearances[0], bottomClearances[1]);
	m_filletRadiusSlider->setSliderValues(m_involuteGear->getFilletRadius(), filletRadii[0], filletRadii[1]);
	m_helixAngleSlider->setSliderValues(m_involuteGear->getHelixAngle(), helixAngles[0], helixAngles[1]);
	m_boreRadiusSlider->setSliderValues(m_involuteGear->getBoreRadius(), boreRadii[0], boreRadii[1]);
}


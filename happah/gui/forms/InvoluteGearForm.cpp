#include <QPushButton>
#include <QVBoxLayout>

#include "happah/gui/forms/InvoluteGearForm.h"

InvoluteGearForm::InvoluteGearForm(GUIManager& guiManager, QWidget* parent)
	: Form(parent), 
		m_boreRadiusSlider(new LabeledSlider<RealValuedSlider, hpreal>(tr("bore radius"))),
		m_bottomClearanceSlider(new LabeledSlider<RealValuedSlider, hpreal>(tr("bottom clearance"))),
		m_faceWidthSlider(new LabeledSlider<RealValuedSlider, hpreal>(tr("face width"))),
		m_filletRadiusSlider(new LabeledSlider<RealValuedSlider, hpreal>(tr("fillet radius"))),
		m_guiManager(guiManager),
		m_involuteGear(new InvoluteGear()), 
		m_involuteGearInserted(false), 
		m_helixAngleSlider(new LabeledSlider<RealValuedSlider, hpreal>(tr("helix angle"))),
		m_moduleSlider(new LabeledSlider<RealValuedSlider, hpreal>(tr("module"))),
		m_pressureAngleSlider(new LabeledSlider<RealValuedSlider, hpreal>(tr("pressure angle"))),
		m_nTeethSlider(new LabeledSlider<IntegerSlider, int>(tr("number of teeth"), false)) {
	QPushButton* createButton  = new QPushButton("create gear");

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
	connect(m_boreRadiusSlider, SIGNAL(sliderValueChanged(hpreal)), this, SLOT(changeBoreRadius(hpreal)));
	connect(m_bottomClearanceSlider, SIGNAL(sliderValueChanged(hpreal)), this, SLOT(changeBottomClearance(hpreal)));
	connect(m_faceWidthSlider, SIGNAL(sliderValueChanged(hpreal)), this, SLOT(changeFaceWidth(hpreal)));
	connect(m_filletRadiusSlider, SIGNAL(sliderValueChanged(hpreal)), this, SLOT(changeFilletRadius(hpreal)));
	connect(m_helixAngleSlider, SIGNAL(sliderValueChanged(hpreal)), this, SLOT(changeHelixAngle(hpreal)));
	connect(m_moduleSlider, SIGNAL(sliderValueChanged(hpreal)), this, SLOT(changeModule(hpreal)));
	connect(m_nTeethSlider, SIGNAL(sliderValueChanged(hpreal)), this, SLOT(changeNumberOfTeeth(hpreal)));
	connect(m_pressureAngleSlider, SIGNAL(sliderValueChanged(hpreal)), this, SLOT(changePressureAngle(hpreal)));

	updateRanges();
}

InvoluteGearForm::~InvoluteGearForm() {}

void InvoluteGearForm::changeBoreRadius(hpreal boreRadius) {
	if(m_involuteGear->setBoreRadius(boreRadius)) {
		updateRanges();
		updateInvoluteGear();
	}
}

void InvoluteGearForm::changeBottomClearance(hpreal bottomClearance) {
	if(m_involuteGear->setBottomClearance(bottomClearance)) {
		updateRanges();
		updateInvoluteGear();
	}
}

void InvoluteGearForm::changeFaceWidth(hpreal faceWidth) {
	if(m_involuteGear->setFaceWidth(faceWidth)) {
		updateInvoluteGear();
	}
}

void InvoluteGearForm::changeFilletRadius(hpreal radius) {
	if(m_involuteGear->setFilletRadius(radius)) {
		updateRanges();
		updateInvoluteGear();
	}
}

void InvoluteGearForm::changeHelixAngle(hpreal angle) {
	if(m_involuteGear->setHelixAngle(angle)) {
		updateRanges();
		updateInvoluteGear();
	}
}

void InvoluteGearForm::changeModule(hpreal module) {
	if(m_involuteGear->setModule(module)) {
		updateRanges();
		updateInvoluteGear();
	}
}

void InvoluteGearForm::changePressureAngle(hpreal angle) {
	if(m_involuteGear->setPressureAngle(angle)) {
		updateRanges();
		updateInvoluteGear();
	}
}

void InvoluteGearForm::changeNumberOfTeeth(hpreal nTeeth) {
	if(m_involuteGear->setNumberOfTeeth(nTeeth)) {
		updateRanges();
		updateInvoluteGear();
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

	updateRanges();
}

void InvoluteGearForm::setInvoluteGear(InvoluteGear_ptr involuteGear) {
	m_involuteGear = involuteGear;
	m_involuteGearInserted = true;
	
	updateRanges();
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
	hpreal epsilon = 0.0001f;

	m_nTeethSlider->setSliderValues(m_involuteGear->getNumberOfTeeth(), nTeeth[0], nTeeth[1]);
	m_moduleSlider->setSliderValues(m_involuteGear->getModule(), modules[0], modules[1]);
	m_faceWidthSlider->setSliderValues(m_involuteGear->getFaceWidth(), 0.0f, m_involuteGear->getReferenceRadius() * 2.0f);
	m_pressureAngleSlider->setSliderValues(m_involuteGear->getPressureAngle(), pressureAngles[0], pressureAngles[1]);
	m_bottomClearanceSlider->setSliderValues(m_involuteGear->getBottomClearance(), bottomClearances[0], bottomClearances[1]);
	m_filletRadiusSlider->setSliderValues(m_involuteGear->getFilletRadius(), filletRadii[0], filletRadii[1]);
	m_helixAngleSlider->setSliderValues(m_involuteGear->getHelixAngle(), -(epsilon + M_PI / 2.0f), epsilon + M_PI / 2.0f );
	m_boreRadiusSlider->setSliderValues(m_involuteGear->getBoreRadius(), boreRadii[0], boreRadii[1]);
}


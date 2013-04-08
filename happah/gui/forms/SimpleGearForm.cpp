#include <QPushButton>
#include <QVBoxLayout>

#include "happah/geometries/gears/InvoluteGear.h"
#include "happah/gui/forms/SimpleGearForm.h"

SimpleGearForm::SimpleGearForm(GUIManager& guiManager, QWidget* parent)
	: Form(parent),
		m_faceWidthSlider(new LabeledRealValuedSlider(tr("face width"))),
		m_guiManager(guiManager),
		m_helixAngleSlider(new LabeledRealValuedSlider(tr("helix angle"))),
		m_radiusSlider(new LabeledRealValuedSlider(tr("approximated radius"))),
		m_simpleGearInserted(false) {
	QPushButton* createButton = new QPushButton("create gear");

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(m_helixAngleSlider);
	layout->addWidget(m_faceWidthSlider);
	layout->addWidget(m_radiusSlider);
	layout->addWidget(createButton);
	setLayout(layout);

	connect(createButton, SIGNAL(clicked()), this, SLOT(createSimpleGear()));
	connect(m_faceWidthSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeFaceWidth(hpreal)));
	connect(m_helixAngleSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeHelixAngle(hpreal)));
	connect(m_radiusSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeRadius(hpreal)));

	InvoluteGear* involuteGear = new InvoluteGear();
	m_simpleGear = SimpleGear_ptr(involuteGear->toSimpleGear());
	delete involuteGear;

	updateRanges();
}

SimpleGearForm::~SimpleGearForm() {}

void SimpleGearForm::changeFaceWidth(hpreal faceWidth) {
	m_simpleGear->setFaceWidth(faceWidth);
	updateSimpleGear();
}

void SimpleGearForm::changeHelixAngle(hpreal angle) {
	m_simpleGear->setHelixAngle(angle);
	updateSimpleGear();
}

void SimpleGearForm::changeRadius(hpreal radius) {
	m_simpleGear->setRadius(radius);
	updateRanges();
	updateSimpleGear();
}

void SimpleGearForm::createSimpleGear() {
	if(m_simpleGearInserted)
		m_simpleGear = SimpleGear_ptr(new SimpleGear(*m_simpleGear));
	m_guiManager.insert(m_simpleGear,HP_TRIANGLE_MESH);
	m_guiManager.insert(m_simpleGear, HP_LINE_MESH);
	m_simpleGearInserted = true;
}

SimpleGear_ptr SimpleGearForm::getSimpleGear() const {
	return m_simpleGear;
}

void SimpleGearForm::reset() {
	InvoluteGear* involuteGear = new InvoluteGear();
	m_simpleGear = SimpleGear_ptr(involuteGear->toSimpleGear());
	delete involuteGear;
	m_simpleGearInserted = false;

	updateRanges();
}

void SimpleGearForm::setSimpleGear(SimpleGear_ptr simpleGear) {
	m_simpleGear = simpleGear;
	m_simpleGearInserted = true;
	
	updateRanges();
}

void SimpleGearForm::updateSimpleGear() {
	if(m_simpleGearInserted)
		m_guiManager.update(m_simpleGear);
}

void SimpleGearForm::updateRanges() {
	hpreal epsilon = 0.0001f;
	m_helixAngleSlider->setSliderValues(m_simpleGear->getHelixAngle(), -(epsilon + M_PI / 2.0f), epsilon + M_PI / 2.0f );
	m_faceWidthSlider->setSliderValues(m_simpleGear->getFaceWidth(), 0.0f, 2.0f);
	m_radiusSlider->setSliderValues(m_simpleGear->getRadius(), m_simpleGear->getRadius() / 2.0f, m_simpleGear->getRadius() * 2.0f);
}


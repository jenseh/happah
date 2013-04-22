#include "DiscForm.h"

#include <QPushButton>
#include <QVBoxLayout>

DiscForm::DiscForm(GUIManager& guiManager, QWidget* parent)
	: Form(parent),
		m_discInserted(false),
		m_guiManager(guiManager),
		m_pressureAngle(30.0),
		m_pressureAngleSlider(new LabeledRealValuedSlider(tr("pressure angle"))),
		m_radius(1.0),
		m_radiusSlider(new LabeledRealValuedSlider(tr("approximated radius"))) {
	QPushButton* createButton = new QPushButton("create disc");

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(m_radiusSlider);
	layout->addWidget(m_pressureAngleSlider);
	layout->addWidget(createButton);
	setLayout(layout);

	connect(createButton, SIGNAL(clicked()), this, SLOT(createDisc()));
	connect(m_radiusSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeRadius(hpreal)));
	connect(m_pressureAngleSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changePressureAngle(hpreal)));

	m_disc = DiscGenerator::generateDiscFrom(StandardProfile(m_radius/2.0, m_pressureAngle / 180.0 * M_PI, 0, 0));
	updateRanges();

}

DiscForm::~DiscForm() {}


void DiscForm::changeRadius(hpreal radius) {
	m_radius = radius;
	updateRanges();
	updateDisc();
}

void DiscForm::changePressureAngle(hpreal pressureAngle) {
	m_pressureAngle = pressureAngle;
	updateRanges();
	updateDisc();
}

void DiscForm::createDisc() {
	m_guiManager.insert(m_disc,HP_TRIANGLE_MESH);
	m_discInserted = true;
}

SurfaceOfRevolution_ptr DiscForm::getDisc() const {
	return m_disc;
}

void DiscForm::reset() {
	m_disc = DiscGenerator::generateDiscFrom(StandardProfile(m_radius/2.0,m_pressureAngle / 180.0 * M_PI ,0,0));
	m_discInserted = false;

	updateRanges();
}


void DiscForm::setDisc(SurfaceOfRevolution_ptr disc) {
	m_disc = disc;
	m_discInserted = true;

	updateRanges();
}

void DiscForm::updateDisc() {
	m_disc = DiscGenerator::generateDiscFrom(StandardProfile(m_radius/2.0,m_pressureAngle / 180.0 * M_PI ,0,0));
	if(m_discInserted)
		m_guiManager.update(m_disc);
}

void DiscForm::updateRanges() {
	m_radiusSlider->setSliderValues(m_radius, m_radius / 2.0f, m_radius * 2.0f);
	m_pressureAngleSlider->setSliderValues(m_pressureAngle, m_pressureAngle / 2.0f, m_pressureAngle * 2.0f);
}


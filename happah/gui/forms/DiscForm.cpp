#include "DiscForm.h"

#include <QPushButton>
#include <QVBoxLayout>

DiscForm::DiscForm(GUIManager& guiManager, QWidget* parent)
	: Form(parent),
		m_disc(new StandardProfileDisc()),
		m_discInserted(false),
		m_guiManager(guiManager),
		m_radiusSlider(new Slider(tr("approximated radius"))) {
	QPushButton* createButton = new QPushButton("create disc");

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(m_radiusSlider);
	layout->addWidget(createButton);
	setLayout(layout);

	connect(createButton, SIGNAL(clicked()), this, SLOT(createDisc()));
	connect(m_radiusSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeRadius(hpreal)));

	updateRanges();
}

DiscForm::~DiscForm() {}


void DiscForm::changeRadius(hpreal radius) {
	m_disc->setRadius(radius);
	updateRanges();
	updateDisc();
}

void DiscForm::createDisc() {
	m_guiManager.insert(m_disc);
	m_discInserted = true;
}

Disc_ptr DiscForm::getDisc() const {
	return m_disc;
}

void DiscForm::reset() {
	m_disc = Disc_ptr(new StandardProfileDisc());
	m_discInserted = false;

	updateRanges();
}


void DiscForm::setDisc(Disc_ptr disc) {
	m_disc = disc;
	m_discInserted = true;

	updateRanges();
}

void DiscForm::updateDisc() {
	if(m_discInserted)
		m_guiManager.update(m_disc);
}

void DiscForm::updateRanges() {
	m_radiusSlider->setSliderValues(m_disc->getRadius(), m_disc->getRadius() / 2.0f, m_disc->getRadius() * 2.0f);
}


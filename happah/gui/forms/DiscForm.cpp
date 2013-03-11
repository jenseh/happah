/*
 * DiscForm.cpp
 *
 *  Created on: 11.03.2013
 *      Author: jlabeit
 */

#include "DiscForm.h"

#include <QPushButton>
#include <QVBoxLayout>

DiscForm::DiscForm(DiscListener& discListener, QWidget* parent)
	: Form(parent),
		m_radiusSlider(new GearSlider(tr("approximated radius"))),
		m_discInserted(false),
		m_discListener(discListener) {
	QPushButton* createButton = new QPushButton("create disc");

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(m_radiusSlider);
	layout->addWidget(createButton);
	setLayout(layout);

	connect(createButton, SIGNAL(clicked()), this, SLOT(createDisc()));
	connect(m_radiusSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeRadius(hpreal)));

	m_disc = Disc_ptr(new Disc());
	updateRanges();
}

DiscForm::~DiscForm() {}


void DiscForm::changeRadius(hpreal radius) {
	m_disc->setRadius(radius);
	updateRanges();
	updateDisc();
}

void DiscForm::createDisc() {
	if(m_discInserted)
		m_disc = Disc_ptr(new Disc(*m_disc));
	m_discListener.insert(m_disc);
	m_discInserted = true;
}

Disc_ptr DiscForm::getDisc() const {
	return m_disc;
}

void DiscForm::reset() {
	m_disc = Disc_ptr(new Disc());
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
		m_discListener.update(m_disc);
}

void DiscForm::updateRanges() {
	m_radiusSlider->setSliderValues(m_disc->getRadius(), m_disc->getRadius() / 2.0f, m_disc->getRadius() * 2.0f);
}


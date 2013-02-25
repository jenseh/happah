#include "happah/gui/qt/GearSlider.h"
#include <iostream>
#include <sstream>
#include <iostream>
#include <cstring>
#include <QGridLayout>

GearSlider::GearSlider(const QString &title, bool smoothValues, QWidget *parent) : QGroupBox(parent) {

	setTitle(title);

	m_smoothValues = smoothValues;

	m_minLabel = new QLabel(this);
	m_minLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);

	m_maxLabel = new QLabel(this);
	m_maxLabel->setAlignment(Qt::AlignTop | Qt::AlignRight);

	m_valueLabel = new QLabel(this);
	m_valueLabel->setAlignment(Qt::AlignTop | Qt::AlignCenter);

	m_slider = new QSlider(Qt::Horizontal, this);
	if(m_smoothValues) {
		m_slider->setMinimum(0);
		m_slider->setMaximum(100);
	}

	m_slider->setToolTip(title);
	m_slider->setTracking(false);
	m_slider->setFocusPolicy(Qt::StrongFocus); //reach it through clicking or tabbing

	if(!m_smoothValues) {
		m_slider->setTickPosition(QSlider::TicksBelow);
		m_slider->setSingleStep(1);
		m_slider->setTickInterval(1);
	}

	m_minLabel->setBuddy(m_slider);
	m_maxLabel->setBuddy(m_slider);
	m_valueLabel->setBuddy(m_slider);

	QGridLayout *gridLayout = new QGridLayout;
	gridLayout->setHorizontalSpacing(0);
	gridLayout->setVerticalSpacing(0);
	gridLayout->setRowStretch(0, 3);
	gridLayout->setRowStretch(1, 1);
	gridLayout->addWidget(m_slider,     0, 0, 1, 3);
	gridLayout->addWidget(m_minLabel,   1, 0);
	gridLayout->addWidget(m_maxLabel,   1, 2);
	gridLayout->addWidget(m_valueLabel, 2, 1);
	setLayout(gridLayout);

	connect(m_slider, SIGNAL(valueChanged(int)), this, SLOT(valueChanged(int)));
}

void GearSlider::setSliderValues(hpreal value, hpreal min, hpreal max) {
	m_value	 = value;
	setRange(min, max);
}

void GearSlider::setRange(hpreal min, hpreal max) {
	m_minValue  = min;
	m_maxValue  = max;
	updateView();
}

void GearSlider::setNewRange(hpreal *minmax) {
	setRange(minmax[0], minmax[1]);
}

void GearSlider::updateView() {
	QString smin, smax, svalue;
	m_minLabel->setText(smin.setNum(m_minValue));
	m_maxLabel->setText(smax.setNum(m_maxValue));
	disconnect(m_slider, SIGNAL(valueChanged(int)), this, SLOT(valueChanged(int)));
	if (!m_smoothValues) {
		m_slider->setMinimum(0);
		m_slider->setMaximum(m_maxValue - m_minValue);
	}
	m_slider->setValue(getValueForSlider(m_value));
	connect(m_slider, SIGNAL(valueChanged(int)), this, SLOT(valueChanged(int)));
	m_valueLabel->setText(svalue.setNum(m_value));
}

hpreal GearSlider::getValue() {
	return m_value;
}

void GearSlider::valueChanged(int value) {
	QString str;
	m_value = getValueFromSlider(value);
	emit valueChanged(m_value);
	m_valueLabel->setText(str.setNum(m_value));
}

hpreal GearSlider::getValueFromSlider(int value) {
	uint stepSize = m_smoothValues ? 100 : (m_maxValue - m_minValue);
	return (m_minValue + value * (m_maxValue - m_minValue) / stepSize);
}

int GearSlider::getValueForSlider(hpreal value) {
	uint stepSize = m_smoothValues ? 100 : (m_maxValue - m_minValue);
	return static_cast<int>((value - m_minValue) * stepSize / (m_maxValue - m_minValue));
}

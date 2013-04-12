#include <QGridLayout>

#include "happah/gui/widgets/LabeledRealValuedSlider.h"

LabeledRealValuedSlider::LabeledRealValuedSlider(const QString &title, QWidget *parent) : QGroupBox(parent), m_emitValueChanged(true) {

	setTitle(title);

	m_minLabel = new QLabel(this);
	m_minLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);

	m_maxLabel = new QLabel(this);
	m_maxLabel->setAlignment(Qt::AlignTop | Qt::AlignRight);

	m_valueLabel = new QLabel(this);
	m_valueLabel->setAlignment(Qt::AlignTop | Qt::AlignCenter);

	m_slider = new QSlider(Qt::Horizontal, this);
	m_slider->setToolTip(title);
	m_slider->setTracking(false);
	m_slider->setFocusPolicy(Qt::StrongFocus); //reach it through clicking or tabbing

	//uses the default values for QSlider where possible
	m_slider->setMinimum(0);
	m_slider->setMaximum(100); //default is 99
	m_slider->setSingleStep(1);
	m_slider->setPageStep(10);

	m_minLabel->setBuddy(m_slider);
	m_maxLabel->setBuddy(m_slider);
	m_valueLabel->setBuddy(m_slider);

	QGridLayout *gridLayout = new QGridLayout;
	gridLayout->setHorizontalSpacing(0);
	gridLayout->setVerticalSpacing(0);
	gridLayout->setRowStretch(2, 2);
	gridLayout->addWidget(m_slider,     0, 0, 1, 3);
	gridLayout->addWidget(m_minLabel,   1, 0);
	gridLayout->addWidget(m_maxLabel,   1, 2);
	gridLayout->addWidget(m_valueLabel, 2, 1, Qt::AlignTop);
	setLayout(gridLayout);

	connect(m_slider, SIGNAL(valueChanged(int)), this, SLOT(sliderValueChanged(int)));
}

void LabeledRealValuedSlider::setSliderValue(hpreal value) {
	m_value = value;
	m_slider->setValue(toSlidersIntegerFromValue(m_value));
	updateLabels();
}
void LabeledRealValuedSlider::setSliderValues(hpreal value, hpreal min, hpreal max) {
	m_minValue = min;
	m_maxValue = max;
	m_emitValueChanged = true;
	m_value = value;
	m_slider->setValue(toSlidersIntegerFromValue(m_value));
	updateLabels();
}

void LabeledRealValuedSlider::setRange(hpreal min, hpreal max) {
	m_minValue = min;
	m_maxValue = max;
	m_emitValueChanged = false;
	m_slider->setValue(toSlidersIntegerFromValue(m_value));
	m_emitValueChanged = true;
	updateLabels();
}

void LabeledRealValuedSlider::updateLabels() {
	QString str;
	m_minLabel->setText(str.setNum(m_minValue));
	m_maxLabel->setText(str.setNum(m_maxValue));
	m_valueLabel->setText(str.setNum(m_value));
}

hpreal LabeledRealValuedSlider::getValue() const {
	return m_value;
}

void LabeledRealValuedSlider::sliderValueChanged(int value) {
	if(m_emitValueChanged) {
		QString str;
		m_value = toValueFromSlidersInteger(value);
		m_valueLabel->setText(str.setNum(m_value));
		emit valueChanged(m_value);
	}
}

hpreal LabeledRealValuedSlider::toValueFromSlidersInteger(int sliderValue) const {
	int resolution = m_slider->maximum() - m_slider->minimum(); // normally resolution = 100
	return m_minValue + (m_maxValue - m_minValue) * sliderValue / resolution;
}
int LabeledRealValuedSlider::toSlidersIntegerFromValue(hpreal value) const {
	int resolution = m_slider->maximum() - m_slider->minimum(); // normally resolution = 100
	return static_cast<int>((value - m_minValue) * resolution / (m_maxValue - m_minValue));
}
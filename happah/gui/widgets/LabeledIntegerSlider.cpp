#include <QGridLayout>

#include "happah/gui/widgets/LabeledIntegerSlider.h"

LabeledIntegerSlider::LabeledIntegerSlider(const QString &title, QWidget* parent) : QGroupBox(parent) {

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

	m_slider->setTickPosition(QSlider::TicksBelow);
	m_slider->setSingleStep(1);
	m_slider->setPageStep(10);
	m_slider->setTickInterval(1);

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
void LabeledIntegerSlider::setSliderValue(int value) {
	m_slider->setValue(value);
}
void LabeledIntegerSlider::setSliderValues(int value, int min, int max) {
	m_slider->setRange(min, max);
	m_slider->setValue(value);
	updateLabels();
}
void LabeledIntegerSlider::setRange(int min, int max) {
	m_slider->setRange(min, max);
	updateLabels();
}
void LabeledIntegerSlider::updateLabels() {
	QString str;
	m_minLabel->setText(str.setNum(m_slider->minimum()));
	m_maxLabel->setText(str.setNum(m_slider->maximum()));
	m_valueLabel->setText(str.setNum(m_slider->value()));
}
int LabeledIntegerSlider::getValue() const {
	return m_slider->value();
}
void LabeledIntegerSlider::sliderValueChanged(int value) {
	QString str;
	m_valueLabel->setText(str.setNum(value));
	emit valueChanged(value);
}
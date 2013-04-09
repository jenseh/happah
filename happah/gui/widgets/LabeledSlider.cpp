// #include <cstring>
#include <QGridLayout>
// #include <sstream>

#include "happah/gui/widgets/LabeledSlider.h"

template<class S, class T>
LabeledSlider::LabeledSlider(const QString &title, QWidget *parent) : QGroupBox(parent) {

	setTitle(title);

	m_minLabel = new QLabel(this);
	m_minLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);

	m_maxLabel = new QLabel(this);
	m_maxLabel->setAlignment(Qt::AlignTop | Qt::AlignRight);

	m_valueLabel = new QLabel(this);
	m_valueLabel->setAlignment(Qt::AlignTop | Qt::AlignCenter);

	m_slider = new S(Qt::Horizontal, this);

	m_slider->setToolTip(title);
	m_slider->setTracking(false);
	m_slider->setFocusPolicy(Qt::StrongFocus); //reach it through clicking or tabbing

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

	connect(m_slider, SIGNAL(valueChanged(T)), this, SLOT(valueChanged(T)));
}

template<class S = IntegerSlider, class T = int>
void LabeledSlider::setSliderValues(T value, T min, T max) {
	m_slider->setRange(min, max);
	m_slider->setValue(value);
	updateLabels();
}

template<class S = IntegerSlider, class T = int>
void LabeledSlider::setRange(T min, T max) {
	m_slider->setRange(min, max);
	updateLabels();
}

template<class S = IntegerSlider, class T = int>
void LabeledSlider::updateLabels() {
	QString str;
	m_minLabel->setText(str.setNum(m_slider->minimum()));
	m_maxLabel->setText(str.setNum(m_slider->maximum()));
	m_valueLabel->setText(str.setNum(m_slider->value()));
}

template<class S = IntegerSlider, class T = int>
T LabeledSlider::getValue() {
	return m_slider->value();
}

template<class S = IntegerSlider, class T = int>
void LabeledSlider::valueChanged(T value) {
	QString str;
	m_valueLabel->setText(str.setNum(value));
	emit sliderValueChanged(value);
}
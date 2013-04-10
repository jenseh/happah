#include "happah/gui/widgets/RealValuedSlider.h"

#include <iostream> //TODO: delete this line!

RealValuedSlider::RealValuedSlider(QWidget* parent) : QSlider(parent) {
	initialize();
}
RealValuedSlider::RealValuedSlider(Qt::Orientation orientation, QWidget* parent) : QSlider(orientation, parent) {
	initialize();
}
RealValuedSlider::~RealValuedSlider() {
}
//Uses the default values where possible
void RealValuedSlider::initialize() {
	QSlider::setMinimum(0);
	QSlider::setMaximum(100);
	QSlider::setValue(0);
	QSlider::setSingleStep(1);
	QSlider::setPageStep(10);
	m_value = 0.0f;
	m_qSliderValue = 0;
	m_min = 0.0f;
	m_max = 1.0f;

	connect(this, SIGNAL(rangeChanged(int, int)), this, SLOT(rangeChanged(int, int)));
	connect(this, SIGNAL(valueChanged(int)), this, SLOT(valueChanged(int)));
	connect(this, SIGNAL(sliderMoved(int)), this, SLOT(sliderMoved(int)));
}

void RealValuedSlider::rangeChanged(int min, int max) {
	std::cerr << "RealValuedSlider got a rangeChanged UNTIL NOW NOTHING IS EMITTED!!!" << std::endl;
	
}
void RealValuedSlider::valueChanged(int sliderValue) {
	if(m_qSliderValue != sliderValue) {
		m_qSliderValue = sliderValue;
		m_value = toValueFromSlidersInteger(sliderValue);
		emit valueChanged(toValueFromSlidersInteger(sliderValue));
	}
}
void RealValuedSlider::sliderMoved(int sliderValue) {
	emit sliderMoved(toValueFromSlidersInteger(sliderValue));
}

hpreal RealValuedSlider::maximum() const {
	return m_max;
}
hpreal RealValuedSlider::minimum() const {
	return m_min;
}
hpreal RealValuedSlider::pagestep() const {
	return toValueFromSlidersInteger(QSlider::pageStep());
}
void RealValuedSlider::setMaximum(hpreal maximum) {
	m_max = maximum;
	if(m_max < m_min) m_min = m_max;
	if(m_value > m_max) m_value = m_max;
	else m_qSliderValue = toSlidersIntegerFromValue(m_value);
	QSlider::setValue(toSlidersIntegerFromValue(m_value));
}
void RealValuedSlider::setMinimum(hpreal minimum) {
	m_min = minimum;
	if(m_max < m_min) m_max = m_min;
	if(m_value < m_min) m_value = m_min;
	else m_qSliderValue = toSlidersIntegerFromValue(m_value);
	QSlider::setValue(toSlidersIntegerFromValue(m_value));
}
void RealValuedSlider::setPageStep(hpreal pageStep) {
	QSlider::setPageStep(toSlidersIntegerFromValue(pageStep));
}
void RealValuedSlider::setRange(hpreal minimum, hpreal maximum) {
	m_min = minimum;
	if(maximum >= minimum) m_max = maximum;
	if(m_min <= m_value && m_value <= m_max) {
		m_qSliderValue = toSlidersIntegerFromValue(m_value);
	}
	else {
		if(m_value < m_min) m_value = m_min;
		if(m_value > m_max) m_value = m_max;
	}
	QSlider::setValue(toSlidersIntegerFromValue(m_value));
}
void RealValuedSlider::setSingleStep(hpreal singleStep) {
	QSlider::setSingleStep(toSlidersIntegerFromValue(singleStep));
}
void RealValuedSlider::setSliderPosition(hpreal position) {
	QSlider::setSliderPosition(toSlidersIntegerFromValue(position));
	//TODO: change m_value here??? what does this method do?
}
hpreal RealValuedSlider::singleStep() const {
	return toValueFromSlidersInteger(QSlider::singleStep());
}
hpreal RealValuedSlider::sliderPosition() const {
	return toValueFromSlidersInteger(QSlider::sliderPosition());
}
hpreal RealValuedSlider::value() const {
	std::cerr << "m_value and value should be the same and are: m_value = " << m_value << ", value = " << toValueFromSlidersInteger(QSlider::value());
	return m_value;
}
void RealValuedSlider::setValue(hpreal value) { //SLOT
	if(value < m_min) m_value = m_min;
	else if (value > m_max) m_value = m_max;
	else m_value = value;
	QSlider::setValue(toSlidersIntegerFromValue(value));
}

hpreal RealValuedSlider::toValueFromSlidersInteger(int sliderValue) const {
	int resolution = QSlider::maximum() - QSlider::minimum(); // normally range = 100
	return m_min + (m_max - m_min) * sliderValue / resolution;
}
int RealValuedSlider::toSlidersIntegerFromValue(hpreal value) const {
	int resolution = QSlider::maximum() - QSlider::minimum(); // normally range = 100
	return static_cast<int>((value - m_min) * resolution / (m_max - m_min));
}
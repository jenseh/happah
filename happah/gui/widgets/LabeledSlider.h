#ifndef LABELEDSLIDER_H
#define LABELEDDSLIDER_H

#include <QGroupBox>
#include <QLabel>
#include <QWidget>

#include "happah/gui/widgets/IntegerSlider.h"
#include "happah/HappahTypes.h"

template<class S = IntegerSlider, class T = int>
class LabeledSlider : public QGroupBox {
Q_OBJECT

public:
	LabeledSlider(const QString &title, QWidget *parent = 0);

	void setSliderValues(T value, T min, T max);
	void setRange(T min, T max);
	T getValue(); //current value

private:
	S* m_slider;
	T  m_minValue,  m_maxValue,  m_value;
	QLabel* m_minLabel, * m_maxLabel, * m_valueLabel;
	void updateLabels();

private slots:
	void valueChanged(T value);

signals:
	void sliderValueChanged(T value);


};

#endif // LABELEDSLIDER_H

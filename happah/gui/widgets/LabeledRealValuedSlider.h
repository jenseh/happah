#ifndef LABELEDREALVALUEDSLIDER_H
#define LABELEDREALVALUEDSLIDER_H

#include <QGroupBox>
#include <QLabel>
#include <QSlider>
#include <QWidget>

#include "happah/HappahTypes.h"

class LabeledRealValuedSlider: public QGroupBox {
Q_OBJECT

public:
	LabeledRealValuedSlider(const QString &title, QWidget *parent = 0);

	void setSliderValue(hpreal value);
	void setSliderValues(hpreal value, hpreal min, hpreal max);
	void setRange(hpreal min, hpreal max);
	hpreal getValue() const; //current value

protected:
	QSlider* m_slider;
	QLabel* m_minLabel, * m_maxLabel, * m_valueLabel;
	hpreal m_minValue, m_maxValue, m_value;
	bool m_emitValueChanged;

	void updateLabels();

private:
	int toSlidersIntegerFromValue(hpreal value) const;
	hpreal toValueFromSlidersInteger(int value) const;

private slots:
	void sliderValueChanged(int value);

signals:
	void valueChanged(hpreal value);

};

#endif // LABELEDREALVALUEDSLIDER_H

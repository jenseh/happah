#ifndef LABELEDINTEGERSLIDER_H
#define LABELEDINTEGERSLIDER_H

#include <QGroupBox>
#include <QLabel>
#include <QSlider>
#include <QWidget>

#include "happah/HappahTypes.h"

class LabeledIntegerSlider : public QGroupBox {
Q_OBJECT

public:
	LabeledIntegerSlider(const QString &title, QWidget* parent = 0);

	void setSliderValue(int value);
	void setSliderValues(int value, int min, int max);
	void setRange(int min, int max);
	int getValue() const; //current value

protected:
	QSlider* m_slider;
	QLabel* m_minLabel, * m_maxLabel, * m_valueLabel;
	bool m_emitValueChanged;

	void updateLabels();

private slots:
	void sliderValueChanged(int value);

signals:
	void valueChanged(int value);

};

#endif // LABELEDINTEGERSLIDER_H

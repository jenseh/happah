#ifndef REALVALUEDSLIDER_H
#define REALVALUEDSLIDER_H

#include <QSlider>
#include <QWidget>

#include "happah/HappahTypes.h"

class RealValuedSlider : public QSlider {
Q_OBJECT

public:
	RealValuedSlider(QWidget* parent = 0);
	RealValuedSlider(Qt::Orientation orientation, QWidget* parent = 0);
	~RealValuedSlider();
	hpreal maximum() const;
	hpreal minimum() const;
	hpreal pagestep() const;
	void setMaximum(hpreal);
	void setMinimum(hpreal);
	void setPageStep(hpreal);
	void setRange(hpreal min, hpreal max);
	void setSingleStep(hpreal);
	void setSliderPosition(hpreal);
	hpreal singleStep() const;
	hpreal sliderPosition() const;
	hpreal value() const; 
private:
	hpreal m_value;
	hpreal m_min, m_max;
	int m_qSliderValue;
	void initialize();
	hpreal toValueFromSlidersInteger(int sliderValue) const;
	int toSlidersIntegerFromValue(hpreal value) const;

public slots:
	void setValue(hpreal);
	void valueChanged(int);
	void rangeChanged(int, int);
	void sliderMoved(int);

signals:
	void rangeChanged(hpreal, hpreal);
	void sliderMoved(hpreal);
	void valueChanged(hpreal);
};

#endif //REALVALUEDSLIDER_H

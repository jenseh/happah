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
	hpreal maximum() const; // int maximum() const;
	hpreal minimum() const; // int minimum() const;
	hpreal pagestep() const; // int pagestep() const;
	void setMaximum(hpreal); // void setMaximum(int);
	void setMinimum(hpreal); // void setMinimum(int);
	void setPageStep(hpreal); // void setPageStep(int);
	void setRange(hpreal min, hpreal max); // void setRange(int min, int max);
	void setSingleStep(hpreal); // void setSingleStep(int);
	void setSliderPosition(hpreal); //void setSliderPosition(int);
	hpreal singleStep() const; // int singleStep() const;
	hpreal sliderPosition() const; //int sliderPosition() const;
	hpreal value() const; // int value() const;

private:
	hpreal m_value;
	hpreal m_min, m_max;
	// hpreal m_singleStep, m_pageStep;
	int m_qSliderValue;
	// hpuint m_qSliderMin, m_qSliderMax;
	// hpuint m_qSliderSingleStep, m_qSliderPageStep;
	void initialize();
	hpreal toValueFromSlidersInteger(int sliderValue) const;
	int toSlidersIntegerFromValue(hpreal value) const;

public slots:
	void setValue(hpreal); //void setValue(int);
	void valueChanged(int);
	void rangeChanged(int, int);

signals:
	void rangeChanged(hpreal, hpreal); // void rangeChanged(int min, int max);
	void sliderMoved(hpreal); // void sliderMoved(int value);
	void valueChanged(hpreal); //void valueChanged(int value);
};

#endif //REALVALUEDSLIDER_H

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
    LabeledRealValuedSlider(const QString &title, bool integer = false, QWidget *parent = 0);

    void setSliderValues(hpreal value, hpreal min, hpreal max);
    void setRange(hpreal min, hpreal max);
    hpreal getValue(); //current value

signals:
    void valueChanged(hpreal value);

private slots:
    void valueChanged(int value);

private:
    QSlider* m_slider;
    QLabel* m_minLabel, * m_maxLabel, * m_valueLabel;
    hpreal  m_minValue,  m_maxValue,  m_value;
    bool m_integer;

    void update();
    int toSlidersIntegerFromValue(hpreal value);
    hpreal toValueFromSlidersInteger(int value);
};

#endif // LABELEDREALVALUEDSLIDER_H

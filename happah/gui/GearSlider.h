#ifndef GEARSLIDER_H
#define GEARSLIDER_H

#include <QGroupBox>
#include <QLabel>
#include <QSlider>
#include <QWidget>

#include "happah/HappahTypes.h"
//TODO: rename GearSlider to Slider!!
class GearSlider: public QGroupBox {
    Q_OBJECT

public:
    GearSlider(const QString &title, bool smoothValues = true, QWidget *parent = 0);

    void setSliderValues(hpreal value, hpreal min, hpreal max);
    void setRange(hpreal min, hpreal max);
    hpreal getValue(); //current value

signals:
    //void valueChanged(int value);
    void valueChanged(hpreal value);

public:
    void setNewRange(hpreal *minmax);

private slots:
    void valueChanged(int value);

private:
    QSlider *m_slider;
    QLabel *m_minLabel, *m_maxLabel, *m_valueLabel;
    hpreal  m_minValue,  m_maxValue,  m_value;
    bool m_smoothValues;

    void updateView();
    int getValueForSlider(hpreal value);
    hpreal getValueFromSlider(int value);
};

#endif // GEARSLIDER_H

#ifndef GEARSLIDER_H
#define GEARSLIDER_H

#include <QGroupBox>
#include <QSlider>
#include <QLabel>
#include <QWidget>

#include "../../HappahTypes.h"

class GearSlider: public QGroupBox {
    Q_OBJECT

public:
    GearSlider(const QString &title, hpreal min, hpreal max, uint steps, QWidget *parent = 0);

    hpreal getValue(); //current value

signals:
    //void valueChanged(int value);
    void valueChanged(hpreal value);

public:
    void setNewRange(hpreal *minmax);

private slots:
/*    void setValue(int value);
    void setMinimum(int value);
    void setMaximum(int value);*/
    void valueChanged(int value);

private:
    QSlider *m_slider;
    QLabel *m_minLabel, *m_maxLabel, *m_valueLabel;
    hpreal  m_minValue,  m_maxValue,  m_value;
    uint m_steps;

    void updateView();
    int getValueForSlider(hpreal value);
    hpreal getValueFromSlider(int value);
};

#endif // GEARSLIDER_H

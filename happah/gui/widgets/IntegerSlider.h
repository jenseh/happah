#ifndef INTEGERSLIDER_H
#define INTEGERSLIDER_H

#include <QSlider>
#include <QWidget>
#include "happah/HappahTypes.h"

class IntegerSlider : public QSlider {
Q_OBJECT

public:
	IntegerSlider(QWidget* parent = 0);
	IntegerSlider(Qt::Orientation orientation, QWidget* parent = 0);
	~IntegerSlider();
};


#endif //INTEGERSLIDER_H
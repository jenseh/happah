#ifndef BSPLINECOMPONENT_H
#define BSPLINECOMPONENT_H

#include <QLine>
#include <QRect>
#include <QPainter>

#include "happah/gui/qt/Component.h"

class BSplineComponent: public Component {

public:
	BSplineComponent();
	~BSplineComponent();

	QRectF boundingRect() const;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
			QWidget *widget);

private:
	QLine line_;
	QRect bRect_;
};

#endif // BSPLINECOMPONENT_H

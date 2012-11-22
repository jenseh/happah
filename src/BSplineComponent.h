#ifndef BSPLINECOMPONENT_H
#define BSPLINECOMPONENT_H

#include <QLine>
#include <QRect>
#include <QPainter>

#include "Component.h"

class BSplineComponent : public Component {

private:
	QLine line;
	QRect bRect;
	
public:
	BSplineComponent();
	~BSplineComponent();

    QRectF getBoundingRect() const;

	void paint( QPainter *painter,
			const QStyleOptionGraphicsItem *option,
			QWidget *widget);

};


#endif // BSPLINECOMPONENT_H


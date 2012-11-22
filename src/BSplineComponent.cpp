
#include "BSplineComponent.h"

BSplineComponent::BSplineComponent() : Component() {
	setText("B-Spline");
	
	setPos(qrand() % 1024, qrand() % 768);

	int x1 = qrand() % 100;
	int x2 = qrand() % 100;
	int y1 = qrand() % 100;
	int y2 = qrand() % 100;

	line = QLine( x1, y1, x2, y2 );

	if(x2 < x1) {
		int tmp = x1; x1 = x2; x2 = tmp;
	}
	if(y2 < y1) {
		int tmp = y1; y1 = y2; y2 = tmp;
	}
	bRect = QRect( x1, y1, x2-x1, y2-y1 );
}

BSplineComponent::~BSplineComponent() {}


QRectF BSplineComponent::getBoundingRect() const {
	return bRect;
}

void BSplineComponent::paint( QPainter *painter,
		const QStyleOptionGraphicsItem *option,
		QWidget *widget) {
	painter->drawLine(line);
}

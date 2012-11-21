#include "Component.h"

Component::Component() : QListWidgetItem() {
	 setText("Empty item");
}

Component::~Component() {}

QRectF Component::boundingRect() const {
	return QRectF(0,0,0,0);
}

void Component::paint( QPainter *painter,
		const QStyleOptionGraphicsItem *option,
		QWidget *widget) {
}

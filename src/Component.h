#ifndef COMPONENT_H
#define COMPONENT_H

#include <QListWidgetItem>
#include <QGraphicsItem>

class Component: public QListWidgetItem, public QGraphicsItem {

public:
	Component(const QString *name = 0);
	~Component();

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
			QWidget *widget);

private:
    QRectF getBoundingRect() const;
};

#endif // COMPONENT_H

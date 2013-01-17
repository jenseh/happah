#ifndef EDITORSCENEITEM_H
#define EDITORSCENEITEM_H

#include <QGraphicsItem>

#include "../../core/Drawable2D.h"

class EditorSceneItem : public QGraphicsItem {

private:
	Drawable2D* m_drawable;

public:
	EditorSceneItem( Drawable2D* myDrawable );

	QRectF getBoundingRect() const;
	// Included for compatibility with other Qt version
	QRectF boundingRect() const;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
			QWidget *widget);

};

#endif // EDITORSCENEITEM_H

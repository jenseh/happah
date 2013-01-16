#include "EditorSceneItem.h"

#include "Painter2DQt.h"

EditorSceneItem::EditorSceneItem(Drawable2D* myDrawable)
		: m_drawable(myDrawable)
{
}

void EditorSceneItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
		QWidget* widget) {
	// TODO: Use singleton pattern for myPainter.
	Painter2DQt* myPainter = new Painter2DQt( painter );
	m_drawable->draw( myPainter );
}

QRectF EditorSceneItem::boundingRect() const {
	glm::vec2 min = glm::vec2(0,0);
	glm::vec2 max = glm::vec2(0,0);
	m_drawable->getBounds( &min, &max );
	return QRectF( QPointF( min.x, min.y ), QPointF( max.x, max.y) );
}

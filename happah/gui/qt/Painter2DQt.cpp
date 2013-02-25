#include "happah/gui/qt/Painter2DQt.h"

Painter2DQt::Painter2DQt( QPainter* painter ) 
		: m_painter(painter)
{
}

void Painter2DQt::drawPoint( glm::vec2 point ) {
	m_painter->drawEllipse( QPointF( point.x, point.y ), 5, 5 );
}

void Painter2DQt::drawPoint( glm::vec3 point ) {
	m_painter->drawEllipse( QPointF( point.x, point.y ), 5, 5 );
}

void Painter2DQt::drawLine( glm::vec2 pointA, glm::vec2 pointB ) {
	m_painter->drawLine( QPointF( pointA.x, pointA.y ), QPointF( pointB.x, pointB.y ) );
}

void Painter2DQt::drawDashedLine( glm::vec2 pointA, glm::vec2 pointB ) {
	QPen oldPen = m_painter->pen();
	m_painter->setPen( QPen(Qt::DashLine) );
	m_painter->drawLine( QPointF( pointA.x, pointA.y ), QPointF( pointB.x, pointB.y ) );
	m_painter->setPen( oldPen );
}

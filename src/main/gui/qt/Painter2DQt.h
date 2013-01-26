#ifndef PAINTER2DQT_H
#define PAINTER2DQT_H

#include <QPainter>

#include "../Painter2D.h"

class Painter2DQt : public Painter2D {

private:
	QPainter* m_painter;

public:
	Painter2DQt( QPainter* painter );

	void drawPoint( glm::vec2 point );
	void drawPoint( glm::vec3 point );

	void drawLine( glm::vec2 pointA, glm::vec2 pointB );

	void drawDashedLine( glm::vec2 pointA, glm::vec2 pointB );
};

#endif // PAINTER2DQT_H

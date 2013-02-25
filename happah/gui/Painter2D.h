#ifndef PAINTER2D_H
#define PAINTER2D_H

#include <glm/glm.hpp>

class Painter2D {

public:
	virtual void drawPoint( glm::vec3 point ); // ,color = 0 );
	virtual void drawPoint( glm::vec2 point );

	virtual void drawLine( glm::vec3 pointA, glm::vec3 pointB );
	virtual void drawLine( glm::vec2 pointA, glm::vec2 pointB );

	virtual void drawDashedLine( glm::vec3 pointA, glm::vec3 pointB );
	virtual void drawDashedLine( glm::vec2 pointA, glm::vec2 pointB );
};

#endif // PAINTER2D_H

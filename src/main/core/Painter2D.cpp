#include "Painter2D.h"

void Painter2D::drawPoint( glm::vec3 point ) {
	drawPoint( glm::vec2( point.x, point.y ) );
}

void Painter2D::drawPoint( glm::vec2 point ) {
}

void Painter2D::drawLine( glm::vec3 pointA, glm::vec3 pointB ) {
	drawLine( glm::vec2(pointA.x, pointA.y), glm::vec2(pointB.x, pointB.y) );
}

void Painter2D::drawLine( glm::vec2 pointA, glm::vec2 pointB ) {
}

void Painter2D::drawDashedLine( glm::vec3 pointA, glm::vec3 pointB ) {
	drawDashedLine( glm::vec2(pointA.x, pointA.y), glm::vec2(pointB.x, pointB.y) );
}

void Painter2D::drawDashedLine( glm::vec2 pointA, glm::vec2 pointB ) {
}

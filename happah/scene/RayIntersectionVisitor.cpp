#include "happah/scene/RayIntersectionVisitor.h"


RayIntersectionVisitor::RayIntersectionVisitor( Ray& ray ) : m_ray(ray) {}

hpvec3 RayIntersectionVisitor::getFirstIntersection() {
	return m_intersections.front().isecPoint;
}

bool RayIntersectionVisitor::hasGotIntersection() {
	return !m_intersections.empty();
}

void RayIntersectionVisitor::visit(PlaneNode& planeNode) {
	hpvec3 intersection;
	bool gotIntersection =  planeNode.getGeometry()->intersect(m_ray, intersection);
	if( gotIntersection ) {
		m_intersections.push_back( Intersection(intersection) );
	}
}

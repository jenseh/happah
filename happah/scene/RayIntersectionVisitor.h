#ifndef RAY_INTERSECTION_VISITOR_H
#define RAY_INTERSECTION_VISITOR_H

#include <list>

#include "happah/scene/PlaneNode.h"
#include "happah/HappahTypes.h"
#include "happah/math/Ray.h"
#include "happah/scene/SceneVisitor.h"

class RayIntersectionVisitor : public SceneVisitor {
private:
	struct Intersection {
		Intersection( hpvec3 point ) : isecPoint(point) {};
		hpvec3 isecPoint;
		// Node node;
	};

	Ray m_ray;
	std::list<Intersection> m_intersections;

public:
	RayIntersectionVisitor( Ray& ray );

	hpvec3 getFirstIntersection();
	bool hasGotIntersection();

	void visit(InvoluteGearNode& involuteGearNode) {};
	void visit(PlaneNode& planeNode);
	void visit(TriangleMeshNode& triangleMeshNode) {};
	void visit(LineMeshNode& lineMeshNode) {};
	void visit(PointCloudNode& pointCloudNode) {};
	void visit(RenderStateNode& renderStateNode) {};
	void visit(ElementRenderStateNode& elementRenderStateNode) {};
	void visit(SimpleGearNode& simpleGearNode) {};
	void visit(DiscNode& discNode) {};
	void visit(WormNode& wormNode) {};
	void visit(SpherePatchNode& spherePatchNode) {};
};

#endif // RAY_INTERSECTION_VISITOR_H

#pragma once

#include "happah/HappahTypes.h"
#include "happah/kdtree/BBox.h"
#include "happah/math/Triangle.h"
#include <iostream>

class Ray
{
private:
    hpvec3 m_origin;    // Origin point of the ray.
    hpvec3 m_direction;	// Normalized vector pointing in the direction of the ray.

    bool intersectTriangle(Triangle& triangle,hpvec3& hit);

    // Help functions:
    bool checkLineBox( hpvec3 boxPointMin, hpvec3 boxPointMax, hpvec3 linePoint1, hpvec3 linePoint2, hpvec3 &hitPoint);
    bool getIntersection( float fDst1, float fDst2, hpvec3 P1, hpvec3 P2, hpvec3 &Hit);
    bool inBox( hpvec3 hitPoint, hpvec3 boxPointMin, hpvec3 boxPointMax, const int axis);

public:
    /**
     * @brief Ray Standard constructor.
     */
    Ray();
    /**
     * @brief Ray constructor setting origin and direction of the ray and normalizes the direction.
     * @param origin origin of the ray.
     * @param direction direction of the ray. The direction must have a positive length or the constructor throws an exception.
     */
    Ray(hpvec3 origin, hpvec3 direction);
    // TODO: Used by BSplineCurve ( Erik? )
    hpreal distanceToPoint(hpvec3& point) const;
    /**
     * @brief gets origin of the ray.
     */
    const hpvec3& getOrigin()const;
    /**
     * @brief gets direction of the ray.
     */
    const hpvec3& getDirection()const;
    /**
     * @brief intersect checks if the line described by the ray's origin and its direction with length intersect a box.
     * @param box the box with which the intersection if checked.
     * @param length the length of vector added to the origin of the ray to calculate the second point of the line with which the intersection is checked.
     * @return true if the line intersects the box, else false.
     */
    bool intersect(BBox& box, hpreal length);
    /**
     * @brief examines Ray for intersection with a line in 2D. Therefore Ray is reduced to 2D by an orthogonal projection on xy plane
     * @param startLine the start point of the line to be examined for intersection with ray
     * @param endLine the end point of the line to be examined for intersection with ray
     * @param intersectionPoint if an intersection is found, found intersection point is written in intersectionPoint. If none is found, intersectionPoint isn't touched.
     * @return true if ray intersects the line, false otherwise
     */
    bool intersect(hpvec2 startLine, hpvec2 endLine, hpvec2& intersectionPoint) const;
    /**
     * @brief intersect calculates the intersection of the ray and the triangle.
     * @return the distance of the origin of the ray and the intersection point on the triangle surface, or infinity if no intersection occurred.
     */
    hpreal intersect(Triangle& triangle);
    /**
     * @brief transform transforms the ray with a transformation matrix.
     * @param matrix the transformation matrix with which the ray is transformed.
     */
    void transform(hpmat4x4& matrix);
    /**
     * @brief translateInDirection moves the origin along the direction vector.
     * @param delta the length by which the origin of the ray is translated.
     */
    void translateInDirection(hpreal delta);
};

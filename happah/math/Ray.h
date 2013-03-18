#pragma once

#include "happah/HappahTypes.h"
#include "happah/kdtree/BBox.h"
#include "happah/math/Triangle.h"

class Ray
{
private:
    hpvec3 m_origin;				// Origin point of the ray.
    hpvec3 m_direction;			// Normalized vector pointing in the direction of the ray.


    bool checkLineBox( hpvec3 boxPointMin, hpvec3 boxPointMax, hpvec3 linePoint1, hpvec3 linePoint2, hpvec3 &hitPoint);
    bool getIntersection( float fDst1, float fDst2, hpvec3 P1, hpvec3 P2, hpvec3 &Hit);
    bool inBox( hpvec3 hitPoint, hpvec3 boxPointMin, hpvec3 boxPointMax, const int axis);

public:

    Ray();
    Ray(hpvec3 orig, hpvec3 dir);
    hpreal intersectDistance(Triangle& triangle);
    bool intersects(BBox& box, hpreal length);
    void transform(hpmat4x4& matrix);
    void moveOrigin(hpreal delta);


};

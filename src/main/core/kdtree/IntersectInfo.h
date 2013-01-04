/*
    Code Based on "heatray" project by Cody White.
*/

#pragma once

#include <glm/glm.hpp>
#include "../primitives/Triangle.h"

struct IntersectInfo
{
	IntersectInfo (void)
	{
		time = HUGE_VAL;
        hit_point = glm::vec3(0,0,0);
	}

    glm::vec3	 hit_point;     // Point on the triangle intersected by the ray.
    double       time;          // Time to the hit point along the ray.
    Triangle	 *triangle;     // Triangle hit by the ray.
};


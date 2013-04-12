#pragma once

#include "happah/HappahTypes.h"
#include <glm/gtx/intersect.hpp>
#include <glm/glm.hpp>

struct Triangle{
    hpvec3 vertices[3];

    Triangle(hpvec3 vertexA, hpvec3 vertexB, hpvec3 vertexC){
      vertices[0] = vertexA;
      vertices[1] = vertexB;
      vertices[2] = vertexC;
    }

    hpvec3 computeNormal() {
    	return glm::cross(vertices[1] - vertices[0],
    					  vertices[2] - vertices[0]);
    }
};

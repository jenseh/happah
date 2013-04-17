#pragma once

#include "happah/HappahTypes.h"
#include <glm/gtx/intersect.hpp>
#include <glm/glm.hpp>

struct Triangle{
	/**
	 * @brief vertices stores the three vertices of the triangle.
	 */
    hpvec3 vertices[3];
    /**
     * @brief Triangle constructor setting the vertices of the triangle.
     */
    Triangle(hpvec3 vertexA, hpvec3 vertexB, hpvec3 vertexC){
      vertices[0] = vertexA;
      vertices[1] = vertexB;
      vertices[2] = vertexC;
    }
    /**
     * @brief computeNormal computes the normal with the cross product of the span vectors of the triangle.
     * @return unnormalized normal of the triangle.
     */
    hpvec3 computeNormal() {
    	return glm::cross(vertices[1] - vertices[0],
    					  vertices[2] - vertices[0]);
    }
};

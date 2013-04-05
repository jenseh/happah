#pragma once

#include "happah/HappahTypes.h"
#include <glm/gtx/intersect.hpp>
#include <glm/glm.hpp>

struct Triangle{
    hpvec3 vertices[3];
    hpvec3 normals[3];

    Triangle(){
    }
//    Triangle(hpvec3 _vertices[3]) : vertices(_vertices){
//    }
    Triangle(hpvec3 vertexA, hpvec3 vertexB, hpvec3 vertexC){
      vertices[0] = vertexA;
      vertices[1] = vertexB;
      vertices[2] = vertexC;
    }

    /**
      * Check for a ray collision.
      * @param ray_origin Origin of the incoming ray.
      * @param ray_direction Direction of the incoming ray.
      * @param time Time of intersection.
      */
    bool checkRayIntersection (hpvec3 &ray_origin, hpvec3 &ray_direction, double &time)
    {
        hpvec3 baryPos;
        if( glm::intersectRayTriangle(ray_origin, ray_direction, vertices[0], vertices[1], vertices[2], baryPos) ){
            time = glm::distance(baryPos, ray_origin) / ray_direction.length();
            return true;
        }
        return false;
    }

    hpvec3 computeNormal() {
    	return glm::cross(vertices[1] - vertices[0],
    					  vertices[2] - vertices[0]);
    }
};



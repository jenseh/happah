#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

struct Triangle{
    glm::vec3 vertices[3];
    glm::vec3 normals[3];

    /**
      * Check for a ray collision.
      * @param ray_origin Origin of the incoming ray.
      * @param ray_direction Direction of the incoming ray.
      * @param time Time of intersection.
      */
    bool checkRayIntersection (glm::vec3 &ray_origin, glm::vec3 &ray_direction, double &time)
    {
        glm::vec3 baryPos;
        if( glm::intersectRayTriangle(ray_origin, ray_direction, vertices[0], vertices[1], vertices[2], baryPos) ){
            time = glm::distance(baryPos, ray_origin) / ray_direction.length();
            return true;
        }
        return false;
    }
};



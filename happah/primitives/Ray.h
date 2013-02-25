#pragma once

#include <glm/glm.hpp>

struct Ray
{
    glm::vec3 origin;				// Origin point of the ray.
    glm::vec3 direction;			// Normalized vector pointing in the direction of the ray.
    glm::vec3 inverse_direction; 	// Used for intersection tests.
    int         id;					// ID of this ray.

    void transform(glm::mat4& matrix){
        glm::vec4 point1,point2;

        point1[0] = origin[0];
        point1[1] = origin[1];
        point1[2]= origin[2];
        point1[3] = 1;

        point2 = point1;
        point2[0] += direction[0];
        point2[1] += direction[1];
        point2[2] += direction[2];

        point1 = matrix * point1;
        point2 = matrix * point2;
        origin = (glm::vec3)point1;
        direction = (glm::vec3)(point2 - point1);
        inverse_direction = (glm::vec3)(point1 - point2);
    }
};

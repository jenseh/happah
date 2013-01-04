#pragma once

#include <glm/glm.hpp>

struct Ray
{
    glm::vec3 origin;				// Origin point of the ray.
    glm::vec3 direction;			// Normalized vector pointing in the direction of the ray.
    glm::vec3 inverse_direction; 	// Used for intersection tests.
    int         id;					// ID of this ray.
};

#pragma once

#include "happah/HappahTypes.h"

struct Ray
{
    hpvec3 origin;				// Origin point of the ray.
    hpvec3 direction;			// Normalized vector pointing in the direction of the ray.
    int         id;					// ID of this ray.

    void transform(hpmat4x4& matrix);
};

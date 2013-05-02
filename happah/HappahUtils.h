#ifndef HAPPAH_UTILS_H_
#define HAPPAH_UITLS_H_

#include <cmath>
#include <iostream>
#include "happah/HappahTypes.h"

namespace HPUtils{

	// Switch netween cartesian and polar coordinates
    hpvec3 cartesianToPolarCoordinates(hpvec3 cartesian,hpvec3 center = hpvec3(0.0f,0.0f,0.0f));
    hpvec3 polarToCartesianCoordinates(hpvec3 polar);

    // Caluclate Line Intersection in 2D Space (Warning: z value is never used)
    hpvec3   calculate2DLineIntersection(hpvec3 a1,hpvec3 a2, hpvec3 b1, hpvec3 b2);

    // returns sign of an number
    template <typename T> int sgn(T val) {
        return (T(0) < val) - (val < T(0));
    }
};

std::ostream& operator<<( std::ostream& os, const hpvec3& vec );
std::ostream& operator<<( std::ostream& os, const hpvec2& vec );



#endif

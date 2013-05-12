#ifndef MATINGPOINT_H
#define MATINGPOINT_H

#include "happah/HappahTypes.h"
#include "glm/glm.hpp"
#include "glm/gtx/rotate_vector.hpp"


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#undef NO_ERROR
#endif

enum class ErrorCode {
	NO_ERROR,
	NO_CUT_WITH_REFERENCE_RADIUS,
	NO_THICKNESS
};

struct MatingPoint {
	hpvec2 point;
	hpvec2 normal; //must be normalized!
	hpvec2 originPoint;
	hpvec2 originNormal; //must be normalized!
	hpreal intersectionRefRadiusAngle;
	hpreal forbiddenAreaLength;
	hpvec2 forbiddenAreaEndPoint;
	ErrorCode error;
	bool isCovered;

	void rotate(hpreal rotation) {
		if(error != ErrorCode::NO_CUT_WITH_REFERENCE_RADIUS) {
			point = glm::rotate(point, rotation);
			normal = glm::rotate(normal, rotation);
			if(error != ErrorCode::NO_THICKNESS) {
				forbiddenAreaEndPoint = glm::rotate(forbiddenAreaEndPoint, rotation);
			}
		}
	}
};


#endif //MATINGPOINT_H

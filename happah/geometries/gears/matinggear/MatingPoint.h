#ifndef MATINGPOINT_H
#define MATINGPOINT_H

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
};


#endif //MATINGPOINT_H
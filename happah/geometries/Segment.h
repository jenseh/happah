#pragma once

#include "happah/HappahTypes.h"

template<typename T>
struct Segment {
	T& a;
	T& b;
};

typedef Segment<hpvec2> Segment2D;
typedef Segment<hpvec3> Segment3D;


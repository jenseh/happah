#pragma once

#include <memory>

#include "happah/HappahTypes.h"

using namespace std;

template<typename T>
class tRay {

public:
	static bool isInHalfspace(const T& origin, const T& direction, const T& point);

	tRay(const T& origin, const T& direction);
	~tRay();

	const T& getDirection() const;
	const T& getOrigin() const;

	bool isInHalfspace(const T& point);

private:
	T m_direction;
	T m_origin;

};
typedef tRay<hpvec2> Ray2D;
typedef shared_ptr<Ray2D> Ray2D_ptr;
typedef tRay<hpvec3> Ray3D;
typedef shared_ptr<Ray3D> Ray3D_ptr;

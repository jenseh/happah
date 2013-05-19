#include "happah/geometries/tRay.h"

template<typename T>
tRay<T>::tRay(const T& origin, const T& direction) : m_direction(direction), m_origin(origin) {}

template<typename T>
tRay<T>::~tRay() {}

template<typename T>
const T& tRay<T>::getDirection() const {
	return m_direction;
}

template<typename T>
const T& tRay<T>::getOrigin() const {
	return m_origin;
}

template<typename T>
bool tRay<T>::isInHalfspace(const T& origin, const T& direction, const T& point) {
	//TODO
	return false;
}

template<typename T>
bool tRay<T>::isInHalfspace(const T& point) {
	return tRay::isInHalfspace(m_origin, m_direction, point);
}

template class tRay<hpvec2>;
template class tRay<hpvec3>;

#pragma once

#include "happah/HappahTypes.h"

class Sphere {

public:
	/** The method determines whether there exists a sphere with the given radius that touches the three vertices and if such a sphere exists, stores in the referenced locations the two possible centers for this sphere.
	 *  @param v1 first vertex
	 *  @param v2 second vertex
	 *  @param v3 third vertex
	 *  @param radius radius of the desired sphere
	 *  @param center1 reference to where the first center should be stored
	 *  @param center2 reference to where the second center should be stored
	 *  @return false if such a sphere does not exist and true if there exists such a sphere
	 */
	static bool isSphere(const hpvec3& v1, const hpvec3& v2, const hpvec3& v3, hpreal radius, hpvec3& center1, hpvec3& center2);

	Sphere(const hpvec3& center, hpreal radius);
	~Sphere();

private:
	hpvec3 m_center;
	hpreal m_radius;

};

#include "happah/math/Ray.h"

void Ray::transform(hpmat4x4& matrix){
	hpvec4 point1,point2;

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
}

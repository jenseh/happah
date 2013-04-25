#include "happah/HappahUtils.h"

namespace HPUtils
{
hpvec3 cartesianToPolarCoordinates(hpvec3 cartesian,hpvec3 center){
	hpreal radius = sqrt((cartesian.x*cartesian.x)+(cartesian.y*cartesian.y));
	hpreal x = cartesian.x-center.x;
	hpreal y = cartesian.y-center.y;
	hpreal phi = 0.0f;
	if (y >= 0){
	if (x>0.0f)
		phi = atan(y/x);
	if (x<0.0f)
		phi = M_PI+atan(y/x);
	if (x==0.0f)
		phi = M_PI/2.0f;
	}
	else {
		if (x>0.0f){
			phi=2*M_PI+atan(y/x);
		}
		if (x<0.0f){
			phi = atan(y/x) + M_PI;
		}
		if (x==0.0f){
			phi= 3*M_PI/2.0f;
		}

	}

	hpvec3 polar = hpvec3(phi,0.0f,radius);
	return polar;
}

hpvec3 polarToCartesianCoordinates(hpvec3 polar){
	hpvec3 cartesian;
	cartesian.x = polar.z * cos(polar.x);
	cartesian.y = polar.z * sin(polar.x);
	cartesian.z = 0.0f;
	return cartesian;
}

hpvec3 calculate2DLineIntersection(hpvec3 a1,hpvec3 a2, hpvec3 b1, hpvec3 b2){
	hpreal x1 = a1.x , x2=a2.x, x3 = b1.x, x4 = b2.x;
	hpreal y1 = a1.y , y2=a2.y, y3 = b1.y, y4 = b2.y;

	hpreal m = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);
	if (m == 0)
		return hpvec3(0.0f,0.0f,0.0f);
	float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
	float x = ( pre * (x3 - x4) - (x1 - x2) * post ) / m;
	float y = ( pre * (y3 - y4) - (y1 - y2) * post ) / m;

	return hpvec3(x,y,0.0f);
}

}

std::ostream& operator<<( std::ostream& os, const hpvec3& vec ) {
	os << "( " << vec.x << " | " << vec.y << " | " << vec.z << " )";
	return os;
}

std::ostream& operator<<( std::ostream& os, const hpvec2& vec ) {
	os << "( " << vec.x << " | " << vec.y << " )";
	return os;
}


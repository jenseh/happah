#include "happah/math/Ray.h"

Ray::Ray() {

}
Ray::Ray(hpvec3 origin, hpvec3 direction):m_origin(origin), m_direction(direction){
    if( m_direction == hpvec3(0) )
		throw;
	m_direction = glm::normalize(m_direction);
}

void Ray::transform(hpmat4x4& matrix){
	hpvec4 point1,point2;

	point1[0] = m_origin[0];
	point1[1] = m_origin[1];
	point1[2]= m_origin[2];
	point1[3] = 1;

	point2 = point1;
	point2[0] += m_direction[0];
	point2[1] += m_direction[1];
	point2[2] += m_direction[2];

	point1 = matrix * point1;
	point2 = matrix * point2;
	m_origin = (glm::vec3)point1;
	m_direction = (glm::vec3)(point2 - point1);
	m_direction = glm::normalize(m_direction);
}

const hpvec3& Ray::getOrigin()const {
	return m_origin;
}

const hpvec3& Ray::getDirection()const {
	return m_direction;
}

hpreal Ray::intersectDistance(Triangle& triangle){
	hpvec3 position;
	if( !intersectTriangle(triangle.vertices[0], triangle.vertices[1], triangle.vertices[2], position) )
		return 1000000;
	return glm::distance(m_origin, position);
}

bool Ray::intersects(BBox& box, hpreal length){
	hpvec3 hitPoint;
	return checkLineBox(*(box.getMin()), *(box.getMax()), m_origin, m_origin + m_direction * length, hitPoint);
}

bool Ray::checkLineBox( hpvec3 boxPointMin, hpvec3 boxPointMax, hpvec3 linePoint1, hpvec3 linePoint2, hpvec3 &hitPoint) {
if (linePoint2.x < boxPointMin.x && linePoint1.x < boxPointMin.x) return false;
if (linePoint2.x > boxPointMax.x && linePoint1.x > boxPointMax.x) return false;
if (linePoint2.y < boxPointMin.y && linePoint1.y < boxPointMin.y) return false;
if (linePoint2.y > boxPointMax.y && linePoint1.y > boxPointMax.y) return false;
if (linePoint2.z < boxPointMin.z && linePoint1.z < boxPointMin.z) return false;
if (linePoint2.z > boxPointMax.z && linePoint1.z > boxPointMax.z) return false;
if (linePoint1.x > boxPointMin.x && linePoint1.x < boxPointMax.x &&
    linePoint1.y > boxPointMin.y && linePoint1.y < boxPointMax.y &&
    linePoint1.z > boxPointMin.z && linePoint1.z < boxPointMax.z)
    {hitPoint = linePoint1;
    return true;}
if ( (getIntersection( linePoint1.x-boxPointMin.x, linePoint2.x-boxPointMin.x, linePoint1, linePoint2, hitPoint) && inBox( hitPoint, boxPointMin, boxPointMax, 1 ))
  || (getIntersection( linePoint1.y-boxPointMin.y, linePoint2.y-boxPointMin.y, linePoint1, linePoint2, hitPoint) && inBox( hitPoint, boxPointMin, boxPointMax, 2 ))
  || (getIntersection( linePoint1.z-boxPointMin.z, linePoint2.z-boxPointMin.z, linePoint1, linePoint2, hitPoint) && inBox( hitPoint, boxPointMin, boxPointMax, 3 ))
  || (getIntersection( linePoint1.x-boxPointMax.x, linePoint2.x-boxPointMax.x, linePoint1, linePoint2, hitPoint) && inBox( hitPoint, boxPointMin, boxPointMax, 1 ))
  || (getIntersection( linePoint1.y-boxPointMax.y, linePoint2.y-boxPointMax.y, linePoint1, linePoint2, hitPoint) && inBox( hitPoint, boxPointMin, boxPointMax, 2 ))
  || (getIntersection( linePoint1.z-boxPointMax.z, linePoint2.z-boxPointMax.z, linePoint1, linePoint2, hitPoint) && inBox( hitPoint, boxPointMin, boxPointMax, 3 )))
	return true;

return false;
}

bool Ray::intersectTriangle(hpvec3 e, hpvec3 f, hpvec3 g,hpvec3& hit){
 float result;
 float epsilon = 0.00001f;

 hpvec3 v1 = f-e;
 hpvec3 v2 = g-e;
 hpvec3 q = glm::cross(m_direction,v2);
 float det = glm::dot(v1,q);
 if (det>(-epsilon)&&det<(epsilon)){
	 return false;
   }
 float inv = (1/det);
 hpvec3 s = m_origin-e;
 float u = inv*glm::dot(s,q);
 if (u<0.0f){
	 return false;
   }
 hpvec3 r=glm::cross(s,v1);
 float v=inv*glm::dot(m_direction,r);
 if (v<0.0f-epsilon || u+v > 1.0f+epsilon){
	 return false;
   }
 float t= inv*glm::dot(v2,r);
 hit= m_origin+t*m_direction;

 return true;
}



bool inline Ray::getIntersection( float fDst1, float fDst2, hpvec3 P1, hpvec3 P2, hpvec3 &Hit) {
	if ( (fDst1 * fDst2) >= 0.0f) return false;
	if ( fDst1 == fDst2) return false;
	Hit = P1 + (P2-P1) * ( -fDst1/(fDst2-fDst1) );
	return true;
}

bool inline Ray::inBox( hpvec3 hitPoint, hpvec3 boxPointMin, hpvec3 boxPointMax, const int axis) {
	if ( axis==1 && hitPoint.z > boxPointMin.z && hitPoint.z < boxPointMax.z && hitPoint.y > boxPointMin.y && hitPoint.y < boxPointMax.y) return true;
	if ( axis==2 && hitPoint.z > boxPointMin.z && hitPoint.z < boxPointMax.z && hitPoint.x > boxPointMin.x && hitPoint.x < boxPointMax.x) return true;
	if ( axis==3 && hitPoint.x > boxPointMin.x && hitPoint.x < boxPointMax.x && hitPoint.y > boxPointMin.y && hitPoint.y < boxPointMax.y) return true;
	return true;
}

void Ray::moveOrigin(hpreal delta){
    m_origin += (delta * m_direction);
}


#include "happah/math/Ray.h"

Ray::Ray() {

}
Ray::Ray(hpvec3 origin, hpvec3 direction):m_origin(origin), m_direction(direction){
    if( m_direction == hpvec3(0) )
		throw;
	m_direction = glm::normalize(m_direction);
}


const hpvec3& Ray::getDirection()const {
    return m_direction;
}

const hpvec3& Ray::getOrigin()const {
    return m_origin;
}


hpreal Ray::distanceToPoint(hpvec3& point) const {
    //The ray "origin+t*direction" is searched for the value t
    //where "point-ray" is vertical to the ray
    //=> (point -(origin + t * direction)) = 0
    //based on this, it follows:
    hpreal t = glm::dot((point - m_origin), m_direction) / glm::dot(m_direction, m_direction);
    if(t >= 0.0f)
        return glm::distance(m_origin + t * m_direction, point);
    else
        return  std::numeric_limits<hpreal>::max();
}

bool Ray::intersect(BBox& box, hpreal length){
    hpvec3 hitPoint;
    return checkLineBox(*(box.getMin()), *(box.getMax()), m_origin, m_origin + m_direction * length, hitPoint);
}

bool Ray::intersect(hpvec2 startLine, hpvec2 endLine, hpvec2& intersectionPoint) const {
    hpvec2 x = startLine - endLine;
    hpvec2 y = hpvec2(m_direction.x, m_direction.y);
    hpvec2 z = startLine - hpvec2(m_origin.x, m_origin.y);
    hpmat2x2 matrix = hpmat2x2(x, y);
    if(glm::determinant(matrix) != 0) {
        hpmat2x2 invMatrix = glm::inverse(matrix);
        hpvec2 t = invMatrix * z;
        if (0 <= t.x && 0 <= t.y && t.x <= 1) {
            intersectionPoint = hpvec2(m_origin.x, m_origin.y) + t.y * y;
            return true;
        }
    }
    return false;
}

hpreal Ray::intersect(Triangle& triangle){
    hpvec3 hit;
    if( !intersectTriangle(triangle, hit) )
        return std::numeric_limits<hpreal>::max();
    return glm::distance(m_origin, hit);
}

bool Ray::intersectTriangle(Triangle& triangle,hpvec3& hit){
     float epsilon = 0.00001f;

     hpvec3 v1 = triangle.vertices[1] - triangle.vertices[0];
     hpvec3 v2 = triangle.vertices[2] - triangle.vertices[0];
     hpvec3 q = glm::cross(m_direction,v2);
     float det = glm::dot(v1,q);
     if( det > (-epsilon) && det < epsilon ){
         return false;
       }
     float inv = (1/det);
     hpvec3 s = m_origin - triangle.vertices[0];
     float u = inv*glm::dot(s,q);
     if(u<0.0f){
         return false;
       }
     hpvec3 r = glm::cross(s,v1);
     float v = inv * glm::dot(m_direction,r);
     if (v < 0.0f - epsilon || u + v > 1.0f + epsilon){
         return false;
       }
     float t = inv * glm::dot(v2,r);
     hit = m_origin + t * m_direction;
     return true;
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

void Ray::translateInDirection(hpreal delta){
    m_origin += (delta * m_direction);
}


// Help functions:

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



/*
bool Ray::insectTriangle(Triangle& triangle, hpvec3& hit) {
    hpvec3 triangleNormal = glm::cross(triangle.vertices[0], triangle.vertices[1]);
    hpreal denominator = glm::dot(m_direction, triangleNormal);
    if( denominator < 0.0001 ) { // ray parallel to tiangle plane
        return false;
    }
    hpreal t = (glm::dot(triangle.vertices[0],triangleNormal) - glm::dot(m_origin,triangleNormal)) / denominator;
    hit = m_origin + t*m_direction;
    // Check if hit is inside the triangle
    if( glm::dot(glm::cross(triangle.vertices[1] - triangle.vertices[0], hit - triangle.vertices[0]), triangleNormal) < 0.0 ){
        return false;
    }
    if( glm::dot(glm::cross(triangle.vertices[2] - triangle.vertices[1], hit - triangle.vertices[1]), triangleNormal) < 0.0 ){
        return false;
    }
    if( glm::dot(glm::cross(triangle.vertices[0] - triangle.vertices[2], hit - triangle.vertices[2]), triangleNormal) < 0.0 ){
        return false;
    }
    return true;
}
*/

/*
void Ray::print() {
    std::cout<<"Origin:"<<m_origin.x<<"/"<<m_origin.y<<"/"<<m_origin.z<<std::endl;
    std::cout<<"Direction:"<<m_direction.x<<"/"<<m_direction.y<<"/"<<m_direction.z<<std::endl;
}
*/


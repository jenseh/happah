#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include "Triangle.h"

struct Circle {
	glm::vec3 m_center;
	glm::vec3 m_normal;
	float m_radius;

	Circle(glm::vec3 center, glm::vec3 normal, float radius) :
			m_center(center), m_normal(normal), m_radius(radius) {
	}

	// This method checks whether a (filled) triangle intersects a (filled) circle.
	// It works as follows:
	// Check collinearity of plane normals
	//    - Yes: Check whether planes are identical
	//        - Yes: Check whether triangle is inside circle
	//          - Yes: -> Return true
	//          - No: Check whether circle is inside triangle
	//            - Yes: -> Return true
	//            - No: -> Return false
	//        - No: -> Return false
	//    - No: Determine the intersection line, Check if line hits sphere and get hitpoints
	//        - Yes: Check if line hits circle and get hitpoints
	//            - Yes: Check if range between respective hitpoints overlaps
	//                - Yes: ->Return true
	//                - No: -> Return false
	//            - No: -> Return false
	//        - No: -> Return false
	bool checkTriangleIntersection(Triangle& triangle) {
		glm::vec3 t_normal = glm::cross(triangle.vertices[1] - triangle.vertices[0],
				triangle.vertices[2] - triangle.vertices[0]);

		// Start with a plane-plane intersection

		// Sanity check: If a normal vector is all 0, then abort
		bool nullNormal = isNullVector(t_normal) || isNullVector(m_normal);
		if (nullNormal) {
			std::cerr << "Error: One of the geometry's normals is a null vector!" << std::endl;
			 // std::cout << t_normal.x << ", " << t_normal.y << ", " << t_normal.z << std::endl;
			 // std::cout << m_normal.x << ", " << m_normal.y << ", " << m_normal.z << std::endl;
			return false;
		}
//		 std::cout << "t_normal: " << t_normal.x << ", " << t_normal.y << ", " << t_normal.z << std::endl;
		// std::cout << "m_normal: " << m_normal.x << ", " << m_normal.y << ", " << m_normal.z << std::endl;

		//1: Check collinearity of normal vectors
		bool collinear = linearDependent(m_normal, t_normal);
		// std::cout << "Info: Collinear: " << collinear << std::endl;

		if (collinear) {
			//2: Check whether planes are identical or parallel
			bool identical = floatEquals(glm::dot(m_center - triangle.vertices[2], t_normal), 0.0f);
			// std::cout << "Info: Identical: " << identical << std::endl;

			//2a: If planes are parallel, return false
			if (!identical) {
				// std::cout << "Exiting due to: Collinear | Planes are parallel!" << std::endl;
				return false;
			}

			//2b: If planes are identical, compute planar intersection of triangle and circle
			else {
				// Compute the closest points on triangle sides to the circle center
				glm::vec3 closestPoint01 = glm::closestPointOnLine(m_center, triangle.vertices[0],
						triangle.vertices[1]);
				glm::vec3 closestPoint12 = glm::closestPointOnLine(m_center, triangle.vertices[1],
						triangle.vertices[2]);
				glm::vec3 closestPoint02 = glm::closestPointOnLine(m_center, triangle.vertices[0],
						triangle.vertices[2]);

				// Compute the respective distances
				float distC01 = glm::distance(m_center, closestPoint01);
				float distC12 = glm::distance(m_center, closestPoint12);
				float distC02 = glm::distance(m_center, closestPoint02);

				// Check whether any distance is shorter than the radius
				bool triangleInside = floatLess(distC01, m_radius) || floatLess(distC12, m_radius) || floatLess(distC02, m_radius);
				// std::cout << "Info: triangleInside: " << triangleInside << std::endl;

				if (triangleInside) {
					// ..then the triangle is "inside" the circle
				    // std::cout << distC01 << ", " << distC12 << ", " << distC02 << ", " << m_radius << std::endl;
				    // std::cout << "Exiting due to: Collinear | Triangle inside circle!" << std::endl;
				    return true;
				} else {
					// Now there is either no intersection or the circle is inside the triangle
					if (pointInTriangle(m_center, triangle)) {
						// std::cout << "Exiting due to: Collinear | Circle inside triangle!" << std::endl;
						return true;
					} else {
						// std::cout << "Exiting due to: Collinear | Circle not inside triangle!" << std::endl;
						return false;
					}
				}
			}
		} else {
			//2: Planes must collide in a common line
			glm::vec3 linePoint;
			glm::vec3 lineDirection;
			intersectPlanes(t_normal, triangle.vertices[0], m_normal, m_center, linePoint, lineDirection);

			// Check whether this line hits our sphere
			// Check whether distance is shorter than the radius
			glm::vec3 circleIntersectionA;
			glm::vec3 circleIntersectionB;
			if (intersectPlanarLineCircle(m_center, m_radius, linePoint, lineDirection, circleIntersectionA, circleIntersectionB)) {
				// Since the line hits our sphere we only need to check whether it also hits the triangle
				//TODO:
				glm::vec3 triangleIntersectionA;
				glm::vec3 triangleIntersectionB;
				bool intersectsTriangle = intersectPlanarLineTriangle(linePoint, lineDirection, triangle,
						triangleIntersectionA, triangleIntersectionB);



				if (intersectsTriangle) {
				    float distanceCA = computeDistanceOnLine(circleIntersectionA, linePoint, lineDirection);
				    float distanceCB = computeDistanceOnLine(circleIntersectionB, linePoint, lineDirection);
				    float distanceTA = computeDistanceOnLine(triangleIntersectionA, linePoint, lineDirection);
				    float distanceTB = computeDistanceOnLine(triangleIntersectionB, linePoint, lineDirection);

				    if (overlapSegments(distanceCA, distanceCB, distanceTA, distanceTB)) {
					// std::cout << "Exiting due to: Not Collinear | Overlapping!" << std::endl;
					return true;
				    }
				    else {
					// std::cout << "Exiting due to: Not Collinear | No overlap!" << std::endl;
					return false;
				    }
				} else {
					// std::cout << "Exiting due to: Not Collinear | No intersection with triangle!" << std::endl;
					return true;
				}

			} else {
				// Since the line does not even hit the sphere we can quit directly
				// std::cout << "linePoint: " << linePoint.x << ", " << linePoint.y << ", " << linePoint.z << std::endl;
				// std::cout << "lineDirection: " << lineDirection.x << ", " << lineDirection.y << ", " << lineDirection.z << std::endl;

				// std::cout << "Not Collinear | Exiting due to: Line doesn't hit circle!" << m_radius << std::endl;
				return false;
			}
		}

		 // std::cout << "Exiting due to: Nothing happened!" << std::endl;
		return false;
	}

	// Note that the values are not normalized (too expensive) and can only
	// be compared to other values from this method.
	// In effect we compute the ratio between the direction vector and the point difference vector.
	float inline computeDistanceOnLine(glm::vec3& distancePoint, glm::vec3& linePoint, glm::vec3& lineDirection) {
	   if (!floatEquals(lineDirection.x, 0.0f)) {
	       return (distancePoint.x - linePoint.x) / lineDirection.x;
	   } else if (!floatEquals(lineDirection.y, 0.0f)) {
	       return (distancePoint.y - linePoint.y) / lineDirection.y;
	   } else {
	       return (distancePoint.z - linePoint.z) / lineDirection.z;
	   }
	}

	// Compute max and min per 1d segment and check if they overlap
	bool inline overlapSegments(float& a1, float& a2, float& b1, float& b2) {
	  float maxA, minA, maxB, minB;
	  // No epsilon comparison required since we need to make a decision anyway
	  if (a1 < a2) {
	      minA = a1;
	      maxA = a2;
	  } else {
	      minA = a2;
	      maxA = a1;
	  }

	  if (b1 < b2) {
	      minB = b1;
	      maxB = b2;
	  } else {
	      minB = b2;
	      maxB = b1;
	  }

	  if (floatLess(maxB, minA) || floatLess(maxA, minB)) return false;
	  else return true;
	}

	// Intersect a line with a circle in a planar setup
	bool inline intersectPlanarLineCircle(glm::vec3& circleCenter, float circleRadius, glm::vec3& linePoint,
			glm::vec3& lineDirection, glm::vec3& intersectionA, glm::vec3& intersectionB) {
		glm::vec3 closestPoint = glm::closestPointOnLine(circleCenter, linePoint, linePoint + lineDirection);

		float dist = glm::distance(closestPoint, circleCenter);
		if (floatLess(dist, circleRadius)) {
		    // Now we compute the intersection points
		    // This is basically a pythagoras because the line is orthogonal to the center-closestPoint line
		    // and the closestPoint lies in the middle of intersectionA and intersectionB
		    glm::vec3 replacement = glm::normalize(lineDirection) * glm::sqrt(circleRadius * circleRadius - dist * dist);
		    intersectionA = closestPoint + replacement;
		    intersectionB = closestPoint - replacement;

		    return true;
		} else {
		    return false;
		}
	}

	// This method checks whether a (planar) line hits a triangle.
	// If so, the intersection points are stored in the parameters.
	bool inline intersectPlanarLineTriangle(glm::vec3& linePoint, glm::vec3& lineDirection, Triangle& triangle,
			glm::vec3& intersectionA, glm::vec3& intersectionB) {
		glm::vec3 a = linePoint;
		glm::vec3 b = a + lineDirection;

		glm::vec3 p1 = triangle.vertices[0];
		glm::vec3 p2 = triangle.vertices[1];
		glm::vec3 p3 = triangle.vertices[2];

		bool pSS12 = pointsOnSameSideOfLine(p1, p2, a, b);
		if (!pSS12) {
		  return false;
		}

		bool pSS23 = pointsOnSameSideOfLine(p2, p3, a, b);
		if (!pSS23) {
		  return false;
		}
		//Not required, because previous calls check that already
//		if (!pointsOnSameSideOfLine(p1, p3, a, b))
//			return false;

		// Note: We only get here if intersections occurred
		// The following code chooses the 2 intersection points that are valid
		if (pSS12) {
		    intersectionA = computeKnownPlanarLineLineIntersection(linePoint, lineDirection, p1, p2 - p1);
		} else if (pSS23) {
		    intersectionA = computeKnownPlanarLineLineIntersection(linePoint, lineDirection, p2, p3 - p2);
		}

		if (pSS23) {
		    intersectionB = computeKnownPlanarLineLineIntersection(linePoint, lineDirection, p2, p3 - p2);
		}  else {
		    intersectionB = computeKnownPlanarLineLineIntersection(linePoint, lineDirection, p1, p3 - p1);
		}

		return true;
	}

	// This method computes the one and only one intersection point of two lines when we know that it must exist
	glm::vec3 inline computeKnownPlanarLineLineIntersection(glm::vec3& linePointA, glm::vec3& lineDirectionA, glm::vec3& linePointB, glm::vec3 lineDirectionB) {
	  return glm::vec3((linePointB - linePointA) / (lineDirectionA - lineDirectionB));
	}

	void inline intersectPlanes(glm::vec3& t_normal, glm::vec3& t_vertex, glm::vec3& m_normal, glm::vec3& m_vertex,
			glm::vec3& linePoint, glm::vec3& lineDirection) {
		// This was solved using paper and pen by setting the planes to be equal

		// Since there are 6 different combinations we setup indices to avoid dividing by 0
		int indexNNotNull = !floatEquals(t_normal.x, 0.0f) ? 0 : !floatEquals(t_normal.y, 0.0f) ? 1 : 2;

		int indexNMDifferent = 0 != indexNNotNull && !floatEquals(t_normal.x - m_normal.x, 0.0f) ? 0 :
								1 != indexNNotNull && !floatEquals(t_normal.y - m_normal.y, 0.0f) ? 1 : 2;

		int indexOther = 0 != indexNMDifferent && 0 != indexNNotNull ? 0 :
							1 != indexNMDifferent && 1 != indexNNotNull ? 1 : 2;

		// Determine plane parameters for triangle plane (n1*x1 + n2*x2 + n3*x3 =  nd)
		float n1 = t_normal[indexNNotNull];
		float n2 = t_normal[indexNMDifferent];
		float n3 = t_normal[indexOther];
		float nd = n1 * t_vertex[indexNNotNull] + n2 * t_vertex[indexNMDifferent] + n3 * t_vertex[indexOther];

		// Determine plane parameters for circle plane (m1*x1 + m2*x2 + m3*x3 =  md)
		float m1 = m_normal[indexNNotNull];
		float m2 = m_normal[indexNMDifferent];
		float m3 = m_normal[indexOther];
		float md = m1 * m_vertex[indexNNotNull] + m2 * m_vertex[indexNMDifferent] + m3 * m_vertex[indexOther];

		// Some temporarily used values
		float p = (md - nd) / (m2 - n2);
		float v = (n3 - m3) / (m2 - n2);

		// This dimension was chosen as variable
		// Depends on nothing
		linePoint[indexOther] = 0.0f;
		lineDirection[indexOther] = 1.0f;

		// Insert values for the other dimensions
		// Depends on m2, n2
		linePoint[indexNMDifferent] = p;
		lineDirection[indexNMDifferent] = v;

		// Depends on n1, m2, n2
		linePoint[indexNNotNull] = (nd - n2 * p) / n1;
		lineDirection[indexNNotNull] = (-n2 * v - n3) / n1;
	}

	// Check whether 2 vectors are linear dependent
	bool inline linearDependent(glm::vec3& a, glm::vec3& b) {
	  // std::cout << a.x << ", " << a.y << ", " << a.z << std::endl;
	  // std::cout << b.x << ", " << b.y << ", " << b.z << std::endl;
		if (floatEquals(a.x, 0.0f) ^ floatEquals(b.x, 0.0f))
			return false;
		if (floatEquals(a.y, 0.0f) ^ floatEquals(b.y, 0.0f))
			return false;
		if (floatEquals(a.z, 0.0f) ^ floatEquals(b.z, 0.0f))
			return false;

		bool ignoreX = floatEquals(b.x, 0.0f);
		bool ignoreY = floatEquals(b.y, 0.0f);
		bool ignoreZ = floatEquals(b.z, 0.0f);

		float ratioX = a.x / b.x;
		float ratioY = a.y / b.y;
		float ratioZ = a.z / b.z;

		float equalsXY = floatEquals(ratioX, ratioY);
		float equalsYZ = floatEquals(ratioY, ratioZ);
		float equalsXZ = floatEquals(ratioX, ratioZ);

		return (ignoreX && ignoreY)
		    || (ignoreY && ignoreZ)
		    || (ignoreX && ignoreZ)
		    || (equalsYZ && ignoreX)
		    || (equalsXZ && ignoreY)
		    || (equalsXY && ignoreZ)
		    || (equalsXY && equalsXZ);
	}

	// Check whether two floats are equal plus minus a tolerance value
	bool inline floatEquals(float a, float b) {
		const float epsilon = 0.0000000001f;
		return (a > b - epsilon) && (a < b + epsilon);
	}

	// Check whether a vector has only zeros
	bool inline isNullVector(glm::vec3& vector) {
		if (floatEquals(vector.x, 0.0f) && floatEquals(vector.y, 0.0f) && floatEquals(vector.z, 0.0f)) {
			// std::cout << vector.x << ", " << vector.y << ", " << vector.z << std::endl;
			return true;
		} else {
			return false;
		}
	}

	// Check whether float a is less than float b
	// A tolerance is added that makes overlapping more likely
	bool inline floatLess(float a, float b) {
		const float epsilon = 0.000001f;
		return a < b + epsilon;
	}

	// Check whether a given point lies inside a triangle, assuming that they lie already in one plane
	bool inline pointInTriangle(glm::vec3& p, Triangle& triangle) {
		glm::vec3 a = triangle.vertices[0];
		glm::vec3 b = triangle.vertices[1];
		glm::vec3 c = triangle.vertices[2];

		if (pointsOnSameSideOfLine(p, a, b, c) && pointsOnSameSideOfLine(p, b, a, c)
				&& pointsOnSameSideOfLine(p, c, a, b)) {
			return true;
		} else {
			return false;
		}
	}

	// Check whether 2 points p1 and p2 are on the same side of the line between a and b
	bool inline pointsOnSameSideOfLine(glm::vec3& p1, glm::vec3& p2, glm::vec3& a, glm::vec3& b) {
		glm::vec3 cp1 = glm::cross(b - a, p1 - a);
		glm::vec3 cp2 = glm::cross(b - a, p2 - a);
		if (glm::dot(cp1, cp2) >= 0) {
			return true;
		} else {
			return false;
		}
	}
};

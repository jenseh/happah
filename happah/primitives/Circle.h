#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <cmath>
#include <algorithm>
#include <list>

#include "Triangle.h"
#include "../kdtree/BBox.h"
#include "../kdtree/BSphere.h"
#include "../../HappahTypes.h"

struct CirclePoint {
  hpreal angle;
  hpreal radius;

  CirclePoint(hpreal angle_, hpreal radius_) {
    angle = angle_;
    radius = radius_;
  }
};

struct CircleRange {
  hpreal startAngle;
  hpreal endAngle;
  hpreal radius;

  CircleRange(hpreal startAngle_, hpreal endAngle_, hpreal radius_) {
    startAngle = startAngle_;
    endAngle = endAngle_;
    radius = radius_;
  }
};

struct CircleHitResult {
  glm::vec3 hitPointA;
  glm::vec3 hitPointB;
  Triangle* object;

  CircleHitResult(glm::vec3 hitPointA_, glm::vec3 hitPointB_, Triangle* object_) : hitPointA(hitPointA_), hitPointB(hitPointB_), object(object_) {
  }
};

struct Circle {
	glm::vec3 m_center;
	glm::vec3 m_normal; //normalized
	float m_radius;

	Circle(glm::vec3 center, glm::vec3 normal, float radius) :
			m_center(center), m_normal(normal), m_radius(radius) {
	}


	// This method checks whether a (filled) triangle intersects a (filled) circle.
	// Assumptions:
	// - normal is normalized
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
	bool intersect(Triangle* triangle, std::list<CircleHitResult*>* hitResults) {
		glm::vec3 t_normal = glm::cross(triangle->vertices[1] - triangle->vertices[0],
						triangle->vertices[2] - triangle->vertices[0]);

//                // // std::cout << "radius: " << m_radius << std::endl;
//                // // std::cout << "circle: " << m_center.x << ", " << m_center.y << ", " << m_center.z << std::endl;




		// Start with a plane-plane intersection

		// Sanity check: If a normal vector is all 0, then abort
		bool nullNormal = isNullVector(t_normal) || isNullVector(m_normal);
		if (nullNormal) {
		    std::cerr << "Error: One of the geometry's normals is a null vector!" << std::endl;
		      std::cout << "EtriangleA: " << triangle->vertices[0].x << ", " << triangle->vertices[0].y << ", " << triangle->vertices[0].z << std::endl;
		      std::cout << "EtriangleB: " << triangle->vertices[1].x << ", " << triangle->vertices[1].y << ", " << triangle->vertices[1].z << std::endl;
		      std::cout << "EtriangleC: " << triangle->vertices[2].x << ", " << triangle->vertices[2].y << ", " << triangle->vertices[2].z << std::endl;
		      std::cout << t_normal.x << ", " << t_normal.y << ", " << t_normal.z << std::endl;
		      std::cout << m_normal.x << ", " << m_normal.y << ", " << m_normal.z << std::endl;
		    exit(1);
		  }
		 // // std::cout << "t_normal: " << t_normal.x << ", " << t_normal.y << ", " << t_normal.z << std::endl;
		// // std::cout << "m_normal: " << m_normal.x << ", " << m_normal.y << ", " << m_normal.z << std::endl;

		//1: Check collinearity of normal vectors
		bool collinear = linearDependent(m_normal, t_normal);
		// // std::cout << "Info: Collinear: " << collinear << std::endl;

		if (collinear) {
			std::cout << "Debug-Info: The very unlikely case of collinear Triangle-Circle intersection just happened!" << std::endl;
		
			//2: Check whether planes are identical or parallel
			bool identical = floatEquals(glm::dot(m_center - triangle->vertices[2], t_normal), 0.0f);
			// // std::cout << "Info: Identical: " << identical << std::endl;

			//2a: If planes are parallel, return false
			if (!identical) {
				// // std::cout << "Error: Collinear | Planes are parallel!" << std::endl;
				return false;
			}

			//2b: If planes are identical, compute planar intersection of triangle and circle
			else {
				// Compute the closest points on triangle sides to the circle center
				glm::vec3 closestPoint01 = glm::closestPointOnLine(m_center, triangle->vertices[0], triangle->vertices[1]);
				glm::vec3 closestPoint12 = glm::closestPointOnLine(m_center, triangle->vertices[1], triangle->vertices[2]);
				glm::vec3 closestPoint02 = glm::closestPointOnLine(m_center, triangle->vertices[0], triangle->vertices[2]);

				// Compute the respective distances
				float distC01 = glm::distance(m_center, closestPoint01);
				float distC12 = glm::distance(m_center, closestPoint12);
				float distC02 = glm::distance(m_center, closestPoint02);

				// Check whether any distance is shorter than the radius
				bool triangleInside = floatSmaller(distC01, m_radius) || floatSmaller(distC12, m_radius) || floatSmaller(distC02, m_radius);
				// // std::cout << "Info: triangleInside: " << triangleInside << std::endl;

				if (triangleInside) {
					// ..then the triangle is "inside" the circle
				    // // std::cout << distC01 << ", " << distC12 << ", " << distC02 << ", " << m_radius << std::endl;
				    // // std::cout << "Success: Collinear | Triangle inside circle!" << std::endl;

				    // Get point on triangle (edge) that is closest to center
				    glm::vec3* hitPoint;

				    if (distC01 < distC12 && distC01 < distC02) {
					hitPoint = &closestPoint01;
				    } else if (distC12 < distC01 && distC12 < distC02) {
					hitPoint = &closestPoint12;
				    } else {
					hitPoint = &closestPoint02;
				    }

				    CircleHitResult* tempHitResult = new CircleHitResult(*hitPoint, *hitPoint, triangle);
				    hitResults->push_back(tempHitResult);
				    return true;
				} else {
					// Now there is either no intersection or the circle is inside the triangle
					if (pointInTriangle(m_center, triangle)) {
						// // std::cout << "Success: Collinear | Circle inside triangle!" << std::endl;
						CircleHitResult* tempHitResult = new CircleHitResult(m_center, m_center, triangle);
						hitResults->push_back(tempHitResult);
						return true;
					} else {
						// // std::cout << "Error: Collinear | Circle not inside triangle!" << std::endl;
						return false;
					}
				}
			}
		} else {
			// std::cout << "FtriangleA: " << triangle->vertices[0].x << ", " << triangle->vertices[0].y << ", " << triangle->vertices[0].z << std::endl;
			// std::cout << "FtriangleB: " << triangle->vertices[1].x << ", " << triangle->vertices[1].y << ", " << triangle->vertices[1].z << std::endl;
			// std::cout << "FtriangleC: " << triangle->vertices[2].x << ", " << triangle->vertices[2].y << ", " << triangle->vertices[2].z << std::endl;

			// std::cout << "CCenter: " << m_center.x << ", " << m_center.y << ", " << m_center.z << std::endl;
			// std::cout << "CNormal: " << m_normal.x << ", " << m_normal.y << ", " << m_normal.z << std::endl;

			//2: Planes must collide in a common line
			glm::vec3 linePoint;
			glm::vec3 lineDirection;
			intersectPlanes(t_normal, triangle->vertices[0], m_normal, m_center, linePoint, lineDirection);

			// Normalize lineDirection for distance comparisons
			lineDirection = glm::normalize(lineDirection);

			    // std::cout << "Intersect linePoint: " << linePoint.x << ", " << linePoint.y << ", " << linePoint.z << std::endl;
			    // std::cout << "Intersect lineDir: " << lineDirection.x << ", " << lineDirection.y << ", " << lineDirection.z << std::endl;

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

                                   // // std::cout << "Intersect triangleA: " << triangleIntersectionA.x << ", " << triangleIntersectionA.y << ", " << triangleIntersectionA.z << std::endl;
                                   // // std::cout << "Intersect triangleB: " << triangleIntersectionB.x << ", " << triangleIntersectionB.y << ", " << triangleIntersectionB.z << std::endl;

				if (intersectsTriangle) {


				     // // std::cout << "Intersect circleA: " << circleIntersectionA.x << ", " << circleIntersectionA.y << ", " << circleIntersectionA.z << std::endl;
				     // // std::cout << "Intersect circleB: " << circleIntersectionB.x << ", " << circleIntersectionB.y << ", " << circleIntersectionB.z << std::endl;





				    float distanceCA = computeDistanceOnLine(circleIntersectionA, linePoint, lineDirection);
				    float distanceCB = computeDistanceOnLine(circleIntersectionB, linePoint, lineDirection);
				    float distanceTA = computeDistanceOnLine(triangleIntersectionA, linePoint, lineDirection);
				    float distanceTB = computeDistanceOnLine(triangleIntersectionB, linePoint, lineDirection);

				    glm::vec3* minC;
				    glm::vec3* maxC;
				    glm::vec3* minT;
				    glm::vec3* maxT;

				    float* minCv;
				    float* maxCv;
				    float* minTv;
				    float* maxTv;

				    if (distanceCA < distanceCB) {
					minCv = &distanceCA;
					maxCv = &distanceCB;
					minC = &circleIntersectionA;
					maxC = &circleIntersectionB;
				    } else {
					minCv = &distanceCB;
					maxCv = &distanceCA;
					minC = &circleIntersectionB;
					maxC = &circleIntersectionA;
				    }

				    if (distanceTA < distanceTB) {
					minTv = &distanceTA;
					maxTv = &distanceTB;
					minT = &triangleIntersectionA;
					maxT = &triangleIntersectionB;
				    } else {
					minTv = &distanceTB;
					maxTv = &distanceTA;
					minT = &triangleIntersectionB;
					maxT = &triangleIntersectionA;
				    }


				    // Check whether the segments on the line overlap
				    if ((floatBigger(*maxTv, *minCv) && floatBigger(*maxCv, *minTv))) {
					// // std::cout << "Success: Overlapping!" << std::endl;

					// Compute the 2 "inner" points along line
					glm::vec3* minVec;
					glm::vec3* maxVec;

					if (*minTv < *minCv) {
					    minVec = minC;
					} else {
					    minVec = minT;
					}

					if (*maxTv < *maxCv) {
					    maxVec = maxT;
					} else {
					    maxVec = maxC;
					}


					glm::vec3 closestPointToCenter = glm::closestPointOnLine(m_center, *minVec, *maxVec);

					// In case min and max are equal, we would get tripple NAN
					if (!isValidVector(closestPointToCenter)) closestPointToCenter = *minVec;

					CircleHitResult* tempHitResult = new CircleHitResult(*minVec, *maxVec, triangle);
					hitResults->push_back(tempHitResult);
//					// // std::cout << "minVec: " << minVec->x << ", " << minVec->y << ", " << minVec->z << std::endl;
//					// // std::cout << "maxVec: " << maxVec->x << ", " << maxVec->y << ", " << maxVec->z << std::endl;
//					// // std::cout << "Intersect center: " << m_center.x << ", " << m_center.y << ", " << m_center.z << std::endl;
//					// // std::cout << "Intersect inside: " << closestPointToCenter.x << ", " << closestPointToCenter.y << ", " << closestPointToCenter.z << std::endl;

//					CircleHitResult* hitResult = hitResults->back();
//					// // std::cout << "Intersect outside1B: size " << hitResults->size() << std::endl;
//					// // std::cout << "Intersect outside1B: " << (hitResult != 0) << std::endl;
//					// // std::cout << "Intersect outside2B: " << hitResult->range.startAngle << ", " << hitResult->range.endAngle << ", " << hitResult->range.radius << std::endl;
					return true;
				    }
				    else {
					    // std::cout << *maxTv << ", " << *minCv << ", " << *maxCv << ", " << *minTv << std::endl;
					    // std::cout << "Error: No overlap!" << std::endl;
					return false;
				    }
				} else {
					    // std::cout << "Error: No intersection with triangle!" << std::endl;
					return false;
				}

			} else {
				// Since the line does not even hit the sphere we can quit directly
				// // std::cout << "linePoint: " << linePoint.x << ", " << linePoint.y << ", " << linePoint.z << std::endl;
				// // std::cout << "lineDirection: " << lineDirection.x << ", " << lineDirection.y << ", " << lineDirection.z << std::endl;

				    // std::cout << "Error: Exiting due to: Line doesn't hit circle!" << m_radius << std::endl;
				return false;
			}
		}

		   // // std::cout << "Error: Nothing happened!" << std::endl;
		return false;
	}

	// Note that the values are not normalized (too expensive) and can only
	// be compared to other values from this method.
	// In effect we compute the ratio between the direction vector and the point difference vector.
	float inline computeDistanceOnLine(glm::vec3& distancePoint, glm::vec3& linePoint, glm::vec3& lineDirection) {
//	   glm::vec3 difference = distancePoint - linePoint;
//	   return glm::length(difference);

	   if (!floatEquals(lineDirection.x, 0.0f)) {
	       return (distancePoint.x - linePoint.x) / lineDirection.x;
	   } else if (!floatEquals(lineDirection.y, 0.0f)) {
	       return (distancePoint.y - linePoint.y) / lineDirection.y;
	   } else {
	      return (distancePoint.z - linePoint.z) / lineDirection.z; //TODO: Only works if there is a z component
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

	  if (floatSmaller(maxB, minA) || floatSmaller(maxA, minB)) return false;
	  else return true;
	}

	// Intersect a line with a circle in a planar setup
	bool inline intersectPlanarLineCircle(glm::vec3& circleCenter, float circleRadius, glm::vec3& linePoint,
			glm::vec3& lineDirection, glm::vec3& intersectionA, glm::vec3& intersectionB) {
		//TODO: fix this by implementing a function for real lines (not segments)
		glm::vec3 closestPoint = glm::closestPointOnLine(circleCenter, linePoint - lineDirection * 1000.0f, linePoint + lineDirection * 1000.0f);


		// // std::cout << "closestPoint: " << closestPoint.x << ", " << closestPoint.y << ", " << closestPoint.z << std::endl;

		float dist = glm::distance(closestPoint, circleCenter);
		if (floatSmaller(dist, circleRadius)) {
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
	// Note that the planes are not necessarily axis aligned.
	bool inline intersectPlanarLineTriangle(glm::vec3& linePoint, glm::vec3& lineDirection, Triangle* triangle,
			glm::vec3& intersectionA, glm::vec3& intersectionB) {
		glm::vec3 a = linePoint;
		glm::vec3 b = a + lineDirection;

		glm::vec3 p0 = triangle->vertices[0];
		glm::vec3 p1 = triangle->vertices[1];
		glm::vec3 p2 = triangle->vertices[2];

		bool pSS01 = pointsOnSameSideOfLineNonTolerant(p0, p1, a, b);
		bool pSS12 = pointsOnSameSideOfLineNonTolerant(p1, p2, a, b);
		bool pSS02 = pointsOnSameSideOfLineNonTolerant(p0, p2, a, b);

		int pSSCount = 0;
		if (pSS01) pSSCount++;
		if (pSS12) pSSCount++;
		if (pSS02) pSSCount++;

		 // std::cout << "pSSCount: " << pSSCount << std::endl;

		if (pSSCount == 3) {
		    return false;
		}


		if (!pSS01) {
		    intersectionA = computeKnownPlanarLineLineIntersection(linePoint, lineDirection, p0, p1 - p0);
		    intersectionB = computeKnownPlanarLineLineIntersection(linePoint, lineDirection, p0, p2 - p0);
		  } else if (!pSS12) {
		    intersectionA = computeKnownPlanarLineLineIntersection(linePoint, lineDirection, p1, p0 - p1);
		    intersectionB = computeKnownPlanarLineLineIntersection(linePoint, lineDirection, p1, p2 - p1);
		  } else if (!pSS02) {
		    intersectionA = computeKnownPlanarLineLineIntersection(linePoint, lineDirection, p2, p0 - p2);
		    intersectionB = computeKnownPlanarLineLineIntersection(linePoint, lineDirection, p2, p1 - p2);
		  }

		  return true;
	}

	// This method computes the one and only one intersection point in XY plane (or parallel) of two lines when we know that it must exist
	glm::vec3 inline computeKnownPlanarLineLineIntersection(glm::vec3& linePointA, glm::vec3& lineDirectionA, glm::vec3& linePointB, glm::vec3 lineDirectionB) {
		float t = (linePointA.z - linePointB.z) / lineDirectionB.z;
		return linePointB + t * lineDirectionB;
	}

	void inline intersectPlanes(glm::vec3& t_normal, glm::vec3& t_vertex, glm::vec3& m_normal, glm::vec3& m_vertex,
			glm::vec3& linePoint, glm::vec3& lineDirection) {
		// This was solved using paper and pen by setting the planes to be equal

		// Since there are 6 different combinations we setup indices to avoid dividing by 0
		int indexNNotNull = !floatEquals(t_normal.x, 0.0f) ? 0 : 1;

		int indexOther = 0 != indexNNotNull ? 0 : 1;


		// Determine plane parameters for triangle plane (n0*x0 + n1*x1 + n2*x2 =  nd)
		float n0 = t_normal[indexNNotNull];
		float n1 = t_normal[indexOther];
		float n2 = t_normal[2];
		float nd = n0 * t_vertex[indexNNotNull] + n1 * t_vertex[indexOther] + n2 * t_vertex[2];

		// Determine plane parameters for circle plane (m0*x0 + m1*x1 + m2*x2 =  md)
		float m0 = m_normal[indexNNotNull];
		float m1 = m_normal[indexOther];
		float m2 = m_normal[2];
		float md = m0 * m_vertex[indexNNotNull] + m1 * m_vertex[indexOther] + m2 * m_vertex[2];

		// Some temporarily used values
		float t = nd - n2 * md;

		// This dimension was chosen as variable
		// Depends on nothing
		linePoint[2] = m_vertex[2]; // Simplification for XY planes
		lineDirection[2] = 0.0f;

		// Insert values for the other dimensions
		// Depends on n1, n2
		linePoint[indexOther] = 0.0f;
		lineDirection[indexOther] = 1.0f;

		// Depends on n1, n2
		linePoint[indexNNotNull] = t / n0;
		lineDirection[indexNNotNull] = -n1 / n0;
	}

	// Check whether 2 vectors are linear dependent
	bool inline linearDependent(glm::vec3& a, glm::vec3& b) {
	  // // std::cout << a.x << ", " << a.y << ", " << a.z << std::endl;
	  // // std::cout << b.x << ", " << b.y << ", " << b.z << std::endl;
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
		const float epsilon = 10e-07f;
		return (a > b - epsilon) && (a < b + epsilon);
	}

	// Check whether two floats are equal plus minus a tolerance value
	bool inline floatEquals(float a, float b, float epsilon) {
		return (a > b - epsilon) && (a < b + epsilon);
	}

	// Check whether a vector has only zeros
	// This requires a very small epsilon (i.e. 10-e7) to avoid misinterpretation of small normals
	bool inline isNullVector(glm::vec3& vector) {
	  float epsilon = 10e-10f;
		if (floatEquals(vector.x, 0.0f, epsilon) && floatEquals(vector.y, 0.0f, epsilon) && floatEquals(vector.z, 0.0f, epsilon)) {
			// // std::cout << vector.x << ", " << vector.y << ", " << vector.z << std::endl;
			return true;
		} else {
			return false;
		}
	}

	// Check whether a vector has only valid entries
	bool inline isValidVector(glm::vec3& vector) {
		if (std::isinf(vector.x) || std::isnan(vector.x)) {
		    return false;
		}
		if (std::isinf(vector.y) || std::isnan(vector.y)) {
		    return false;
		}
		if (std::isinf(vector.z) || std::isnan(vector.z)) {
		    return false;
		}

		return true;
	}

	// Check whether float a is smaller than float b
	// A tolerance is added that makes overlapping more likely
	bool inline floatSmaller(float a, float b) {
		const float epsilon = 10e-04f;
		return a < b + epsilon;
	}

	// Check whether float a is bigger than float b
	// A tolerance is added that makes overlapping more likely
	bool inline floatBigger(float a, float b) {
		const float epsilon = 10e-04f;
		return a > b - epsilon;
	}

	// Check whether a given point lies inside a triangle, assuming that they lie already in one plane
	bool inline pointInTriangle(glm::vec3& p, Triangle* triangle) {
		glm::vec3 a = triangle->vertices[0];
		glm::vec3 b = triangle->vertices[1];
		glm::vec3 c = triangle->vertices[2];

		if (pointsOnSameSideOfLineTolerant(p, a, b, c) && pointsOnSameSideOfLineTolerant(p, b, a, c)
				&& pointsOnSameSideOfLineTolerant(p, c, a, b)) {
			return true;
		} else {
			return false;
		}
	}

	// Check whether 2 points p1 and p2 are on the same side of the line between a and b
	// If p1 or p2 is on the line, it counts as not being on the same side
	bool inline pointsOnSameSideOfLineTolerant(glm::vec3& p1, glm::vec3& p2, glm::vec3& a, glm::vec3& b) {
		glm::vec3 cp1 = glm::cross(b - a, p1 - a);
		glm::vec3 cp2 = glm::cross(b - a, p2 - a);
		 // // std::cout << cp1.x << ", " << cp1.y << ", " << cp1.z << std::endl;
		 // // std::cout << cp2.x << ", " << cp2.y << ", " << cp2.z << std::endl;

		float dotProduct = glm::dot(cp1, cp2);

		if (floatBigger(dotProduct, 0.0f)) {
			return true;
		} else {
			return false;
		}
	}

	// Check whether 2 points p1 and p2 are on the same side of the line between a and b
	// If p1 or p2 is on the line, it counts as being on the same side
	bool inline pointsOnSameSideOfLineNonTolerant(glm::vec3& p1, glm::vec3& p2, glm::vec3& a, glm::vec3& b) {
		glm::vec3 cp1 = glm::cross(b - a, p1 - a);
		glm::vec3 cp2 = glm::cross(b - a, p2 - a);


		float dotProduct = glm::dot(cp1, cp2);

		// std::cout << "CP1: " <<cp1.x << ", " << cp1.y << ", " << cp1.z << std::endl;
		// std::cout << "CP2: " <<cp2.x << ", " << cp2.y << ", " << cp2.z << std::endl;
		// std::cout << "Dot Product: " << dotProduct << std::endl;

		if (floatEquals(dotProduct, 0.0f, 10e-4f)) {
		    return false;
		} else if (dotProduct > 0.0f) {
			return true;
		} else {
			return false;
		}
	}


	// Required for kd-Tree
	BSphere computeBoundingSphere() {
	  return BSphere(m_center, m_radius);
	}
	// Note that the conversion here regards the circle as a sphere.
	// Further optimization might be possible for circles.
	BBox computeBoundingBox() {
	  glm::vec3 radiusV = glm::vec3(m_radius, m_radius, m_radius);
	  glm::vec3 min = m_center - radiusV;
	  glm::vec3 max = m_center + radiusV;
	  return BBox(min, max);
	}
};

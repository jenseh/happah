#pragma once

#include <algorithm>
#include <cmath>
#include <glm/glm.hpp>
#include <iostream>
#include <list>

#include "happah/HappahTypes.h"
#include "happah/kdtree/BBox.h"
#include "happah/math/Triangle.h"

//#include "happah/LoggingUtils.h"

struct CircleHitResult {
  hpvec3 hitPointA;
  hpvec3 hitPointB;

  CircleHitResult(hpvec3 hitPointA_, hpvec3 hitPointB_) : hitPointA(hitPointA_), hitPointB(hitPointB_) {
  }
};

struct Circle {
	hpvec3 m_center;
	hpvec3 m_normal; //normalized
	hpreal m_radius;

	Circle(hpvec3 center, hpvec3 normal, hpreal radius) :
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
	bool intersect(Triangle& triangle, std::list<CircleHitResult>* hitResults) {
		hpvec3 t_normal = glm::normalize(triangle.computeNormal());

		// Start with a plane-plane intersection

		// Sanity check: If a normal vector is all 0, then abort
		bool nullNormal = isNullVector(t_normal) || isNullVector(m_normal);
		if (nullNormal) {
		    std::cerr << "Error: One of the geometry's normals is a null vector!" << std::endl;
		    return false;
		}

		//1: Check collinearity of normal vectors
		bool collinear = linearDependent(m_normal, t_normal);
		// // std::cout << "Info: Collinear: " << collinear << std::endl;

		if (collinear) {
			// // std::cout << "Debug-Info: The very unlikely case of collinear Triangle-Circle intersection just happened!" << std::endl;
		
			//2: Check whether planes are identical or parallel
			bool identical = floatEquals(glm::dot(m_center - triangle.vertices[2], t_normal), 0.0);
			// // std::cout << "Info: Identical: " << identical << std::endl;

			//2a: If planes are parallel, return false
			if (!identical) {
				// // std::cout << "Error: Collinear | Planes are parallel!" << std::endl;
				return false;
			} else {
				//2b: If planes are identical, compute planar intersection of triangle and circle

				// Compute the closest points on triangle sides to the circle center
				hpvec3 closestPoint01 = glm::closestPointOnLine(m_center, triangle.vertices[0], triangle.vertices[1]);
				hpvec3 closestPoint12 = glm::closestPointOnLine(m_center, triangle.vertices[1], triangle.vertices[2]);
				hpvec3 closestPoint02 = glm::closestPointOnLine(m_center, triangle.vertices[0], triangle.vertices[2]);

				// Compute the respective distances
				hpreal distC01 = glm::distance(m_center, closestPoint01);
				hpreal distC12 = glm::distance(m_center, closestPoint12);
				hpreal distC02 = glm::distance(m_center, closestPoint02);

				// Check whether any distance is shorter than the radius
				bool triangleInside = floatSmaller(distC01, m_radius) || floatSmaller(distC12, m_radius) || floatSmaller(distC02, m_radius);
				// // std::cout << "Info: triangleInside: " << triangleInside << std::endl;

				if (triangleInside) {
					// ..then the triangle is "inside" the circle
				    // // std::cout << distC01 << ", " << distC12 << ", " << distC02 << ", " << m_radius << std::endl;

				    // Get point on triangle (edge) that is closest to center
				    hpvec3* hitPoint;

				    if (distC01 < distC12 && distC01 < distC02) {
				    	hitPoint = &closestPoint01;
				    } else if (distC12 < distC01 && distC12 < distC02) {
				    	hitPoint = &closestPoint12;
				    } else {
				    	hitPoint = &closestPoint02;
				    }

				    CircleHitResult tempHitResult = CircleHitResult(*hitPoint, *hitPoint);
				    hitResults->push_back(tempHitResult);

				    // // std::cout << "Success: Collinear | Triangle inside circle!" << std::endl;
				    return true;
				} else {
					// Now there is either no intersection or the circle is inside the triangle
					if (pointInTriangle(m_center, triangle)) {
						CircleHitResult tempHitResult = CircleHitResult(m_center, m_center);
						hitResults->push_back(tempHitResult);

						// // std::cout << "Success: Collinear | Circle inside triangle!" << std::endl;
						return true;
					} else {
						// // std::cout << "Error: Collinear | Circle not inside triangle!" << std::endl;
						return false;
					}
				}
			}
		} else {
			//2: Planes must collide in a common line
			hpvec3 linePoint;
			hpvec3 lineDirection;
			intersectPlanes(t_normal, triangle.vertices[0], m_normal, m_center, linePoint, lineDirection);

			// Normalize lineDirection for distance comparisons
			lineDirection = glm::normalize(lineDirection);

			 // std::cout << "Intersect linePoint: " << linePoint.x << ", " << linePoint.y << ", " << linePoint.z << std::endl;
			 // std::cout << "Intersect lineDir: " << lineDirection.x << ", " << lineDirection.y << ", " << lineDirection.z << std::endl;

			// Check whether this line hits our sphere
			// Check whether distance is shorter than the radius
			hpvec3 circleIntersectionA;
			hpvec3 circleIntersectionB;
			if (intersectPlanarLineCircle(linePoint, lineDirection, circleIntersectionA, circleIntersectionB)) {
				// Since the line hits our sphere we only need to check whether it also hits the triangle
				hpvec3 triangleIntersectionA;
				hpvec3 triangleIntersectionB;
				bool intersectsTriangle = intersectPlanarLineTriangle(linePoint, lineDirection, triangle, triangleIntersectionA, triangleIntersectionB);

				 // std::cout << "Intersect triangleA: " << triangleIntersectionA.x << ", " << triangleIntersectionA.y << ", " << triangleIntersectionA.z << std::endl;
				 // std::cout << "Intersect triangleB: " << triangleIntersectionB.x << ", " << triangleIntersectionB.y << ", " << triangleIntersectionB.z << std::endl;

				if (intersectsTriangle) {
					 // std::cout << "Intersect circleA: " << circleIntersectionA.x << ", " << circleIntersectionA.y << ", " << circleIntersectionA.z << std::endl;
					 // std::cout << "Intersect circleB: " << circleIntersectionB.x << ", " << circleIntersectionB.y << ", " << circleIntersectionB.z << std::endl;

					hpreal distanceCA = computeDistanceOnLine(circleIntersectionA, linePoint, lineDirection);
					hpreal distanceCB = computeDistanceOnLine(circleIntersectionB, linePoint, lineDirection);
				    hpreal distanceTA = computeDistanceOnLine(triangleIntersectionA, linePoint, lineDirection);
				    hpreal distanceTB = computeDistanceOnLine(triangleIntersectionB, linePoint, lineDirection);

				    hpvec3* minC;
				    hpvec3* maxC;
				    hpvec3* minT;
					hpvec3* maxT;

					hpreal* minCv;
					hpreal* maxCv;
					hpreal* minTv;
					hpreal* maxTv;

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
					// We need a very low accuracy here due to the other dimensions
					if (overlapSegments(*minTv, *maxTv, *minCv, *maxCv)) {
						// // std::cout << "Success: Overlapping!" << std::endl;

						// Compute the 2 "inner" points along line
						hpvec3* minVec;
						hpvec3* maxVec;

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

						// // std::cout << *maxTv << ", " << *minCv << ", " << *maxCv << ", " << *minTv << std::endl;
						CircleHitResult tempHitResult = CircleHitResult(*minVec, *maxVec);
						hitResults->push_back(tempHitResult);
						return true;
					} else {
						// // std::cout << *maxTv << ", " << *minCv << ", " << *maxCv << ", " << *minTv << std::endl;
						// // std::cout << "Error: No overlap!" << std::endl;
						return false;
					}
				} else {
					// // std::cout << "Error: No intersection with triangle!" << std::endl;
					return false;
				}
			} else {
				// // std::cout << "Error: Exiting due to: Line doesn't hit circle!" << std::endl;
				return false;
			}
		}

		// // std::cout << "Error: Nothing happened!" << std::endl;
		return false;
	}

	// Note that the values are not normalized (too expensive) and can only
	// be compared to other values from this method.
	// In effect we compute the ratio between the direction vector and the point difference vector.
	hpreal computeDistanceOnLine(hpvec3& distancePoint, hpvec3& linePoint, hpvec3& lineDirection) {
//	   hpvec3 difference = distancePoint - linePoint;
//	   return glm::length(difference);

		if (!floatEquals(lineDirection.x, 0.0)) {
			return (distancePoint.x - linePoint.x) / lineDirection.x;
		} else if (!floatEquals(lineDirection.y, 0.0)) {
			return (distancePoint.y - linePoint.y) / lineDirection.y;
		} else {
			return (distancePoint.z - linePoint.z) / lineDirection.z;
		}
	}

	// Compute max and min per 1d segment and check if they overlap
	bool overlapSegments(hpreal& a1, hpreal& a2, hpreal& b1, hpreal& b2) {
	  hpreal maxA, minA, maxB, minB;
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
	bool intersectPlanarLineCircle(hpvec3& linePoint,
			hpvec3& lineDirection, hpvec3& intersectionA, hpvec3& intersectionB) {
		hpvec3 centerToLineDir = glm::normalize(glm::cross(lineDirection, m_normal));
		// std::cout << "centerToLineDir: " << centerToLineDir.x << ", " << centerToLineDir.y << ", " << centerToLineDir.z << std::endl;
		hpvec3 closestPointToCenter = computeClosestLineLineIntersection(linePoint, m_center, lineDirection, centerToLineDir);
		hpreal dist = glm::distance(closestPointToCenter, m_center);

		// std::cout << "closestPointToCenter: " << closestPointToCenter.x << ", " << closestPointToCenter.y << ", " << closestPointToCenter.z << std::endl;
		// std::cout << "dist: " << dist << ", radius: " << m_radius << std::endl;

		if (floatSmaller(dist, m_radius)) {
			// Now we compute the intersection points
			// This is basically a pythagoras because the line is orthogonal to the center-closestPoint line
			// and the closestPoint lies in the middle of intersectionA and intersectionB
			hpvec3 replacement = lineDirection * glm::sqrt(m_radius * m_radius - dist * dist);
			intersectionA = closestPointToCenter + replacement;
			intersectionB = closestPointToCenter - replacement;

			return true;
		} else {
			return false;
		}
	}

	bool computeClosestLineSegmentIntersection(hpvec3& linePoint, hpvec3& lineDirection, hpvec3& segmentPointA, hpvec3& segmentPointB, hpvec3& closestIntersection) {
		closestIntersection = computeClosestLineLineIntersection(linePoint, segmentPointA, lineDirection, segmentPointB - segmentPointA);

		hpreal segmentPointADistance = computeDistanceOnLine(segmentPointA, linePoint, lineDirection);
		hpreal segmentPointBDistance = computeDistanceOnLine(segmentPointB, linePoint, lineDirection);

		hpreal intersectionDistance = computeDistanceOnLine(closestIntersection, linePoint, lineDirection);

		if ( (floatBigger(intersectionDistance, segmentPointBDistance) && floatSmaller(intersectionDistance, segmentPointADistance))
				|| (floatBigger(intersectionDistance, segmentPointADistance) && floatSmaller(intersectionDistance, segmentPointBDistance)) ) {
			return true;
		} else {
			return false;
		}
	}

	// This method checks whether a (planar) line hits a triangle.
	// If so, the intersection points are stored in the parameters.
	// Note that the planes are not necessarily axis aligned.
	bool intersectPlanarLineTriangle(hpvec3& linePoint, hpvec3& lineDirection, Triangle& triangle,
			hpvec3& intersectionA, hpvec3& intersectionB) {
		hpvec3 p0 = triangle.vertices[0];
		hpvec3 p1 = triangle.vertices[1];
		hpvec3 p2 = triangle.vertices[2];

		hpvec3 closestIntersection01;
		hpvec3 closestIntersection02;
		hpvec3 closestIntersection12;

		bool intersects01 = computeClosestLineSegmentIntersection(linePoint, lineDirection, p0, p1, closestIntersection01); //TODO: check the distance to line
		bool intersects02 = computeClosestLineSegmentIntersection(linePoint, lineDirection, p0, p2, closestIntersection02);
		bool intersects12 = computeClosestLineSegmentIntersection(linePoint, lineDirection, p1, p2, closestIntersection12);


		// std::cout << "closestIntersection01: " << closestIntersection01.x << ", " << closestIntersection01.y << ", " << closestIntersection01.z << std::endl;
		// std::cout << "closestIntersection02: " << closestIntersection02.x << ", " << closestIntersection02.y << ", " << closestIntersection02.z << std::endl;
		// std::cout << "closestIntersection12: " << closestIntersection12.x << ", " << closestIntersection12.y << ", " << closestIntersection12.z << std::endl;

		hpuint intersectCount = 0;
		if (intersects01) intersectCount++;
		if (intersects02) intersectCount++;
		if (intersects12) intersectCount++;


		// std::cout << "intersectCount:" << intersectCount << std::endl;

		if (intersectCount <= 1) {
			return false;
		} else {

			if (intersects01) {
				intersectionA = closestIntersection01;
			} else {
				intersectionA = closestIntersection02;
			}

			if (intersects12) {
				intersectionB = closestIntersection12;
			} else {
				intersectionB = closestIntersection02;
			}

			return true;
		}
	}

	// This method computes the one and only one intersection point of two lines when we know that it must exist
	hpvec3 computeClosestLineLineIntersection(hpvec3& linePointA, hpvec3& linePointB, hpvec3 lineDirectionA, hpvec3 lineDirectionB) {
		hpreal t;
		if (!floatEquals(lineDirectionB.x, 0.0)) {
			t = (linePointB.x - linePointA.x) / lineDirectionB.x;
		} else if (!floatEquals(lineDirectionB.y, 0.0)) {
			t = (linePointB.y - linePointA.y) / lineDirectionB.y;
		} else {
			t = (linePointB.z - linePointA.z) / lineDirectionB.z;
		}
		hpvec3 intersectionPoint = linePointB + t * lineDirectionB;
		return intersectionPoint;
	}

	// this method intersects two non axis aligned planes
	void intersectPlanes(hpvec3& t_normal, hpvec3& t_vertex, hpvec3& m_normal, hpvec3& m_vertex,
			hpvec3& linePoint, hpvec3& lineDirection) {

		hpvec3 h1 = m_vertex;
		hpvec3 h2 = t_vertex;
		hpvec3 n1 = m_normal;
		hpvec3 n2 = t_normal;

		hpreal dotProduct = glm::dot(n1, n2);
		hpvec3 c1 = (h1 - h2 * dotProduct) / (1.0f - dotProduct * dotProduct);
		hpvec3 c2 = (h2 - h1 * dotProduct) / (1.0f - dotProduct * dotProduct);

		linePoint = c1 * n1 + c2 * n2;
		lineDirection = glm::cross(m_normal, t_normal);

		 // // std::cout << "Triangle vertex: " << t_vertex.x << ", " << t_vertex.y << ", " << t_vertex.z << std::endl;
		 // // std::cout << "Triangle normal: " << t_normal.x << ", " << t_normal.y << ", " << t_normal.z << std::endl;
		 // // std::cout << "Circle center: " << m_center.x << ", " << m_center.y << ", " << m_center.z << std::endl;
		 // // std::cout << "Circle normal: " << m_normal.x << ", " << m_normal.y << ", " << m_normal.z << std::endl;
	}


	hpreal computePointPlaneDistance(hpvec3& p_normal, hpvec3& p_vertex, hpvec3& point) {
		return glm::dot((point - p_vertex), glm::normalize(p_normal));
	}

	// Check whether 2 vectors are linear dependent
	bool linearDependent(hpvec3& a, hpvec3& b) {
		if (floatEquals(a.x, 0.0) ^ floatEquals(b.x, 0.0))
			return false;
		if (floatEquals(a.y, 0.0) ^ floatEquals(b.y, 0.0))
			return false;
		if (floatEquals(a.z, 0.0) ^ floatEquals(b.z, 0.0))
			return false;

		bool ignoreX = floatEquals(b.x, 0.0);
		bool ignoreY = floatEquals(b.y, 0.0);
		bool ignoreZ = floatEquals(b.z, 0.0);

		hpreal ratioX = a.x / b.x;
		hpreal ratioY = a.y / b.y;
		hpreal ratioZ = a.z / b.z;

		hpreal equalsXY = floatEquals(ratioX, ratioY);
		hpreal equalsYZ = floatEquals(ratioY, ratioZ);
		hpreal equalsXZ = floatEquals(ratioX, ratioZ);

		return (ignoreX && ignoreY)
		    || (ignoreY && ignoreZ)
		    || (ignoreX && ignoreZ)
		    || (equalsYZ && ignoreX)
		    || (equalsXZ && ignoreY)
		    || (equalsXY && ignoreZ)
		    || (equalsXY && equalsXZ);
	}

	// Check whether two hpreals are equal plus minus a tolerance value
	bool floatEquals(hpreal a, hpreal b) {
		const hpreal epsilon = 10e-07;
		return (a > b - epsilon) && (a < b + epsilon);
	}

	// Check whether two floats are equal plus minus a tolerance value
	bool floatEquals(hpreal a, hpreal b, hpreal epsilon) {
		return (a > b - epsilon) && (a < b + epsilon);
	}

	// Check whether a vector has only zeros
	// This requires a very small epsilon (i.e. 10-e7) to avoid misinterpretation of small normals
	bool isNullVector(hpvec3& vector) {
	  hpreal epsilon = 10e-10;
		if (floatEquals(vector.x, 0.0, epsilon) && floatEquals(vector.y, 0.0, epsilon) && floatEquals(vector.z, 0.0, epsilon)) {
			return true;
		} else {
			return false;
		}
	}

	// Check whether a vector has only valid entries
	bool isValidVector(hpvec3& vector) {
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
	bool floatSmaller(hpreal a, hpreal b) {
		const hpreal epsilon = 10e-06;
		return floatSmaller(a, b, epsilon);
	}

	// Check whether float a is smaller than float b
	// A tolerance is added that makes overlapping more likely
	bool floatSmaller(hpreal a, hpreal b, hpreal epsilon) {
		return a < b + epsilon;
	}

	// Check whether hpreal a is bigger than hpreal b
	// A tolerance is added that makes overlapping more likely
	bool floatBigger(hpreal a, hpreal b) {
		const hpreal epsilon = 10e-06;
		return floatBigger(a, b, epsilon);
	}

	bool floatBigger(hpreal a, hpreal b, hpreal epsilon) {
		return a > b - epsilon;
	}

	// Check whether a given point lies inside a triangle, assuming that they lie already in one plane
	bool pointInTriangle(hpvec3& p, Triangle& triangle) {
		hpvec3 a = triangle.vertices[0];
		hpvec3 b = triangle.vertices[1];
		hpvec3 c = triangle.vertices[2];

		if (pointsOnSameSideOfLineTolerant(p, a, b, c) && pointsOnSameSideOfLineTolerant(p, b, a, c)
				&& pointsOnSameSideOfLineTolerant(p, c, a, b)) {
			return true;
		} else {
			return false;
		}
	}

	// Check whether 2 points p1 and p2 are on the same side of the line between a and b
	// If p1 or p2 is on the line, it counts as not being on the same side
	bool pointsOnSameSideOfLineTolerant(hpvec3& p1, hpvec3& p2, hpvec3& a, hpvec3& b) {
		hpvec3 cp1 = glm::cross(b - a, p1 - a);
		hpvec3 cp2 = glm::cross(b - a, p2 - a);

		hpreal dotProduct = glm::dot(cp1, cp2);

		if (floatBigger(dotProduct, 0.0)) {
			return true;
		} else {
			return false;
		}
	}

	// Check whether 2 points p1 and p2 are on the same side of the line between a and b
	// If p1 or p2 is on the line, it counts as being on the same side
	bool pointsOnSameSideOfLineNonTolerant(hpvec3& p1, hpvec3& p2, hpvec3& a, hpvec3& b) {
		hpvec3 cp1 = glm::cross(b - a, p1 - a);
		hpvec3 cp2 = glm::cross(b - a, p2 - a);

		hpreal dotProduct = glm::dot(cp1, cp2);

		if (floatEquals(dotProduct, 0.0, 10e-4)) {
		    return false;
		} else if (dotProduct > 0.0) {
			return true;
		} else {
			return false;
		}
	}

	// Note that the conversion here regards the circle as a sphere.
	// Further optimization might be possible for circles.
	BBox computeBoundingBox() {
	  hpvec3 radiusV = hpvec3(m_radius, m_radius, m_radius);
	  hpvec3 min = m_center - radiusV;
	  hpvec3 max = m_center + radiusV;
	  return BBox(min, max);
	}
};

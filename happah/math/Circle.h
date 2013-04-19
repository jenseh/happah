#pragma once

#include <algorithm>
#include <cmath>
#include <glm/glm.hpp>
#include <iostream>
#include <list>

#include "happah/HappahTypes.h"
#include "happah/kdtree/BBox.h"
#include "happah/kdtree/BSphere.h"
#include "happah/math/Triangle.h"

#include "happah/LoggingUtils.h"

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
  hpvec3 hitPointA;
  hpvec3 hitPointB;
  Triangle* object;

  CircleHitResult(hpvec3 hitPointA_, hpvec3 hitPointB_, Triangle* object_) : hitPointA(hitPointA_), hitPointB(hitPointB_), object(object_) {
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
	bool intersect(Triangle* triangle, std::list<CircleHitResult*>* hitResults) {
		hpvec3 t_normal = triangle->computeNormal();

		//LoggingUtils::printVal("radius", m_radius);
		//LoggingUtils::printVec("circle", m_center);




		// Start with a plane-plane intersection

		// Sanity check: If a normal vector is all 0, then abort
		bool nullNormal = isNullVector(t_normal) || isNullVector(m_normal);
		if (nullNormal) {
		    std::cerr << "Error: One of the geometry's normals is a null vector!" << std::endl;
		    //LoggingUtils::printVec("EtriangleA", triangle->vertices[0]);
		    //LoggingUtils::printVec("EtriangleB", triangle->vertices[1]);
		    //LoggingUtils::printVec("EtriangleC", triangle->vertices[2]);

		    //LoggingUtils::printVec("t_normal", t_normal);
		    //LoggingUtils::printVec("m_normal", m_normal);

		    return false;
		    //exit(1);
		}
		//LoggingUtils::printVec("t_normal", t_normal);
		//LoggingUtils::printVec("m_normal", m_normal);

		//1: Check collinearity of normal vectors
		bool collinear = linearDependent(m_normal, t_normal);
		// std::cout << "Info: Collinear: " << collinear << std::endl;

		if (collinear) {
			std::cout << "Debug-Info: The very unlikely case of collinear Triangle-Circle intersection just happened!" << std::endl;
		
			//2: Check whether planes are identical or parallel
			bool identical = floatEquals(glm::dot(m_center - triangle->vertices[2], t_normal), 0.0);
			// std::cout << "Info: Identical: " << identical << std::endl;

			//2a: If planes are parallel, return false
			if (!identical) {
				// std::cout << "Error: Collinear | Planes are parallel!" << std::endl;
				return false;
			}

			//2b: If planes are identical, compute planar intersection of triangle and circle
			else {
				// Compute the closest points on triangle sides to the circle center
				hpvec3 closestPoint01 = glm::closestPointOnLine(m_center, triangle->vertices[0], triangle->vertices[1]);
				hpvec3 closestPoint12 = glm::closestPointOnLine(m_center, triangle->vertices[1], triangle->vertices[2]);
				hpvec3 closestPoint02 = glm::closestPointOnLine(m_center, triangle->vertices[0], triangle->vertices[2]);

				// Compute the respective distances
				hpreal distC01 = glm::distance(m_center, closestPoint01);
				hpreal distC12 = glm::distance(m_center, closestPoint12);
				hpreal distC02 = glm::distance(m_center, closestPoint02);

				// Check whether any distance is shorter than the radius
				bool triangleInside = floatSmaller(distC01, m_radius) || floatSmaller(distC12, m_radius) || floatSmaller(distC02, m_radius);
				// std::cout << "Info: triangleInside: " << triangleInside << std::endl;

				if (triangleInside) {
					// ..then the triangle is "inside" the circle
				    // std::cout << distC01 << ", " << distC12 << ", " << distC02 << ", " << m_radius << std::endl;
				    // std::cout << "Success: Collinear | Triangle inside circle!" << std::endl;

				    // Get point on triangle (edge) that is closest to center
				    hpvec3* hitPoint;

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
						// std::cout << "Success: Collinear | Circle inside triangle!" << std::endl;
						CircleHitResult* tempHitResult = new CircleHitResult(m_center, m_center, triangle);
						hitResults->push_back(tempHitResult);
						return true;
					} else {
						// std::cout << "Error: Collinear | Circle not inside triangle!" << std::endl;
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
			hpvec3 linePoint;
			hpvec3 lineDirection;
			intersectPlanes(t_normal, triangle->vertices[0], m_normal, m_center, linePoint, lineDirection);

			// Normalize lineDirection for distance comparisons
			lineDirection = glm::normalize(lineDirection);

			    // std::cout << "Intersect linePoint: " << linePoint.x << ", " << linePoint.y << ", " << linePoint.z << std::endl;
			    // std::cout << "Intersect lineDir: " << lineDirection.x << ", " << lineDirection.y << ", " << lineDirection.z << std::endl;

			// Check whether this line hits our sphere
			// Check whether distance is shorter than the radius
			hpvec3 circleIntersectionA;
			hpvec3 circleIntersectionB;
			if (intersectPlanarLineCircle(m_center, m_radius, linePoint, lineDirection, circleIntersectionA, circleIntersectionB)) {


				// Since the line hits our sphere we only need to check whether it also hits the triangle
				//TODO:
				hpvec3 triangleIntersectionA;
				hpvec3 triangleIntersectionB;
				bool intersectsTriangle = intersectPlanarLineTriangle(linePoint, lineDirection, triangle,
						triangleIntersectionA, triangleIntersectionB);

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
				    if ((floatBigger(*maxTv, *minCv) && floatBigger(*maxCv, *minTv))) {
					// std::cout << "Success: Overlapping!" << std::endl;

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


					hpvec3 closestPointToCenter = glm::closestPointOnLine(m_center, *minVec, *maxVec);

					// In case min and max are equal, we would get tripple NAN
					if (!isValidVector(closestPointToCenter)) closestPointToCenter = *minVec;

					CircleHitResult* tempHitResult = new CircleHitResult(*minVec, *maxVec, triangle);
					hitResults->push_back(tempHitResult);
					// std::cout << "minVec: " << minVec->x << ", " << minVec->y << ", " << minVec->z << std::endl;
					// std::cout << "maxVec: " << maxVec->x << ", " << maxVec->y << ", " << maxVec->z << std::endl;
					// std::cout << "Intersect center: " << m_center.x << ", " << m_center.y << ", " << m_center.z << std::endl;
					// std::cout << "Intersect inside: " << closestPointToCenter.x << ", " << closestPointToCenter.y << ", " << closestPointToCenter.z << std::endl;

//					CircleHitResult* hitResult = hitResults->back();
//					// std::cout << "Intersect outside1B: size " << hitResults->size() << std::endl;
//					// std::cout << "Intersect outside1B: " << (hitResult != 0) << std::endl;
//					// std::cout << "Intersect outside2B: " << hitResult->range.startAngle << ", " << hitResult->range.endAngle << ", " << hitResult->range.radius << std::endl;
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
				// std::cout << "linePoint: " << linePoint.x << ", " << linePoint.y << ", " << linePoint.z << std::endl;
				// std::cout << "lineDirection: " << lineDirection.x << ", " << lineDirection.y << ", " << lineDirection.z << std::endl;

				// std::cout << "Error: Exiting due to: Line doesn't hit circle!" << m_radius << std::endl;
				return false;
			}
		}

		   // std::cout << "Error: Nothing happened!" << std::endl;
		return false;
	}

	// Note that the values are not normalized (too expensive) and can only
	// be compared to other values from this method.
	// In effect we compute the ratio between the direction vector and the point difference vector.
	hpreal inline computeDistanceOnLine(hpvec3& distancePoint, hpvec3& linePoint, hpvec3& lineDirection) {
//	   hpvec3 difference = distancePoint - linePoint;
//	   return glm::length(difference);

	   if (!floatEquals(lineDirection.x, 0.0)) {
	       return (distancePoint.x - linePoint.x) / lineDirection.x;
	   } else if (!floatEquals(lineDirection.y, 0.0)) {
	       return (distancePoint.y - linePoint.y) / lineDirection.y;
	   } else {
	      return (distancePoint.z - linePoint.z) / lineDirection.z; //TODO: Only works if there is a z component
	  }
	}

	// Compute max and min per 1d segment and check if they overlap
	bool inline overlapSegments(hpreal& a1, hpreal& a2, hpreal& b1, hpreal& b2) {
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
	bool inline intersectPlanarLineCircle(hpvec3& circleCenter, hpreal circleRadius, hpvec3& linePoint,
			hpvec3& lineDirection, hpvec3& intersectionA, hpvec3& intersectionB) {
		//TODO: fix this by implementing a function for real lines (not segments)
		hpreal highFactor = 10e3;
		hpvec3 closestPoint = glm::closestPointOnLine(circleCenter, linePoint - lineDirection * highFactor, linePoint + lineDirection * highFactor);


		// std::cout << "closestPoint: " << closestPoint.x << ", " << closestPoint.y << ", " << closestPoint.z << std::endl;

		hpreal dist = glm::distance(closestPoint, circleCenter);
		if (floatSmaller(dist, circleRadius)) {
		    // Now we compute the intersection points
		    // This is basically a pythagoras because the line is orthogonal to the center-closestPoint line
		    // and the closestPoint lies in the middle of intersectionA and intersectionB
		    hpvec3 replacement = glm::normalize(lineDirection) * glm::sqrt(circleRadius * circleRadius - dist * dist);
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
	bool inline intersectPlanarLineTriangle(hpvec3& linePoint, hpvec3& lineDirection, Triangle* triangle,
			hpvec3& intersectionA, hpvec3& intersectionB) {
		hpvec3 a = linePoint;
		hpvec3 b = a + lineDirection;

		hpvec3 p0 = triangle->vertices[0];
		hpvec3 p1 = triangle->vertices[1];
		hpvec3 p2 = triangle->vertices[2];

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
		    intersectionA = computeKnownPlanarLineLineIntersection(linePoint, p0, p1 - p0);
		    intersectionB = computeKnownPlanarLineLineIntersection(linePoint, p0, p2 - p0);
		  } else if (!pSS12) {
		    intersectionA = computeKnownPlanarLineLineIntersection(linePoint, p1, p0 - p1);
		    intersectionB = computeKnownPlanarLineLineIntersection(linePoint, p1, p2 - p1);
		  } else if (!pSS02) {
		    intersectionA = computeKnownPlanarLineLineIntersection(linePoint, p2, p0 - p2);
		    intersectionB = computeKnownPlanarLineLineIntersection(linePoint, p2, p1 - p2);
		  }

		  return true;
	}

	// This method computes the one and only one intersection point in XY plane (or parallel) of two lines when we know that it must exist
	hpvec3 inline computeKnownPlanarLineLineIntersection(hpvec3& linePointA, hpvec3& linePointB, hpvec3 lineDirectionB) {
		hpreal t = (linePointA.z - linePointB.z) / lineDirectionB.z;
		return linePointB + t * lineDirectionB;
	}

	void inline intersectPlanes(hpvec3& t_normal, hpvec3& t_vertex, hpvec3& m_normal, hpvec3& m_vertex,
			hpvec3& linePoint, hpvec3& lineDirection) {
		// This was solved using paper and pen by setting the planes to be equal

		// Since there are 6 different combinations we setup indices to avoid dividing by 0
		int indexNNotNull = !floatEquals(t_normal.x, 0.0) ? 0 : 1;

		int indexOther = 0 != indexNNotNull ? 0 : 1;


		// Determine plane parameters for triangle plane (n0*x0 + n1*x1 + n2*x2 =  nd)
		hpreal n0 = t_normal[indexNNotNull];
		hpreal n1 = t_normal[indexOther];
		hpreal n2 = t_normal[2];
		hpreal nd = n0 * t_vertex[indexNNotNull] + n1 * t_vertex[indexOther] + n2 * t_vertex[2];

		// Determine plane parameters for circle plane (m0*x0 + m1*x1 + m2*x2 =  md)
		hpreal m0 = m_normal[indexNNotNull];
		hpreal m1 = m_normal[indexOther];
		hpreal m2 = m_normal[2];
		hpreal md = m0 * m_vertex[indexNNotNull] + m1 * m_vertex[indexOther] + m2 * m_vertex[2];

		// Some temporarily used values
		hpreal t = nd - n2 * md;

		// This dimension was chosen as variable
		// Depends on nothing
		linePoint[2] = m_vertex[2]; // Simplification for XY planes
		lineDirection[2] = 0.0;

		// Insert values for the other dimensions
		// Depends on n1, n2
		linePoint[indexOther] = 0.0;
		lineDirection[indexOther] = 1.0;

		// Depends on n1, n2
		linePoint[indexNNotNull] = t / n0;
		lineDirection[indexNNotNull] = -n1 / n0;
	}

	// Check whether 2 vectors are linear dependent
	bool inline linearDependent(hpvec3& a, hpvec3& b) {
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
	bool inline floatEquals(hpreal a, hpreal b) {
		const hpreal epsilon = 10e-07;
		return (a > b - epsilon) && (a < b + epsilon);
	}

	// Check whether two floats are equal plus minus a tolerance value
	bool inline floatEquals(hpreal a, hpreal b, hpreal epsilon) {
		return (a > b - epsilon) && (a < b + epsilon);
	}

	// Check whether a vector has only zeros
	// This requires a very small epsilon (i.e. 10-e7) to avoid misinterpretation of small normals
	bool inline isNullVector(hpvec3& vector) {
	  hpreal epsilon = 10e-10;
		if (floatEquals(vector.x, 0.0, epsilon) && floatEquals(vector.y, 0.0, epsilon) && floatEquals(vector.z, 0.0, epsilon)) {
			return true;
		} else {
			return false;
		}
	}

	// Check whether a vector has only valid entries
	bool inline isValidVector(hpvec3& vector) {
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
	bool inline floatSmaller(hpreal a, hpreal b) {
		const hpreal epsilon = 10e-04;
		return a < b + epsilon;
	}

	// Check whether hpreal a is bigger than hpreal b
	// A tolerance is added that makes overlapping more likely
	bool inline floatBigger(hpreal a, hpreal b) {
		const hpreal epsilon = 10e-04;
		return a > b - epsilon;
	}

	// Check whether a given point lies inside a triangle, assuming that they lie already in one plane
	bool inline pointInTriangle(hpvec3& p, Triangle* triangle) {
		hpvec3 a = triangle->vertices[0];
		hpvec3 b = triangle->vertices[1];
		hpvec3 c = triangle->vertices[2];

		if (pointsOnSameSideOfLineTolerant(p, a, b, c) && pointsOnSameSideOfLineTolerant(p, b, a, c)
				&& pointsOnSameSideOfLineTolerant(p, c, a, b)) {
			return true;
		} else {
			return false;
		}
	}

	// Check whether 2 points p1 and p2 are on the same side of the line between a and b
	// If p1 or p2 is on the line, it counts as not being on the same side
	bool inline pointsOnSameSideOfLineTolerant(hpvec3& p1, hpvec3& p2, hpvec3& a, hpvec3& b) {
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
	bool inline pointsOnSameSideOfLineNonTolerant(hpvec3& p1, hpvec3& p2, hpvec3& a, hpvec3& b) {
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


	// Required for kd-Tree
	BSphere computeBoundingSphere() {
	  return BSphere(m_center, m_radius);
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

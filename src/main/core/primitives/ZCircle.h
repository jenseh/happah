#ifndef ZCIRCLE_H
#define ZCIRCLE_H

// This struct is an optimization of circle that is centered at origin with a normal pointing along z-axis
struct ZCircle {
	float m_radius;

	ZCircle(float radius) : m_radius(radius) {
	}

	// This method checks whether a (filled) triangle intersects a (filled) circle.
	// Assumptions:
	//  - Triangles always have 3 distinct points
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

		// Simplifications for 2d case
		glm::vec2 tv0 = glm::vec2(triangle.vertices[0].x, triangle.vertices[0].y);
		glm::vec2 tv1 = glm::vec2(triangle.vertices[1].x, triangle.vertices[1].y);
		glm::vec2 tv2 = glm::vec2(triangle.vertices[2].x, triangle.vertices[2].y);
		glm::vec2 tn = glm::vec2(t_normal.x, t_normal.y);

		// Start with a plane-plane intersection
//		std::cout << "t_normal: " << t_normal.x << ", " << t_normal.y << ", " << t_normal.z << std::endl;


		//1: Check collinearity of normal vectors
		bool collinear = isZNormal(t_normal);
		// std::cout << "Info: Collinear: " << collinear << std::endl;

		if (collinear) {
			//2: Check whether planes are identical or parallel
			bool identical = floatEquals(glm::dot(tv2, tn), 0.0f);
			// std::cout << "Info: Identical: " << identical << std::endl;

			//2a: If planes are parallel, return false
			if (!identical) {
				return false;
			}

			//2b: If planes are identical, compute planar intersection of triangle and circle
			else {
				// Compute the closest points on triangle sides to the circle center
				glm::vec2 closestPoint01 = closestPointToCenterOnLine(tv0,
						tv1);
				glm::vec2 closestPoint12 = closestPointToCenterOnLine(tv1,
						tv2);
				glm::vec2 closestPoint02 = closestPointToCenterOnLine(tv0,
						tv2);

				// Compute the respective distances
				float distC01 = glm::length(closestPoint01);
				float distC12 = glm::length(closestPoint12);
				float distC02 = glm::length(closestPoint02);

				// Check whether any distance is shorter than the radius
				bool triangleInside = floatLess(distC01, m_radius) || floatLess(distC12, m_radius) || floatLess(distC02, m_radius);
				// std::cout << "Info: triangleInside: " << triangleInside << std::endl;

				if (triangleInside) {
					// ..then the triangle is "inside" the circle
				    return true;
				} else {
					// Now there is either no intersection or the circle is inside the triangle
					if (originInTriangle(tv0, tv1, tv2)) {
						return true;
					} else {
						return false;
					}
				}
			}
		} else {
			//2: Planes must collide in a common line
			glm::vec2 linePoint;
			glm::vec2 lineDirection;
			intersectPlanes(t_normal, triangle.vertices[0], linePoint, lineDirection);

			// Check whether this line hits our sphere
			// Check whether distance is shorter than the radius
			glm::vec2 circleIntersectionA;
			glm::vec2 circleIntersectionB;
			if (intersectPlanarLineCircle(linePoint, lineDirection, circleIntersectionA, circleIntersectionB)) {
				// Since the line hits our sphere we only need to check whether it also hits the triangle
				//TODO:
				glm::vec2 triangleIntersectionA;
				glm::vec2 triangleIntersectionB;
				bool intersectsTriangle = intersectPlanarLineTriangle(linePoint, lineDirection, tv0, tv1, tv2,
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
	float inline computeDistanceOnLine(glm::vec2& distancePoint, glm::vec2& linePoint, glm::vec2& lineDirection) {
	   if (!floatEquals(lineDirection.x, 0.0f)) {
	       return (distancePoint.x - linePoint.x) / lineDirection.x;
	   } else {
	       return (distancePoint.y - linePoint.y) / lineDirection.y;
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
	bool inline intersectPlanarLineCircle(glm::vec2& linePoint, glm::vec2& lineDirection, glm::vec2& intersectionA, glm::vec2& intersectionB) {
		glm::vec2 linePointB = linePoint + lineDirection;
		glm::vec2 closestPoint = closestPointToCenterOnLine(linePoint, linePointB);

		float dist = glm::length(closestPoint);
		if (floatLess(dist, m_radius)) {
		    // Now we compute the intersection points
		    // This is basically a pythagoras because the line is orthogonal to the center-closestPoint line
		    // and the closestPoint lies in the middle of intersectionA and intersectionB
		    glm::vec2 replacement = glm::normalize(lineDirection) * glm::sqrt(m_radius * m_radius - dist * dist);
		    intersectionA = closestPoint + replacement;
		    intersectionB = closestPoint - replacement;

		    return true;
		} else {
		    return false;
		}
	}

	// This method checks whether a (planar) line hits a triangle.
	// If so, the intersection points are stored in the parameters.
	bool inline intersectPlanarLineTriangle(glm::vec2& linePoint, glm::vec2& lineDirection, glm::vec2& tv0, glm::vec2& tv1, glm::vec2& tv2,
			glm::vec2& intersectionA, glm::vec2& intersectionB) {
		glm::vec2& a = linePoint;
		glm::vec2 b = a + lineDirection;

		bool pSS12 = pointsOnSameSideOfLine(tv0, tv1, a, b);
		if (!pSS12) {
		  return false;
		}

		bool pSS23 = pointsOnSameSideOfLine(tv1, tv2, a, b);
		if (!pSS23) {
		  return false;
		}

		// Note: We only get here if intersections occurred
		// The following code chooses the 2 intersection points that are valid
		if (pSS12) {
		    intersectionA = computeKnownPlanarLineLineIntersection(linePoint, lineDirection, tv0, tv1 - tv0);
		} else if (pSS23) {
		    intersectionA = computeKnownPlanarLineLineIntersection(linePoint, lineDirection, tv1, tv2 - tv1);
		}

		if (pSS23) {
		    intersectionB = computeKnownPlanarLineLineIntersection(linePoint, lineDirection, tv1, tv2 - tv1);
		}  else {
		    intersectionB = computeKnownPlanarLineLineIntersection(linePoint, lineDirection, tv0, tv2 - tv0);
		}

		return true;
	}

	// This method computes the one and only one intersection point of two lines when we know that it must exist
	glm::vec2 inline computeKnownPlanarLineLineIntersection(glm::vec2& linePointA, glm::vec2& lineDirectionA, glm::vec2& linePointB, glm::vec2 lineDirectionB) {
	  return glm::vec2((linePointB - linePointA) / (lineDirectionA - lineDirectionB));
	}

	// This intersects the given plane with the z=0 plane of the circle
	void inline intersectPlanes(glm::vec3& t_normal, glm::vec3& t_vertex, glm::vec2& linePoint, glm::vec2& lineDirection) {
		// This was solved using paper and pen by setting the planes to be equal


		// Determine plane parameters for triangle plane (n1*x1 + n2*x2 + n3*x3 =  nd)
		float n1 = t_normal[0];
		float n2 = t_normal[1];
		float dn = n1 * t_vertex[0] + n2 * t_vertex[1];

		// Insert values for the other dimensions
		// Depends on n1
		if (floatEquals(n1, 0.0f)) {
		  linePoint[0] = 0.0f;
		  linePoint[1] = dn / n2;

		  lineDirection[0] = 1.0f;
		  lineDirection[1] = -n1 / n2;
		}
		// Depends on n2
		else {
		    linePoint[0] = dn / n1;
		    linePoint[1] = 0.0f;

                    lineDirection[0] = -n1 / n1;
                    lineDirection[1] = 1.0f;
               }
        }

	// Check whether the vector only has a Z dimension
	// Null vectors are not assumed to be possible by precondition
	bool inline isZNormal(glm::vec3& a) {
	  return floatEquals(a.x, 0.0f) && floatEquals(a.y, 0.0f);
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

	// Check whether the origin lies inside a 2D triangle
	// This is done by determining the quadrant for each vertex
	// Only if in each dimension at least one point is on a different side of +-, the origin is inside
	// TODO: epsilon comparison
	bool inline originInTriangle(glm::vec2& tv0, glm::vec2& tv1, glm::vec2& tv2) {
		return !((tv0.x >= 0 && tv1.x >= 0 && tv2.x >= 0)
		      || (tv0.x <= 0 && tv1.x <= 0 && tv2.x <= 0))
		    && !((tv0.y >= 0 && tv1.y >= 0 && tv2.y >= 0)
		      || (tv0.y <= 0 && tv1.y <= 0 && tv2.y <= 0));
	}

	// Check whether 2 points p1 and p2 are on the same side of the line between a and b
	bool inline pointsOnSameSideOfLine(glm::vec2& p1, glm::vec2& p2, glm::vec2& a, glm::vec2& b) {
		glm::vec2 ab = b - a;

		return floatEquals(glm::dot(ab, p1 - a), glm::dot(ab, p2 - a));
	}

	glm::vec2 inline closestPointToCenterOnLine(glm::vec2& linePoint, glm::vec2& lineDirection) {
	  const float& a1 = lineDirection.x;
	  const float& a2 = lineDirection.y;

	  const float& b1 = linePoint.x;
	  const float& b2 = linePoint.y;

	if (floatEquals(a1, 0.0f)){
	    return glm::vec2(b1, 0.0f);
	} else if (floatEquals(a2, 0.0f)){
	    return glm::vec2(0, b2);
	} else {
	      const float r = a2 / a1; //line slope
	      const float d = b2 - r * b1; //line y-offset
	      const float w = -a1 / a2; //slope of normal to line
	      const float x = d / (w - r);
	      const float y = w * x;

	      return glm::vec2(x, y);
	  }
	}
};

#endif // ZCIRCLE_H

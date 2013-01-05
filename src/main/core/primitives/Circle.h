#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include "Triangle.h"

struct Circle
{
    glm::vec3 m_center;
    glm::vec3 m_normal;
    float m_radius;

    Circle(glm::vec3 center, glm::vec3 normal, float radius) : m_center(center), m_normal(normal), m_radius(radius){
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
    bool checkTriangleIntersection(Triangle* triangle) {
      glm::vec3 t_normal = glm::cross(triangle->vertices[1] - triangle->vertices[0],
                                      triangle->vertices[2] - triangle->vertices[0]);

      // Start with a plane-plane intersection

      // Sanity check: If a normal vector is all 0, then abort
      bool nullNormal = isNullVector(t_normal) || isNullVector(m_normal);
      if (nullNormal) {
           std::cerr << "Error: One of the geometry's normals is a null vector!" << std::endl;
          // std::cout << t_normal.x << ", " << t_normal.y << ", " << t_normal.z << std::endl;
          // std::cout << m_normal.x << ", " << m_normal.y << ", " << m_normal.z << std::endl;
          return false;
      }
      // std::cout << "t_normal: " << t_normal.x << ", " << t_normal.y << ", " << t_normal.z << std::endl;
      // std::cout << "m_normal: " << m_normal.x << ", " << m_normal.y << ", " << m_normal.z << std::endl;

      //1: Check collinearity of normal vectors
      bool collinear =  linearDependent(m_normal, t_normal);

      if (collinear) {
        //2: Check whether planes are identical or parallel
        bool identical = floatEquals(glm::dot(m_center - triangle->vertices[2], t_normal), 0.0f);

        //2a: If planes are parallel, return false
        if (!identical) {
            // std::cout << "Exiting due to: Collinear | Planes are parallel!" << std::endl;
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
            if (floatLess(distC01, m_radius) || floatLess(distC12, m_radius) || floatLess(distC02, m_radius)) {
                // ..then the triangle is "inside" the circle
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
        intersectPlanes(t_normal, triangle->vertices[0], m_normal, m_center, &linePoint, &lineDirection);



        // Check whether this line hits our sphere
        // Check whether distance is shorter than the radius
        // TODO: Make sure closestPointOnLine also works for infinitely long lines (not line segments)

        glm::vec3 closestPoint = glm::closestPointOnLine(m_center, linePoint, linePoint + lineDirection);

        float dist = glm::distance(closestPoint, m_center);
        if (floatLess(dist, m_radius)) {

//        glm::vec3 sphereIntersectionA;
//        glm::vec3 sphereIntersectionB;
//        glm::vec3::value_type v_radius = m_radius;
//        glm::intersectLineSphere(&sphereIntersectionA, &sphereIntersectionB, &m_center, v_radius, &linePoint, &lineDirection);
//        if (sphereIntersectionA != 0 && sphereIntersectionB != 0) {
            // Since the line hits our sphere we only need to check whether it also hits the triangle
            //TODO:
            glm::vec3 triangleIntersectionA;
            glm::vec3 triangleIntersectionB;
            bool intersectsTriangle = intersectPlanarLineTriangle(&linePoint, &lineDirection, triangle, &triangleIntersectionA, &triangleIntersectionB);

            if (intersectsTriangle) {
                // std::cout << "Exiting due to: Not Collinear | Not implemented!" << std::endl;
                return true;
            } else {
                // std::cout << "Exiting due to: Not Collinear | No intersection with triangle!" << std::endl;
                return true;
            }

        } else {
            // Since the line does not even hit the sphere we can quit directly
            // std::cout << "linePoint: " << linePoint.x << ", " << linePoint.y << ", " << linePoint.z << std::endl;
            // std::cout << "Not Collinear | Exiting due to: Line doesn't hit circle!" << dist << ", " << m_radius << std::endl;
            return false;
        }
      }

      // std::cout << "Exiting due to: Nothing happened!" << std::endl;
      return false;
    }

    bool inline intersectPlanarLineTriangle(glm::vec3* linePoint, glm::vec3* lineDirection, Triangle* triangle, glm::vec3* triangleIntersectionA, glm::vec3* triangleIntersectionB) {
      glm::vec3 a = *linePoint;
      glm::vec3 b = a + *lineDirection;

      glm::vec3 p1 = triangle->vertices[0];
      glm::vec3 p2 = triangle->vertices[1];
      glm::vec3 p3 = triangle->vertices[2];

      if (!pointsOnSameSideOfLine(p1, p2, a, b)) return false;
      if (!pointsOnSameSideOfLine(p2, p3, a, b)) return false;
      if (!pointsOnSameSideOfLine(p1, p3, a, b)) return false;

      return true;
    }

    void inline intersectPlanes(glm::vec3 t_normal, glm::vec3 t_vertex, glm::vec3 m_normal, glm::vec3 m_vertex, glm::vec3* linePoint, glm::vec3* lineDirection){
      // This was solved using paper and pen by setting the planes to be equal

      // Since there are 6 different combinations we setup indices to avoid dividing by 0
      int indexNNotNull = !floatEquals(t_normal.x, 0.0f) ? 0
                        : !floatEquals(t_normal.y, 0.0f) ? 1
                        : 2;

      int indexNMDifferent = 0 != indexNNotNull && !floatEquals(t_normal.x - m_normal.x, 0.0f) ? 0
                           : 1 != indexNNotNull && !floatEquals(t_normal.y - m_normal.y, 0.0f) ? 1
                           : 2;

      int indexOther = 0 != indexNMDifferent && 0 != indexNNotNull ? 0
                     : 1 != indexNMDifferent && 1 != indexNNotNull ? 1
                     : 2;


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
      (*linePoint)[indexOther] = 0.0f;
      (*lineDirection)[indexOther] = 1.0f;

      // Insert values for the other dimensions
      // Depends on m2, n2
      (*linePoint)[indexNMDifferent] = p;
      (*lineDirection)[indexNMDifferent] = v;

      // Depends on n1, m2, n2
      (*linePoint)[indexNNotNull] = (nd - n2 * p) / n1;
      (*lineDirection)[indexNNotNull] = (-n2 * v - n3) / n1;

      // TODO: What happens if any of the denominators is 0? n1, (m2 - n2)  -> exchange indices
      // std::cout << "indices: " << indexNMDifferent << ", " << indexNNotNull << ", " << indexOther << std::endl;
      // std::cout << "linePoint: " << linePoint->x << ", " << linePoint->y << ", " << linePoint->z << std::endl;
      // std::cout << "lineDirection: " << lineDirection->x << ", " << lineDirection->y << ", " << lineDirection->z << std::endl;
    }


    // Check whether 2 vectors are linear dependent
    bool inline linearDependent(glm::vec3 a, glm::vec3 b) {
      if (floatEquals(a.x, 0.0f) ^ floatEquals(b.x, 0.0f)) return false;
      if (floatEquals(a.y, 0.0f) ^ floatEquals(b.y, 0.0f)) return false;
      if (floatEquals(a.z, 0.0f) ^ floatEquals(b.z, 0.0f)) return false;

      float ratioX = floatEquals(b.x, 0.0f) ? 0.0f : a.x / b.x;
      float ratioY = floatEquals(b.y, 0.0f) ? 0.0f : a.y / b.y;
      float ratioZ = floatEquals(b.z, 0.0f) ? 0.0f : a.z / b.z;

      return floatEquals(ratioX, ratioY) && floatEquals(ratioY, ratioZ);
    }

    // Check whether two floats are equal plus minus a tolerance value
    bool inline floatEquals(float a, float b) {
      const double epsilon = 0.000001d;
      return (a > b - epsilon) && (a < b + epsilon);
    }
    // Check whether a vector has only zeros
    bool inline isNullVector(glm::vec3 vector) {
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
    bool inline pointInTriangle(glm::vec3 p, Triangle* triangle) {
      glm::vec3 a = triangle->vertices[0];
      glm::vec3 b = triangle->vertices[1];
      glm::vec3 c = triangle->vertices[2];

      if (pointsOnSameSideOfLine(p, a, b, c)
          && pointsOnSameSideOfLine(p, b, a, c)
          && pointsOnSameSideOfLine(p, c, a, b)) {
          return true;
        } else {
        return false;
      }
    }


    // Check whether 2 points p1 and p2 are on the same side of the line between a and b
    bool inline pointsOnSameSideOfLine(glm::vec3 p1, glm::vec3 p2, glm::vec3 a, glm::vec3 b) {
        glm::vec3 cp1 = glm::cross(b-a, p1-a);
        glm::vec3 cp2 = glm::cross(b-a, p2-a);
        if (glm::dot(cp1, cp2) >= 0) {
            return true;
        }
        else {
            return false;
        }
    }
};

#include "WormGearGrind.h"
#include <time.h>

WormGearGrind::WormGearGrind(SpurGear& worm, SpurGear& gear) :
    m_worm(worm), m_gear(gear)
{
}

WormGearGrind::~WormGearGrind() {}
// Assumptions
//  - The circles are sorted per z coordinate from small to big radius
void WormGearGrind::calculateGrindingDepth(){
   CircleCloud& worm = *(m_worm.toCircleCloud());
   TriangleMesh& gear = *(m_gear.toTriangleMesh());

   std::vector<Circle*>& circles = worm.getCircles();
   gear.fillTriangles();
   std::vector<Triangle*>& triangles = *(gear.getTriangles());

   size_t resolutionXY = worm.getResolutionXY();
   size_t resolutionZ = worm.getResolutionZ();

   std::list<Triangle*> hits;

   clock_t start, end;

   start = clock();
   // Compute the distance for between every circle and triangle
   // TODO: Optimize this using spatial data structures
   for (size_t z = 0; z < resolutionZ; z++) {
       int minXY = 0;
       int maxXY = resolutionXY - 1;

       // Check upper bound
       int xy = maxXY;
       computeIntersectingTriangles(xy, resolutionXY, z, circles, triangles, hits);
       if (hits.size() <= 0) {
           std::cout << "No intersect inside: at [" << z << "]" << std::endl;
           continue;
       }

       // Check lower bound
       xy = minXY;
       reduceIntersectingTriangles(xy, resolutionXY, z, circles, hits);
       if (hits.size() <= 0) {
           std::cout << "No intersect in range: at [" << z << "]" << std::endl;
           continue;
       }

       // Start binary search
       while (maxXY - minXY > 1) {
          xy = (minXY + maxXY) / 2;

          bool intersectsMiddle = reduceNonIntersectingTriangles(xy, resolutionXY, z, circles, hits);

          if (intersectsMiddle) {
            maxXY = xy;
          } else {
            minXY = xy;
          }
       }

       // We found a solution in minXY
       std::cout << "Intersect: at [" << z << ", " << minXY << "]" << std::endl;

     }
   end = clock();
   cout << "Time required for execution: " << (double)(end-start)/CLOCKS_PER_SEC << " seconds." << "\n\n";
    return;
}


bool inline WormGearGrind::checkIntersection(int& xy, size_t& resolutionXY, size_t& z, std::vector<Circle*>& circles, std::vector<Triangle*>& triangles) {
  for (size_t j = 0; j < triangles.size(); j++) {
      int i = z * resolutionXY + xy;
      Circle transformedCircle = transformCircle(*(circles[i]));
      bool intersectionXY = transformedCircle.checkTriangleIntersection(*triangles[j]);

      if (intersectionXY) {

          // TODO: Remember radius
          //          float curRadius = transformedCircle.m_radius;
          //          if (curRadius < minRadius) {
          //              minRadius = curRadius;
          //            }

          // Since we detected a collision we can return true
          return true;
        }
    }
  return false;
}
void inline WormGearGrind::computeIntersectingTriangles(int& xy, size_t& resolutionXY, size_t& z, std::vector<Circle*>& circles, std::vector<Triangle*>& triangles, std::list<Triangle*>& hits) {
  for (size_t j = 0; j < triangles.size(); j++) {
      int i = z * resolutionXY + xy;
      Circle transformedCircle = transformCircle(*(circles[i]));
      bool intersectionXY = transformedCircle.checkTriangleIntersection(*triangles[j]);

      if (intersectionXY) {
          // Since we detected a collision we can return true
          hits.push_back(triangles[j]);
        }
    }
}

// Returns whether a triangle could be removed from hits
bool inline WormGearGrind::reduceIntersectingTriangles(int& xy, size_t& resolutionXY, size_t& z, std::vector<Circle*>& circles, std::list<Triangle*>& hits) {
  size_t startSize = hits.size();
  for (std::list<Triangle*>::iterator it = hits.begin(); it != hits.end();) {
      int i = z * resolutionXY + xy;
      Circle transformedCircle = transformCircle(*(circles[i]));
      bool intersectionXY = transformedCircle.checkTriangleIntersection(**it);

      if (intersectionXY) {
          // Since we detected a collision we can return true
          it = hits.erase(it);
      } else {
          it++;
      }
    }
  return hits.size() == startSize;
}

bool inline WormGearGrind::reduceNonIntersectingTriangles(int& xy, size_t& resolutionXY, size_t& z, std::vector<Circle*>& circles, std::list<Triangle*>& hits) {
  size_t startSize = hits.size();
  for (std::list<Triangle*>::iterator it = hits.begin(); it != hits.end();) {
      int i = z * resolutionXY + xy;
      Circle transformedCircle = transformCircle(*(circles[i]));
      bool intersectionXY = transformedCircle.checkTriangleIntersection(**it);

      if (!intersectionXY) {
          // Since we detected a collision we can return true
          // Assigning the following element of it to it prevents null pointers
          it = hits.erase(it);
      } else {
          it++;
      }
    }
  return hits.size() == startSize;
}


glm::vec3 inline WormGearGrind::transformVector(glm::vec3& vector, QMatrix4x4& transformation) {
  QVector3D result = transformation.mapVector(QVector3D(vector.x, vector.y, vector.z));
  return glm::vec3(result.x(), result.y(), result.z());
}
glm::vec3 inline WormGearGrind::transformPoint(glm::vec3& point, QMatrix4x4& transformation) {
  QVector4D result = transformation.map(QVector4D(point.x, point.y, point.z, 1.0f));
  return glm::vec3(result.x(), result.y(), result.z());
}

// This transform a triangle into a different the space of the circle.
// Note that normals are not transformed, since we don't use them here.
Triangle WormGearGrind::transformTriangle(Triangle& triangle) {
  QMatrix4x4 transformation = *(m_gear.getModelMatrix()) * (m_worm.getModelMatrix()->inverted(0));
  return Triangle(transformPoint(triangle.vertices[0], transformation),
                  transformPoint(triangle.vertices[1], transformation),
                  transformPoint(triangle.vertices[2], transformation));
}

// This transform a circle into the different space of the triangle.
// Note that the radius is not transformed, since we forbid scaling.
Circle WormGearGrind::transformCircle(Circle& circle) {
  QMatrix4x4 transformation = *(m_worm.getModelMatrix()) * (m_gear.getModelMatrix()->inverted(0));
  return Circle(transformPoint(circle.m_center, transformation),
                  transformVector(circle.m_normal, transformation), circle.m_radius);
}





void WormGearGrind::runSimulation() {
  calculateGrindingDepth();
}

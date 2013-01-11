#include "WormGearGrind.h"
#include <time.h>

WormGearGrind::WormGearGrind(SpurGear& worm, SpurGear& gear) {
    m_worm = worm.toZCircleCloud();
    m_gear = gear.toTriangleMesh();
}

WormGearGrind::~WormGearGrind() {}

void WormGearGrind::calculateGrindingDepth(){
   std::cout << "Starting simulation:" << std::endl;
   m_gear->translate(0.5f, 0.0f, 0.0f); //TODO:remove
   m_gear->fillTriangles();
   std::vector<Triangle*>& triangles = *(m_gear->getTriangles());

   size_t resolutionXY = m_worm->getResolutionXY();
   size_t resolutionZ = m_worm->getResolutionZ();


   clock_t start, end;
   clock_t startZ, endZ;

   start = clock();
   // Compute the distance for between every circle and triangle
   // TODO: Optimize this using spatial data structures
   for (size_t z = 0; z < resolutionZ; z++) {
       startZ = clock();
       std::list<Triangle*> hits;
       int minXY = 0;
       int maxXY = resolutionXY - 1;
       int intersectionCount = 0;

       // Check upper bound
       int xy = maxXY;
       computeIntersectingTriangles(xy, z, triangles, hits);
       intersectionCount++;
       if (hits.size() <= 0) {
           std::cout << "No intersect inside: at [" << z << "]" << std::endl;
           continue;
         }

       // Check lower bound
       xy = minXY;
       reduceIntersectingTriangles(xy, z, hits);
       intersectionCount++;
       if (hits.size() <= 0) {
           std::cout << "No intersect in range: at [" << z << "]" << std::endl;
           continue;
       }

       // Start binary search
       while (maxXY - minXY > 1 && hits.size() > 0) {
           if (hits.size() == 0) std::cout << "Error: Invalid hits size: " << hits.size() << std::endl;
//           else std::cout << "Hits size: " << hits.size() << std::endl;
           xy = (minXY + maxXY) / 2;

           bool intersectsMiddle = reduceSubdivideTriangles(xy, z, hits);
           intersectionCount++;

           if (intersectsMiddle) {
               maxXY = xy;
             } else {
               minXY = xy;
             }
       }

       // We found a solution in minXY
       if (hits.size() <= 0) {
           std::cout << "Error: at [" << z << ", " << minXY  << std::endl;
           continue;
       }
       endZ = clock();
       std::cout << "Intersect: at [" << z << ", " << minXY << "], intersections: " << intersectionCount << std::endl;
       std::cout << "Time required for execution at z: " << (double)(endZ - startZ)/CLOCKS_PER_SEC << " seconds." << std::endl;
     }
   end = clock();
   std::cout << "Time required for execution: " << (double)(end-start)/CLOCKS_PER_SEC << " seconds." << std::endl << std::endl;
   return;
}


//bool inline WormGearGrind::checkIntersection(int& xy, size_t& z, std::vector<Triangle*>& triangles) {
//  Circle circle = m_worm->computeCircle(z, xy);
//  Circle transformedCircle = transformCircle(circle);
//  for (std::vector<Triangle*>::iterator it = triangles.begin(); it != triangles.end();) {
//      bool intersectionXY = transformedCircle.checkTriangleIntersection(**it);

//      if (intersectionXY) {

//          // TODO: Remember radius
//          //          float curRadius = transformedCircle.m_radius;
//          //          if (curRadius < minRadius) {
//          //              minRadius = curRadius;
//          //            }

//          // Since we detected a collision we can return true
//          return true;
//        }
//    }
//  return false;
//}
void inline WormGearGrind::computeIntersectingTriangles(int& xy, size_t& z, std::vector<Triangle*>& triangles, std::list<Triangle*>& hits) {
  Circle circle = m_worm->computeCircle(z, xy);
  Circle transformedCircle = transformCircle(circle);
  for (std::vector<Triangle*>::iterator it = triangles.begin(); it != triangles.end(); ++it) {
//      if ((**it).vertices[2].x * (**it).vertices[2].x + (**it).vertices[2].y * (**it).vertices[2].y <= 0.25f) {
//        float diff = (**it).vertices[2].z - transformedCircle.m_center.z;
//        if (diff < 0.0f) diff *= -1.0f;
//        if (diff < 0.0001f) {
//          std::cout << "diff: " << diff << std::endl;
//          std::cout << "radius: " << transformedCircle.m_radius << std::endl;
//          std::cout << "circle: " << circle.m_center.x << ", " << circle.m_center.y << ", " << circle.m_center.z << ":" << z << std::endl;
//          std::cout << "tcircle: " << transformedCircle.m_center.x << ", " << transformedCircle.m_center.y << ", " << transformedCircle.m_center.z << std::endl;
//          std::cout << "triangleA: " << (**it).vertices[0].x << ", " << (**it).vertices[0].y << ", " << (**it).vertices[0].z << std::endl;
//          std::cout << "triangleB: " << (**it).vertices[1].x << ", " << (**it).vertices[1].y << ", " << (**it).vertices[1].z << std::endl;
//          std::cout << "triangleC: " << (**it).vertices[2].x << ", " << (**it).vertices[2].y << ", " << (**it).vertices[2].z << std::endl;
//        }
//      }
      bool intersectionXY = transformedCircle.checkTriangleIntersection(**it);
//      if (intersectionXY) {
//                    std::cout << "tcircle: " << transformedCircle.m_center.x << ", " << transformedCircle.m_center.y << ", " << transformedCircle.m_center.z << std::endl;
//                    std::cout << "triangleA: " << (**it).vertices[0].x << ", " << (**it).vertices[0].y << ", " << (**it).vertices[0].z << std::endl;
//                    std::cout << "triangleB: " << (**it).vertices[1].x << ", " << (**it).vertices[1].y << ", " << (**it).vertices[1].z << std::endl;
//                    std::cout << "triangleC: " << (**it).vertices[2].x << ", " << (**it).vertices[2].y << ", " << (**it).vertices[2].z << std::endl;
//          std::cout << "intersectionXY: " << intersectionXY << std::endl;
//      }

      if (intersectionXY) {
          // Since we detected a collision we can return true
          hits.push_back(*it);
        }
    }
}

// Returns whether a triangle could be removed from hits
bool inline WormGearGrind::reduceIntersectingTriangles(int& xy, size_t& z, std::list<Triangle*>& hits) {
  size_t startSize = hits.size();

  Circle circle = m_worm->computeCircle(z, xy);
  Circle transformedCircle = transformCircle(circle);
  for (std::list<Triangle*>::iterator it = hits.begin(); it != hits.end();) {
      bool intersectionXY = transformedCircle.checkTriangleIntersection(**it);
//      if (intersectionXY) {
//                    std::cout << "tcircle: " << transformedCircle.m_center.x << ", " << transformedCircle.m_center.y << ", " << transformedCircle.m_center.z << std::endl;
//                    std::cout << "triangleA: " << (**it).vertices[0].x << ", " << (**it).vertices[0].y << ", " << (**it).vertices[0].z << std::endl;
//                    std::cout << "triangleB: " << (**it).vertices[1].x << ", " << (**it).vertices[1].y << ", " << (**it).vertices[1].z << std::endl;
//                    std::cout << "triangleC: " << (**it).vertices[2].x << ", " << (**it).vertices[2].y << ", " << (**it).vertices[2].z << std::endl;
//          std::cout << "intersectionXY: " << intersectionXY << std::endl;
//      }

      if (intersectionXY) {
          it = hits.erase(it);
      } else {
          it++;
      }
    }
  return hits.size() == startSize;
}

bool inline WormGearGrind::reduceSubdivideTriangles(int& xy, size_t& z, std::list<Triangle*>& hits) {
  size_t startSize = hits.size();
  std::list<Triangle*> inside;
  std::list<Triangle*> outside;

  Circle circle = m_worm->computeCircle(z, xy);
  Circle transformedCircle = transformCircle(circle);
  for (std::list<Triangle*>::iterator it = hits.begin(); it != hits.end(); ++it) {
      bool intersectionXY = transformedCircle.checkTriangleIntersection(**it);
//      if (intersectionXY) {
//                    std::cout << "tcircle: " << transformedCircle.m_center.x << ", " << transformedCircle.m_center.y << ", " << transformedCircle.m_center.z << std::endl;
//                    std::cout << "triangleA: " << (**it).vertices[0].x << ", " << (**it).vertices[0].y << ", " << (**it).vertices[0].z << std::endl;
//                    std::cout << "triangleB: " << (**it).vertices[1].x << ", " << (**it).vertices[1].y << ", " << (**it).vertices[1].z << std::endl;
//                    std::cout << "triangleC: " << (**it).vertices[2].x << ", " << (**it).vertices[2].y << ", " << (**it).vertices[2].z << std::endl;
//          std::cout << "intersectionXY: " << intersectionXY << std::endl;
//      }

      if (intersectionXY) {
          inside.push_back(*it);
      } else {
          outside.push_back(*it);
      }
    }

  if (inside.size() != 0) {
      hits.clear();
      hits.splice(hits.end(), inside);
  } else {
      hits.clear();
      hits.splice(hits.end(), outside);
  }
  return hits.size() != startSize;
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
  QMatrix4x4 transformation = *(m_gear->getModelMatrix()) * (m_worm->getModelMatrix()->inverted(0));
  return Triangle(transformPoint(triangle.vertices[0], transformation),
                  transformPoint(triangle.vertices[1], transformation),
                  transformPoint(triangle.vertices[2], transformation));
}

// This transform a circle into the different space of the triangle.
// Note that the radius is not transformed, since we forbid scaling.
Circle WormGearGrind::transformCircle(Circle& circle) {
  QMatrix4x4 transformation = *(m_worm->getModelMatrix()) * (m_gear->getModelMatrix()->inverted(0));
  return Circle(transformPoint(circle.m_center, transformation),
                  transformVector(circle.m_normal, transformation), circle.m_radius);
}







void WormGearGrind::runSimulation() {
  calculateGrindingDepth();
}

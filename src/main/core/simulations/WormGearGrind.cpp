#include "WormGearGrind.h"
#include <time.h>

WormGearGrind::WormGearGrind(SpurGear& worm, SpurGear& gear) :
    m_worm(worm), m_gear(gear)
{
}

WormGearGrind::~WormGearGrind() {}

void WormGearGrind::calculateGrindingDepth(){
   CircleCloud& worm = *(m_worm.toCircleCloud());
   TriangleMesh& gear = *(m_gear.toTriangleMesh());

   std::vector<Circle*>& circles = worm.getCircles();
   gear.fillTriangles();
   std::vector<Triangle*>& triangles = gear.getTriangles();

   size_t resolutionXY = worm.getResolutionXY();
   size_t resolutionZ = worm.getResolutionZ();

   float minRadius = INFINITY;

   clock_t start, end;

   start = clock();
   // Compute the distance for between every circle and triangle
   // TODO: Optimize this using spatial data structures
   for (size_t z = 0; z < resolutionZ; z++) {
       bool solutionExists = true;
       bool intersectionZ = false;

       // Check outer circle first
       {
         int i = z * resolutionXY + resolutionXY - 1;
         for (size_t j = 0; j < triangles.size(); j++) {
             Circle transformedCircle = transformCircle(*(circles[i]));
//             std::cout << "Transformation: " << circles[i]->m_center.x << ", " << circles[i]->m_center.y << ", " << circles[i]->m_center.z << " to " << transformedCircle.m_center.x << ", " << transformedCircle.m_center.y << ", " << transformedCircle.m_center.z << std::endl;
             bool intersectionXY = transformedCircle.checkTriangleIntersection(*triangles[j]);

           if (!intersectionXY) {
               std::cout << "No solution exists!" << std::endl;
               solutionExists = false;
           }
         }
       }

       if (solutionExists) {
         // Then check all the other circles with all triangles
         for (size_t xy = 0; xy < resolutionXY - 1 && !intersectionZ; xy++) {
           for (size_t j = 0; j < triangles.size(); j++) {
               int i = z * resolutionXY + xy;
               Circle transformedCircle = transformCircle(*(circles[i]));
               bool intersectionXY = transformedCircle.checkTriangleIntersection(*triangles[j]);

               if (intersectionXY) {
                   intersectionZ = true;
                   float curRadius = transformedCircle.m_radius;
                   if (curRadius < minRadius) {
                       minRadius = curRadius;
                   }

                   std::cout << "Intersect: at [" << z << ", " << xy << ":" << j << "], radius: " << curRadius << " / " << minRadius << std::endl;

                   // Since we detected a collision we can go on to another circle
                   break;
               }
           }
        }

         if (!intersectionZ) {
             std::cout << "No intersect: at [" << z << "], radius: " << minRadius << std::endl;
         }
      }
   }
   end = clock();
   cout << "Time required for execution: " << (double)(end-start)/CLOCKS_PER_SEC << " seconds." << "\n\n";
    return;
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

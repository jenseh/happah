#include "WormGearGrind.h"

WormGearGrind::WormGearGrind(SpurGear* worm, SpurGear* gear) :
    m_worm(worm), m_gear(gear)
{
}

void WormGearGrind::calculateGrindingDepth(){
   CircleCloud* worm = m_worm->toCircleCloud();
   TriangleMesh* gear = m_gear->toTriangleMesh();

   std::vector<Circle*> circles = *(worm->getCircles());
   gear->fillTriangles();
   std::vector<Triangle*> triangles = *(gear->getTriangles());

   float minRadius = INFINITY;


   // Compute the distance for between every circle and triangle
   // TODO: Optimize this using spatial data structures
   for (size_t i = 0; i < circles.size(); i++) {
       bool intersection = false;
       for (size_t j = 0; j < triangles.size(); j++) {
           intersection = circles[i]->checkTriangleIntersection(triangles[j]);
           if (intersection) {
               float curRadius = circles[i]->m_radius;
               if (curRadius < minRadius) {
                   minRadius = curRadius;
               }

               std::cout << "Intersect: at [" << i << ", " << j << "], radius: " << curRadius << " / " << minRadius << std::endl;

               // Since we detected a collision we can go on to another circle
               break;
           }
       }
       if (!intersection) {
           std::cout << "No intersect: at [" << i << "], radius: " << minRadius << std::endl;
       }
   }
    return;
}

void WormGearGrind::runSimulation() {
  calculateGrindingDepth();
}

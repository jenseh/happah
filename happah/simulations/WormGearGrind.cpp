#include "happah/simulations/WormGearGrind.h"

WormGearGrind::WormGearGrind(Worm& worm, InvoluteGear& gear, RigidAffineTransformation& wormTransformation, RigidAffineTransformation& gearTransformation) {
    m_worm = worm.toZCircleCloud();
    m_gear = gear.toTriangleMesh();

    m_wormModelMatrix = wormTransformation.toMatrix4x4();
    m_gearModelMatrix = gearTransformation.toMatrix4x4();
}

WormGearGrind::~WormGearGrind() {}


void WormGearGrind::calculateGrindingDepth(){
   std::cout << "Starting simulation:" << std::endl;
   std::vector<Triangle>* triangles = m_gear->toTriangles();

//   for (int i = 0; i < triangles->size(); i++) {
//         Triangle* triangle = triangles->at(i);
//         std::cout << "EtriangleA: " << triangle->vertices[0].x << ", " << triangle->vertices[0].y << ", " << triangle->vertices[0].z << std::endl;
//         std::cout << "EtriangleB: " << triangle->vertices[1].x << ", " << triangle->vertices[1].y << ", " << triangle->vertices[1].z << std::endl;
//         std::cout << "EtriangleC: " << triangle->vertices[2].x << ", " << triangle->vertices[2].y << ", " << triangle->vertices[2].z << std::endl;
//   }
   KDTree tree = KDTree(triangles);
   size_t resolutionZ = m_worm->getResolutionZ();

   size_t resultAngleSlotCount = 100;
   CircularSimulationResult simResult = CircularSimulationResult(resultAngleSlotCount, resolutionZ);

   clock_t start, end;
//   clock_t startZ, endZ;

   start = clock();
   // Compute the distance for between every circle and triangle
   // TODO: Optimize this using spatial data structures
   for (size_t z = 0; z < resolutionZ; z++) {
//       startZ = clock();
       std::list<CircleHitResult*>* hitResults = new std::list<CircleHitResult*>;

       // Check upper bound
       computeIntersectingTriangles(z, tree, hitResults);


       // Get the intersection information and use it to color vertices
       std::list<CircleHitResult*>::iterator pos = hitResults->begin();
       std::list<CircleHitResult*>::iterator end = hitResults->end();
       for (; pos != end; pos++) {
           CircleHitResult* hitResult = *pos;

           simResult.addItem(hitResult->hitPointA, z);
           simResult.addItem(hitResult->hitPointB, z);

          //TODO: Implement this function
//           std::vector<hpvec3*>* closestPoints = m_worm->getClosestPoints(hitResult->hitPoint);
//           std::cout << "CP size: " << closestPoints->size() << std::endl;

//           std::vector<hpvec3*>::iterator posCP = closestPoints->begin();
//           std::vector<hpvec3*>::iterator endCP = closestPoints->end();
//           for (; posCP != endCP; posCP++) {
//              hpvec3* closestPoint = *posCP;
//              std::cout << "HitPoint: " << hitResult->hitPoint.x << ", " << hitResult->hitPoint.y << " : " << hitResult->hitPoint.z << std::endl;
//              std::cout << "   ClosestPoint: " << closestPoint->x << ", " << closestPoint->y << " : " << closestPoint->z << std::endl;
//           }




//           delete closestPoints;
       }

       // Check whether
       if (hitResults->size() <= 0) {
           std::cout << "No intersect: [" << z << "]" << std::endl;
//           Circle circle = m_worm->computeOuterCircle(z);
//           Circle transformedCircle = transformCircle(circle);
//           std::cout << "transformedCircle-center: " << transformedCircle.m_center.x << ", " << transformedCircle.m_center.y << " : " << transformedCircle.m_center.z << std::endl;
//           std::cout << "transformedCircle-normal: " << transformedCircle.m_normal.x << ", " << transformedCircle.m_normal.y << " : " << transformedCircle.m_normal.z << std::endl;
//           std::cout << "transformedCircle-radius: " << transformedCircle.m_radius << std::endl;
       } else {
//        endZ = clock();
           std::cout << "Intersect: at [" << z << "]:" << hitResults->size() << " intersections." << std::endl;
//           Circle circle = m_worm->computeOuterCircle(z);
//           Circle transformedCircle = transformCircle(circle);
//           std::cout << "transformedCircle-center: " << transformedCircle.m_center.x << ", " << transformedCircle.m_center.y << " : " << transformedCircle.m_center.z << std::endl;
//           std::cout << "transformedCircle-normal: " << transformedCircle.m_normal.x << ", " << transformedCircle.m_normal.y << " : " << transformedCircle.m_normal.z << std::endl;
//           std::cout << "transformedCircle-radius: " << transformedCircle.m_radius << std::endl;
       }
//       std::cout << "Time required for execution at z: " << (double)(endZ - startZ)/CLOCKS_PER_SEC << " seconds." << std::endl;
       delete hitResults;
     }

   // Print out results
   for (size_t z = 0; z < resolutionZ; z++) {
     for (size_t angleSlot = 0; angleSlot < resultAngleSlotCount; angleSlot++) {
         float radius = simResult.getItem(angleSlot, z);
         if (radius != INFINITY) {
          std::cout << "angleSlot: " << angleSlot << ", posZ: " << z << ", radius: " << radius << std::endl;
         }
     }
   }



   end = clock();
   std::cout << "Time required for execution: " << (double)(end-start) / CLOCKS_PER_SEC << " seconds." << std::endl << std::endl;
   return;
}


void inline WormGearGrind::computeIntersectingTriangles(size_t& z, KDTree& tree, std::list<CircleHitResult*>* hitResults) {
  Circle circle = m_worm->computeOuterCircle(z);
  Circle transformedCircle = transformCircle(circle);

  tree.intersectAll(transformedCircle, hitResults);
}

hpvec3 inline WormGearGrind::transformVector(hpvec3& vector, hpmat4x4& transformation) {
  hpvec4 result = transformation * hpvec4(vector.x, vector.y, vector.z, 1.0);
  return hpvec3(result.x, result.y, result.z); //TODO: does this make sense?
}
hpvec3 inline WormGearGrind::transformPoint(hpvec3& point, hpmat4x4& transformation) {
  hpvec4 result = transformation * hpvec4(point.x, point.y, point.z, 1.0f);
  return hpvec3(result.x, result.y, result.z); //TODO: does this make sense?
}

// This transform a triangle into a different the space of the circle.
// Note that normals are not transformed, since we don't use them here.
Triangle WormGearGrind::transformTriangle(Triangle& triangle) {
  hpmat4x4 transformation = m_gearModelMatrix * glm::inverse(m_wormModelMatrix);
  return Triangle(transformPoint(triangle.vertices[0], transformation),
                  transformPoint(triangle.vertices[1], transformation),
                  transformPoint(triangle.vertices[2], transformation));
}

// This transform a circle into the different space of the triangle.
// Note that the radius is not transformed, since we forbid scaling.
Circle WormGearGrind::transformCircle(Circle& circle) {
  hpmat4x4 transformation = m_wormModelMatrix * glm::inverse(m_gearModelMatrix);
  return Circle(transformPoint(circle.m_center, transformation),
                  transformVector(circle.m_normal, transformation), circle.m_radius);
}

void WormGearGrind::runSimulation() {
  calculateGrindingDepth();
}

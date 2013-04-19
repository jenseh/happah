#include "happah/simulations/WormGearGrind.h"
#include <glm/glm.hpp>

WormGearGrind::WormGearGrind(Worm_ptr worm, TriangleMesh_ptr wormMesh, InvoluteGear_ptr gear, TriangleMesh_ptr gearMesh)
	: m_worm(worm), m_wormMesh(wormMesh), m_gear(gear), m_gearMesh(gearMesh), m_maxDistance(2.0) {

	hpreal rotXStart = 360.0;
	hpreal rotXEnd = 0.0;
	hpreal rotY = 90.0;

	hpreal x = m_worm->getModule() * M_PI / 4.0;
	hpreal y = m_worm->getReferenceRadius() + m_gear->getReferenceRadius();
	hpvec3 position = hpvec3(x, y, 0.0);

    m_wormMovement = Kinematic(
    		Polynom<double>(1, position.x),
    		Polynom<double>(1, position.y),
    		Polynom<double>(1, position.z),
    		Polynom<double>(2, rotXStart, rotXEnd-rotXStart),
    		Polynom<double>(1, rotY),
    		Polynom<double>(0));

    hpreal rotZStart = 0.0;
    hpreal rotZEnd = 360.0 / m_gear->getNumberOfTeeth();

    m_gearMovement = Kinematic(
    		Polynom<double>(0),
    		Polynom<double>(0),
    		Polynom<double>(0),
    		Polynom<double>(0),
    		Polynom<double>(0),
    		Polynom<double>(2, rotZStart, rotZEnd-rotZStart));

    // Convert to right representation
    m_wormCircleCloud = worm->toZCircleCloud();

    std::vector<Triangle>* triangles = m_wormMesh->toTriangles();
    hpuint triangleCount = triangles->size();

    // resize distances array
    m_distances.resize(triangleCount);
    m_gearColor = new vector<hpcolor>;
    m_gearColor->resize(triangleCount);

    // Build kdtree
    m_kdTree = new KDTree(triangles);
}

WormGearGrind::~WormGearGrind() {
    delete m_gearColor;
    delete m_kdTree;
}


void WormGearGrind::calculateGrindingDepth(hpreal time) {
   hpmat4x4 gearModelMatrix = m_gearMovement.getMatrix(time);
   hpmat4x4 wormModelMatrix = m_wormMovement.getMatrix(time);
   std::cout << "Starting simulation:" << std::endl;

   size_t resolutionZ = m_wormCircleCloud->getResolutionZ();

   CircularSimulationResult simResult = CircularSimulationResult(m_resultAngleSlotCount, resolutionZ);

   clock_t start, end;
//   clock_t startZ, endZ;

   start = clock();
   // Compute the distance between every circle and triangle
   // TODO: Optimize this using spatial data structures
//   for (size_t z = 0; z < resolutionZ; z++) {
////       startZ = clock();
//       std::list<CircleHitResult*>* hitResults = new std::list<CircleHitResult*>;
//
//       // Check upper bound
//       computeIntersectingTriangles(z, hitResults, gearModelMatrix, wormModelMatrix);
//
//
//       // Get the intersection information and use it to color vertices
//       std::list<CircleHitResult*>::iterator pos = hitResults->begin();
//       std::list<CircleHitResult*>::iterator end = hitResults->end();
//       for (; pos != end; pos++) {
//           CircleHitResult* hitResult = *pos;
//
//           simResult.addItem(hitResult->hitPointA, z);
//           simResult.addItem(hitResult->hitPointB, z);
//
//          //TODO: Implement this function
//           std::vector<hpvec3*>* closestPoints = m_wormCircleCloud->getClosestPoints(hitResult->hitPointA);
////           std::cout << "CP size: " << closestPoints->size() << std::endl;
//
//           std::vector<hpvec3*>::iterator posCP = closestPoints->begin();
//           std::vector<hpvec3*>::iterator endCP = closestPoints->end();
//           for (; posCP != endCP; posCP++) {
//              hpvec3* closestPoint = *posCP;
//              std::cout << "HitPoint: " << hitResult->hitPointA.x << ", " << hitResult->hitPointA.y << " : " << hitResult->hitPointA.z << std::endl;
//              std::cout << "   ClosestPoint: " << closestPoint->x << ", " << closestPoint->y << " : " << closestPoint->z << std::endl;
//           }
//           delete closestPoints;
//       }
//
//       // Check whether
//       if (hitResults->size() <= 0) {
//           std::cout << "No intersect: [" << z << "]" << std::endl;
//       } else {
////        endZ = clock();
//           std::cout << "Intersect: at [" << z << "]:" << hitResults->size() << " intersections." << std::endl;
//       }
////       std::cout << "Time required for execution at z: " << (double)(endZ - startZ)/CLOCKS_PER_SEC << " seconds." << std::endl;
//       delete hitResults;
//     }

   // Print out results
//   for (size_t z = 0; z < resolutionZ; z++) {
//     for (size_t angleSlot = 0; angleSlot < m_resultAngleSlotCount; angleSlot++) {
//         float radius = simResult.getItem(angleSlot, z);
//         if (radius == INFINITY) {
//        	 radius = m_maxDistance;
//         }
//
//         std::cout << "angleSlot: " << angleSlot << ", posZ: " << z << ", radius: " << radius << std::endl;
//     }
//   }

   // Save the distance values
   for( size_t i = 0; i < m_wormMesh->getTriangleCount(); i++){
       m_distances[i] = 2 * m_maxDistance;
   }


   end = clock();
   std::cout << "Time required for execution: " << (hpreal) (end-start) / CLOCKS_PER_SEC << " seconds." << std::endl << std::endl;
   return;
}


void inline WormGearGrind::computeIntersectingTriangles(size_t& z, std::list<CircleHitResult*>* hitResults, hpmat4x4 gearModelMatrix, hpmat4x4 wormModelMatrix) {
  Circle circle = m_wormCircleCloud->computeOuterCircle(z);
  Circle transformedCircle = transformCircle(circle, gearModelMatrix, wormModelMatrix);

  m_kdTree->intersectAll(transformedCircle, hitResults);
}

hpvec3 inline WormGearGrind::transformVector(hpvec3& vector, hpmat4x4& transformation) {
  hpvec4 result = transformation * hpvec4(vector.x, vector.y, vector.z, 1.0);
  return hpvec3(result.x, result.y, result.z); //TODO: does this make sense?
}
hpvec3 inline WormGearGrind::transformPoint(hpvec3& point, hpmat4x4& transformation) {
  hpvec4 result = transformation * hpvec4(point.x, point.y, point.z, 1.0);
  return hpvec3(result.x, result.y, result.z); //TODO: does this make sense?
}

// This transform a triangle into a different the space of the circle.
// Note that normals are not transformed, since we don't use them here.
Triangle WormGearGrind::transformTriangle(Triangle& triangle, hpmat4x4 gearModelMatrix, hpmat4x4 wormModelMatrix) {
  hpmat4x4 transformation = gearModelMatrix * glm::inverse(wormModelMatrix);
  return Triangle(transformPoint(triangle.vertices[0], transformation),
                  transformPoint(triangle.vertices[1], transformation),
                  transformPoint(triangle.vertices[2], transformation));
}

// This transform a circle into the different space of the triangle.
// Note that the radius is not transformed, since we forbid scaling.
Circle WormGearGrind::transformCircle(Circle& circle, hpmat4x4 gearModelMatrix, hpmat4x4 wormModelMatrix) {
  hpmat4x4 transformation = wormModelMatrix * glm::inverse(gearModelMatrix);
  return Circle(transformPoint(circle.m_center, transformation),
                  transformVector(circle.m_normal, transformation), circle.m_radius);
}

WormGearGrindResult WormGearGrind::calculateSimulationResult(hpreal time){
    calculateGrindingDepth(time);

    // Fill color
    for( size_t i = 0; i < m_gearColor->size(); i++){
    	if( m_distances[i] >= 0 ){
    		m_gearColor->at(i) = hpcolor(0.0, m_distances[i], 1.0, 1.0);
    	}else{
            m_gearColor->at(i) = hpcolor(1.0, 1.0 + m_distances[i], 1.0 + m_distances[i], 1.0);
    	}
    }
    return WormGearGrindResult(m_gear, m_gearColor, m_gearMesh, m_gearMovement.getRigidAffineTransformation(time),  m_worm, m_wormMesh, m_wormMovement.getRigidAffineTransformation(time));
}

WormGearGrindResult WormGearGrind::getSimulationResult(hpreal time){
	map<hpreal, WormGearGrindResult>::iterator it = m_precalcResults.lower_bound(time);
	if(it == m_precalcResults.end()){
		it--;
	}
	return it->second;
}

void WormGearGrind::runSimulation() {
    // "-1.0" because 0.0 and 1.0 have to be calculated.
    hpreal deltaT = 1.0 / ((hpreal) STEP_COUNT - 1.0);
	m_precalcResults.clear();
	for( hpreal t = 0.0; t <= 1.0; t += deltaT ) {
		m_precalcResults.insert(pair<hpreal, WormGearGrindResult>(t, calculateSimulationResult(t)));
	}
}

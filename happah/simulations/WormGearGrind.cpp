#include "happah/simulations/WormGearGrind.h"
#include <glm/glm.hpp>

WormGearGrind::WormGearGrind(Worm_ptr worm, TriangleMesh_ptr wormMesh, InvoluteGear_ptr gear, TriangleMesh_ptr gearMesh)
	: m_worm(worm), m_wormMesh(wormMesh), m_gear(gear), m_gearMesh(gearMesh), m_maxDistance(1.0) {
	init(gear->getReferenceRadius());
}

WormGearGrind::WormGearGrind(Worm_ptr worm, TriangleMesh_ptr wormMesh, SimpleGear_ptr gear, hpreal gearReferenceRadius, TriangleMesh_ptr gearMesh)
	: m_worm(worm), m_wormMesh(wormMesh), m_gear(gear), m_gearMesh(gearMesh), m_maxDistance(1.0) {
	init(gearReferenceRadius);
}

void WormGearGrind::init(hpreal gearReferenceRadius) {
	hpreal rotXStart = 360.0;
	hpreal rotXEnd = 0.0;
	hpreal rotY = 90.0;

	hpreal x = m_worm->getModule() * M_PI / 4.0;
	hpreal y = m_worm->getReferenceRadius() + gearReferenceRadius / 1.5; //TODO: remove the factor
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
    m_wormCircleCloud = m_worm->toZCircleCloud();

    std::vector<Triangle>* triangles = m_wormMesh->toTriangles();
    hpuint gearVertexCount = m_gearMesh->getVertexCount();

    // resize color array
    m_gearColor = new vector<hpcolor>;
    m_gearColor->resize(gearVertexCount);

    // Build kdtree
    m_kdTree = new KDTree(triangles);
}

WormGearGrind::~WormGearGrind() {
    delete m_gearColor;
    delete m_kdTree;
}


void WormGearGrind::calculateGrindingDepth(hpreal time) {
	std::cout << "Starting simulation at time " << time << ":" << std::endl;

   hpmat4x4 gearModelMatrix = m_gearMovement.getMatrix(time);
   hpmat4x4 wormModelMatrix = m_wormMovement.getMatrix(time);



   size_t resolutionZ = m_wormCircleCloud->getResolutionZ();
   simResult = CircularSimulationResult(m_resultAngleSlotCount, resolutionZ);


   clock_t start, end;
   start = clock();

   // Compute the distance between every circle and triangle
   for (hpuint posZIdx = 0; posZIdx < resolutionZ; posZIdx++) {
       std::list<CircleHitResult*>* hitResults = new std::list<CircleHitResult*>;

       // Check upper bound
       computeIntersectingTriangles(posZIdx, hitResults, gearModelMatrix, wormModelMatrix);


       // Get the intersection information and use it to color vertices
       std::list<CircleHitResult*>::iterator pos = hitResults->begin();
       std::list<CircleHitResult*>::iterator end = hitResults->end();
       for (; pos != end; pos++) {
           CircleHitResult* hitResult = *pos;

           simResult.addItem(hitResult->hitPointA, posZIdx);
           simResult.addItem(hitResult->hitPointB, posZIdx);
       }

       // Check whether
       if (hitResults->size() <= 0) {
//           std::cout << "No intersect: [" << posZIdx << "]" << std::endl;
       } else {
           std::cout << "Intersect: at [" << posZIdx << "]:" << hitResults->size() << " intersections." << std::endl;
       }
       delete hitResults;
     }

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

   end = clock();
   std::cout << "Time required for execution: " << (hpreal) (end-start) / CLOCKS_PER_SEC << " seconds." << std::endl << std::endl;
   return;
}


void inline WormGearGrind::computeIntersectingTriangles(hpuint& posZIdx, std::list<CircleHitResult*>* hitResults, hpmat4x4 gearModelMatrix, hpmat4x4 wormModelMatrix) {
  Circle circle = m_wormCircleCloud->computeOuterCircle(posZIdx);
  Circle transformedCircle = transformCircle(circle, gearModelMatrix, wormModelMatrix);
//  LoggingUtils::print(transformedCircle);

  m_kdTree->intersectAll(transformedCircle, hitResults);

//  std::list<CircleHitResult*>::const_iterator iterator;
//  for (iterator = hitResults->begin(); iterator != hitResults->end(); ++iterator) {
//	  LoggingUtils::printVec("hitPointA", (*iterator)->hitPointA);
//	  LoggingUtils::printVec("hitPointB", (*iterator)->hitPointB);
//  }
}

hpvec3 inline WormGearGrind::transformPoint(hpvec3& point, hpmat4x4& transformation) {
  hpvec4 result = transformation * hpvec4(point.x, point.y, point.z, 1.0);
  return hpvec3(result.x, result.y, result.z);
}

// This transform a circle into the different space of the triangle.
// Note that the radius is not transformed, since we forbid scaling.
Circle WormGearGrind::transformCircle(Circle& circle, hpmat4x4 gearModelMatrix, hpmat4x4 wormModelMatrix) {
  hpmat4x4 transformation = wormModelMatrix * glm::inverse(gearModelMatrix);
  return Circle(transformPoint(circle.m_center, transformation),
                transformVector(circle.m_normal, transformation),
                circle.m_radius);
}

//// This transform a triangle into a different the space of the circle.
//// Note that normals are not transformed, since we don't use them here.
//Triangle WormGearGrind::transformTriangle(Triangle& triangle, hpmat4x4 gearModelMatrix, hpmat4x4 wormModelMatrix) {
//  hpmat4x4 transformation = gearModelMatrix * glm::inverse(wormModelMatrix);
//  return Triangle(transformPoint(triangle.vertices[0], transformation),
//                  transformPoint(triangle.vertices[1], transformation),
//                  transformPoint(triangle.vertices[2], transformation));
//}

hpvec3 inline WormGearGrind::transformVector(hpvec3& vector, hpmat4x4& transformation) {
  hpvec4 result = transformation * hpvec4(vector.x, vector.y, vector.z, 0.0);
  return hpvec3(result.x, result.y, result.z);
}



WormGearGrindResult WormGearGrind::calculateSimulationResult(hpreal time){
    calculateGrindingDepth(time);

	vector<hpvec3>* verticesAndNormals = m_gearMesh->getVerticesAndNormals();
	vector<hpuint>* indices = m_gearMesh->getIndices();

    // Fill color
    for(hpuint i = 0; i < m_gearMesh->getVertexCount(); i++){
    	hpvec3 point = verticesAndNormals->at(2 * indices->at(i));
    	hpuint posZIdx = m_wormCircleCloud->convertPosZToPosZIdx(point.z);
    	hpreal distance = simResult.getItem(point, posZIdx);
    	if (distance > m_maxDistance) distance = m_maxDistance;
//    	hpreal distanceRatio =  distance / m_maxDistance;

    	if(distance >= 0) {
    		m_gearColor->at(i) = hpcolor(0.0, distance, 1.0, 1.0);
    	} else{
            m_gearColor->at(i) = hpcolor(1.0, 1.0 + distance, 1.0 + distance, 1.0);
    	}
    }
    return WormGearGrindResult(m_gear, m_gearColor, m_gearMesh, m_gearMovement.getRigidAffineTransformation(time),
    						   m_worm, m_wormMesh, m_wormMovement.getRigidAffineTransformation(time));
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

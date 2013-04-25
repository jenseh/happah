#include "happah/simulations/WormGearGrind.h"
#include <glm/glm.hpp>


WormGearGrind::WormGearGrind(Worm_ptr worm, TriangleMesh_ptr wormMesh, InvoluteGear_ptr gear, TriangleMesh_ptr gearMesh)
	: m_worm(worm), m_wormMesh(wormMesh), m_gear(gear), m_gearMesh(gearMesh), m_maxDistance(worm->getModule() / 4.0) {
	init(gear->getReferenceRadius());
}

WormGearGrind::WormGearGrind(Worm_ptr worm, TriangleMesh_ptr wormMesh, SimpleGear_ptr gear, hpreal gearReferenceRadius, TriangleMesh_ptr gearMesh)
	: m_worm(worm), m_wormMesh(wormMesh), m_gear(gear), m_gearMesh(gearMesh), m_maxDistance(worm->getModule() / 4.0) {
	init(gearReferenceRadius);
}

void WormGearGrind::init(hpreal gearReferenceRadius) {
	hpreal rotXStart = 360.0;
	hpreal rotXEnd = 0.0;
	hpreal rotY = 90.0;

	hpreal x = -m_worm->getModule() * M_PI / 4.0; //TODO: adapt;
	hpreal y = m_worm->getReferenceRadius() + gearReferenceRadius * 0.9; //TODO: remove the factor
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
    m_wormCircleCloud = m_worm->toZCircleCloud(10);

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


CircularSimulationResult* WormGearGrind::calculateGrindingDepth(hpreal time) {
//	std::cout << "Starting simulation at time " << time << ":" << std::endl;

   hpmat4x4 gearModelMatrix = m_gearMovement.getMatrix(time);
   hpmat4x4 wormModelMatrix = m_wormMovement.getMatrix(time);



   hpuint wormResolutionZ = m_wormCircleCloud->getResolutionZ();
   hpuint gearResolutionZ = 11;
   CircularSimulationResult* simResult = new CircularSimulationResult(m_resultAngleSlotCount, 0.0, m_gear->getFaceWidth(), gearResolutionZ);


//   clock_t start, end;
//   start = clock();

   // Compute the distance between every circle and triangle
   for (hpuint wormPosZIdx = 0; wormPosZIdx < wormResolutionZ; wormPosZIdx++) {
       // Check upper bound
       computeIntersectingTriangles(wormPosZIdx, simResult, gearModelMatrix, wormModelMatrix);
     }

   // Print out results
   for (hpuint posZSlot = 0; posZSlot < gearResolutionZ; posZSlot++) {
     for (hpuint angleSlot = 0; angleSlot < m_resultAngleSlotCount; angleSlot++) {
         hpreal radius = simResult->getItem(angleSlot, posZSlot);
         if (radius != INFINITY) {
             std::cout << "angleSlot: " << angleSlot << ", posZSlot: " << posZSlot << ", radius: " << radius << std::endl;
         }
     }
   }

//   end = clock();
//   std::cout << "Time required for execution: " << (hpreal) (end-start) / CLOCKS_PER_SEC << " seconds." << std::endl << std::endl;
   return simResult;
}


void inline WormGearGrind::computeIntersectingTriangles(hpuint& wormPosZIdx, CircularSimulationResult* simResult, hpmat4x4& gearModelMatrix, hpmat4x4& wormModelMatrix) {
  // Retrieve outermost circle at current z position
  Circle circle = m_wormCircleCloud->computeOuterCircle(wormPosZIdx);

  std::list<CircleHitResult>* hitResults = new std::list<CircleHitResult>;

//  LoggingUtils::print("circle", circle);

  // Transform circle from worm coordinates to gear coordinates
  Circle transformedCircle = transformCircle(circle, gearModelMatrix, wormModelMatrix);

//  LoggingUtils::print("transformedCircle", transformedCircle); //TODO: circles seem to be correct in gear coordinates

  // Find all intersections between circle and triangles
  m_kdTree->intersectAll(transformedCircle, hitResults);

  // Transform intersection points from gear coordinates to worm coordinates //TODO: change
  hpmat4x4 transformation = hpmat4x4();//gearModelMatrix;// //glm::inverse(wormModelMatrix) * gearModelMatrix; //TODO: Check whether the matrices are valid

  // Transform result coordinates back to world
  std::list<CircleHitResult>::iterator iterator;
  for (iterator = hitResults->begin(); iterator != hitResults->end(); ++iterator) {
//	  LoggingUtils::printVec("hitPointA", iterator->hitPointA);
//	  LoggingUtils::printVec("hitPointB", iterator->hitPointB);
	  hpvec3 pointA = (*iterator).hitPointA;
	  hpvec3 pointB = (*iterator).hitPointB;

	  pointA = transformPoint(pointA, transformation);
	  pointB = transformPoint(pointB, transformation);
//	  LoggingUtils::printVec("hitPointA", iterator->hitPointA); //TODO: Result points seem to be okay
//	  LoggingUtils::printVec("hitPointB", iterator->hitPointB);
//	  std::cout << "-----------" << std::endl;
      simResult->addItem(pointA);
      simResult->addItem(pointB);
  }

  // Check whether
  if (hitResults->size() <= 0) {
      std::cout << "No intersect: [" << wormPosZIdx << "]" << std::endl;
  } else {
      std::cout << "Intersect: at [" << wormPosZIdx << "]: " << hitResults->size() << " intersections." << std::endl;
  }

  // Cleanup
  delete hitResults;
}

hpvec3 inline WormGearGrind::transformPoint(hpvec3& point, hpmat4x4& transformation) {
  hpvec4 result = transformation * hpvec4(point.x, point.y, point.z, 1.0);
  return hpvec3(result.x, result.y, result.z);
}

// This transform a circle from worm coordinates to gear coordinates.
// Note that the radius is not transformed, since we forbid scaling.
Circle WormGearGrind::transformCircle(Circle& circle, hpmat4x4& gearModelMatrix, hpmat4x4& wormModelMatrix) {
  hpmat4x4 transformation = glm::inverse(gearModelMatrix) * wormModelMatrix;
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
	CircularSimulationResult* simResult = calculateGrindingDepth(time);

	vector<hpvec3>* verticesAndNormals = m_gearMesh->getVerticesAndNormals();
	vector<hpuint>* indices = m_gearMesh->getIndices();

//	hpmat4x4 gearModelMatrix = m_gearMovement.getMatrix(time);
//	hpmat4x4 wormModelMatrix = m_wormMovement.getMatrix(time);
	hpmat4x4 transformation = hpmat4x4(); //glm::inverse(wormModelMatrix) * gearModelMatrix; //TODO:dont

    // Fill color
    for(hpuint i = 0; i < m_gearMesh->getVertexCount(); i++){
    	// Transform current point from gear coordinates to worm coordinates//TODO:dont
    	hpvec3 point = transformPoint(verticesAndNormals->at(2 * indices->at(i)), transformation);

		hpreal resultRadius = simResult->getItem(point);
		hpreal currentRadius = simResult->computeRadiusXY(point); // TODO: dont use currentradius
		hpreal distance = currentRadius - resultRadius;

//			hpreal distance = resultRadius;
//			if (resultRadius != INFINITY) {
//				std::cout << resultRadius << " " << currentRadius << " " << distance << std::endl;
//			}

		if (distance > m_maxDistance) distance = m_maxDistance;
		else if (distance < -m_maxDistance) distance = -m_maxDistance;
		hpreal distanceRatio =  distance / m_maxDistance;

//	    	std::cout << "ratio: " << distanceRatio  << std::endl;

		if(distance >= 0) {
			m_gearColor->at(i) = hpcolor(0.0, 0.5 * distanceRatio, 1.0 - distanceRatio, 1.0);
		} else {
			m_gearColor->at(i) = hpcolor(1.0 + distanceRatio, 0.5 * -distanceRatio, 0.0, 1.0);
		}
    }

    delete simResult;
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

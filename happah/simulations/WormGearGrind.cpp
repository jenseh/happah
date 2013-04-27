#include "happah/simulations/WormGearGrind.h"
#include <glm/glm.hpp>


//WormGearGrind::WormGearGrind(Worm_ptr worm, TriangleMesh_ptr wormMesh, InvoluteGear_ptr gear, TriangleMesh_ptr gearMesh)
//	: m_worm(worm), m_wormMesh(wormMesh), m_gear(gear), m_gearMesh(gearMesh), m_maxDistance(worm->getModule() / 4.0) {
//	init(gear->getReferenceRadius());
//}

WormGearGrind::WormGearGrind(Worm_ptr worm, TriangleMesh_ptr wormMesh, SimpleGear_ptr gear, hpreal gearReferenceRadius, TriangleMesh_ptr gearMesh)
	: m_worm(worm), m_wormMesh(wormMesh), m_gear(gear), m_gearMesh(gearMesh), m_maxDistance(worm->getModule()) {
	init(gearReferenceRadius);
}

void WormGearGrind::init(hpreal gearReferenceRadius) {
	hpreal rotXStart = 360.0;
	hpreal rotXEnd = 0.0;
	hpreal rotY = 90.0;

	hpreal x = m_worm->getModule() * M_PI / 4.0;
	hpreal y = m_worm->getReferenceRadius() + gearReferenceRadius; //TODO:remove this * 0.8
	hpvec3 position = hpvec3(x, y, 0.0);

    m_wormMovement = Kinematic(
    		Polynom<double>(1, position.x),
    		Polynom<double>(1, position.y),
    		Polynom<double>(1, position.z),
    		Polynom<double>(2, rotXStart, rotXEnd-rotXStart), //TODO: undo this //
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
    		Polynom<double>(2, rotZStart, rotZEnd-rotZStart));	//TODO: undo this Polynom<double>(0));//

    // Convert to right representation
    m_gearCircleCloud = m_gear->toZCircleCloud(m_resultPosZSlotCount);

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
   hpmat4x4 gearModelMatrix = m_gearMovement.getMatrix(time);
   hpmat4x4 wormModelMatrix = m_wormMovement.getMatrix(time);

   hpuint gearResolutionZ = m_gearCircleCloud->getResolutionZ();
   CircularSimulationResult* simResult = new CircularSimulationResult(m_resultAngleSlotCount, 0.0, m_gear->getFaceWidth(), gearResolutionZ);

   // Compute the distance between every circle and triangle
   for (hpuint gearPosZIdx = 0; gearPosZIdx < gearResolutionZ; gearPosZIdx++) {
       // Check upper bound
       computeIntersectingTriangles(gearPosZIdx, simResult, gearModelMatrix, wormModelMatrix, time);
   }

   // Print out results
//   for (hpuint posZSlot = 0; posZSlot < simResult->getResolutionZ(); posZSlot++) {
//     for (hpuint angleSlot = 0; angleSlot < m_resultAngleSlotCount; angleSlot++) {
//         hpreal radius = simResult->getItem(angleSlot, posZSlot);
//         if (radius != INFINITY) {
//             std::cout << "angleSlot: " << angleSlot << ", posZSlot: " << posZSlot << ", radius: " << radius << std::endl;
//         }
//     }
//   }

   return simResult;
}


void WormGearGrind::computeIntersectingTriangles(hpuint& gearPosZIdx, CircularSimulationResult* simResult, hpmat4x4& gearModelMatrix, hpmat4x4& wormModelMatrix, hpreal& time) {
  // Retrieve outermost circle at current z position
  Circle circle = m_gearCircleCloud->computeOuterCircle(gearPosZIdx);

  std::list<CircleHitResult>* hitResults = new std::list<CircleHitResult>;

  hpmat4x4 transform = glm::inverse(wormModelMatrix) * gearModelMatrix;

  // Transform circle from worm coordinates to gear coordinates
  Circle transformedCircle = transformCircle(circle, transform);

  // Find all intersections between circle and triangles
  m_kdTree->intersectAll(transformedCircle, hitResults);

  hpmat4x4 backTransform = glm::inverse(gearModelMatrix) * wormModelMatrix;

  int relevantHitCount = 0;

  // Transform result coordinates back to world
  std::list<CircleHitResult>::iterator iterator;
  for (iterator = hitResults->begin(); iterator != hitResults->end(); ++iterator) {
	  hpvec3 pointA = (*iterator).hitPointA;
	  hpvec3 pointB = (*iterator).hitPointB;

	  pointA = transformPoint(pointA, backTransform);
	  pointB = transformPoint(pointB, backTransform);

	  // Realign values to z plane
	  hpreal pushDistanceA = abs(pointA.z - circle.m_center.z);
	  hpreal pushDistanceB = abs(pointB.z - circle.m_center.z);

	  if (pushDistanceA > 0.3) continue;
	  if (pushDistanceB > 0.3) continue;

	  pointA.z = circle.m_center.z;
	  pointB.z = circle.m_center.z;

      bool addedA = simResult->addItem(pointA);
      bool addedB = simResult->addItem(pointB);

      if (addedA) relevantHitCount++;
      if (addedB) relevantHitCount++;
  }

  // Debug: to be removed
//  if (hitResults->size() != 0) {
//	  std::cout << "Intersect: " << gearPosZIdx << " relevant: " << relevantHitCount << " time: " << time << " intersections: " << hitResults->size() * 2 << std::endl;
//  }

  // Cleanup
  delete hitResults;
}

// This transform a circle from worm coordinates to gear coordinates.
// Note that the radius is not transformed, since we forbid scaling.
Circle WormGearGrind::transformCircle(Circle& circle, hpmat4x4 transformation) {
  return Circle(transformPoint(circle.m_center, transformation),
                transformVector(circle.m_normal, transformation),
                circle.m_radius);
}

hpvec3 WormGearGrind::transformPoint(hpvec3& point, hpmat4x4& transformation) {
  hpvec4 result = transformation * hpvec4(point.x, point.y, point.z, 1.0);
  return hpvec3(result.x, result.y, result.z);
}

hpvec3 WormGearGrind::transformVector(hpvec3& vector, hpmat4x4& transformation) {
  hpvec4 result = transformation * hpvec4(vector.x, vector.y, vector.z, 0.0);
  return hpvec3(result.x, result.y, result.z);
}



WormGearGrindResult WormGearGrind::calculateSimulationResult(hpreal time){
	CircularSimulationResult* simResult = calculateGrindingDepth(time);

	vector<hpvec3>* verticesAndNormals = m_gearMesh->getVerticesAndNormals();

    // Fill color
    for(hpuint i = 0; i < verticesAndNormals->size()/2; i++){
    	hpvec3 point = verticesAndNormals->at(2*i);

//    	hpmat4x4 transformation = glm::inverse(m_gearMovement.getMatrix(time));
//    	point = transformPoint(point, transformation);

		hpreal resultRadius = simResult->getItem(point);
		hpreal currentRadius = simResult->computeRadiusXY(point);
		hpreal distance = currentRadius - resultRadius;

		bool exists = resultRadius != INFINITY;

		hpreal maxRadius = m_gearCircleCloud->getMaxRadius();
		hpreal distanceRatio;

		if (distance > m_maxDistance) distance = m_maxDistance;
		else if (distance < -m_maxDistance) distance = -m_maxDistance;

		if (distance >= 0) {
			distanceRatio = distance / m_maxDistance;
		} else {
			distanceRatio = distance / m_maxDistance;
		}

//		if (!exists) {
//			m_gearColor->at(i) = hpcolor(0.0, 1.0, 0.0, 1.0);
//		} else {
//			m_gearColor->at(i) = hpcolor(0.0, 0.0, 1.0, 1.0);
//		}

//		if (!exists) {
//			m_gearColor->at(i) = hpcolor(0.0, 1.0, 0.0, 1.0);
//		} else if (distanceRatio >= 0) {
//			m_gearColor->at(i) = hpcolor(0.0, 0.0, distanceRatio>=0, 1.0);
//		} else {
//			m_gearColor->at(i) = hpcolor(distanceRatio<0, 0.0, 0.0, 1.0);
//		}

		if (!exists) {
			m_gearColor->at(i) = hpcolor(0.0, 0.5, 0.0, 1.0);
		} else if (distanceRatio >= 0) {
			m_gearColor->at(i) = hpcolor(0.0, 0.5 * distanceRatio, 1.0 - distanceRatio, 1.0);
		} else {
			m_gearColor->at(i) = hpcolor(-distanceRatio, 0.5 * (1.0+distanceRatio), 0.0, 1.0);
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

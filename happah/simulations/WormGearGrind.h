#ifndef WORMGEARGRIND_H
#define WORMGEARGRIND_H

#include <time.h>

#include "happah/HappahTypes.h"
#include "happah/geometries/gears/InvoluteGear.h"
#include "happah/geometries/gears/Worm.h"
#include "happah/geometries/ZCircleCloud.h"
#include "happah/kdtree/KDTree.h"
#include "happah/math/Circle.h"
#include "happah/math/Triangle.h"
#include "happah/simulations/CircularSimulationResult.h"
#include "happah/transformations/RigidAffineTransformation.h"

class WormGearGrind
{
public:
  WormGearGrind(Worm& worm, InvoluteGear& gear, RigidAffineTransformation& wormTransformation, RigidAffineTransformation& gearTransformation);
  ~WormGearGrind();

  void runSimulation();
  void calculateGrindingDepth();

private:
  hpvec3 inline transformVector(hpvec3& vector, hpmat4x4& transformation);
  hpvec3 inline transformPoint(hpvec3& point, hpmat4x4& transformation);
  void inline computeIntersectingTriangles(size_t& z, KDTree& tree, std::list<CircleHitResult*>* hitResults);


  Triangle translateTriangle(Triangle& triangle, hpvec3& vector);

public:
  Triangle transformTriangle(Triangle& triangle);
  Circle transformCircle(Circle& circle);

private:
  ZCircleCloud* m_worm;
  TriangleMesh* m_gearMesh;

  hpmat4x4 m_wormModelMatrix;
  hpmat4x4 m_gearModelMatrix;

  constexpr static size_t m_resultAngleSlotCount = 100;
  constexpr static hpreal MAX_DIST = 1.0;
};

#endif // WORMGEARGRIND_H

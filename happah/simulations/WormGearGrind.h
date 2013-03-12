#ifndef WORMGEARGRIND_H
#define WORMGEARGRIND_H

#include "happah/HappahTypes.h"
#include "happah/geometries/InvoluteGear.h"
#include "happah/geometries/ZCircleCloud.h"
#include "happah/kdtree/ExplicitKDTree.h"
#include "happah/math/Circle.h"
#include "happah/math/Triangle.h"
#include "happah/simulations/CircularSimulationResult.h"

class WormGearGrind
{
public:
  WormGearGrind(InvoluteGear& worm, InvoluteGear& gear);
  ~WormGearGrind();

  void runSimulation();
  void calculateGrindingDepth();

private:
  hpvec3 inline transformVector(hpvec3& vector, hpmat4x4& transformation);
  hpvec3 inline transformPoint(hpvec3& point, hpmat4x4& transformation);
  void inline computeIntersectingTriangles(size_t& z, ExplicitKDTree& tree, std::list<CircleHitResult*>* hitResults);


  Triangle translateTriangle(Triangle& triangle, hpvec3& vector);

public:
  Triangle transformTriangle(Triangle& triangle);
  Circle transformCircle(Circle& circle);

private:
  ZCircleCloud* m_worm;
  TriangleMesh* m_gear;

  constexpr static hpreal MAX_DIST = 1.0f;
};

#endif // WORMGEARGRIND_H

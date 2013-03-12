#ifndef WORMGEARGRIND_H
#define WORMGEARGRIND_H

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
  glm::vec3 inline transformVector(glm::vec3& vector, QMatrix4x4& transformation);
  glm::vec3 inline transformPoint(glm::vec3& point, QMatrix4x4& transformation);
  void inline computeIntersectingTriangles(size_t& z, KDTree& tree, std::list<CircleHitResult*>* hitResults);


  Triangle translateTriangle(Triangle& triangle, glm::vec3& vector);

public:
  Triangle transformTriangle(Triangle& triangle);
  Circle transformCircle(Circle& circle);

private:
  ZCircleCloud* m_worm;
  TriangleMesh* m_gear;

  constexpr static float MAX_DIST = 1.0f;
};

#endif // WORMGEARGRIND_H

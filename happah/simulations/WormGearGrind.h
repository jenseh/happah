#ifndef WORMGEARGRIND_H
#define WORMGEARGRIND_H

#include "happah/geometries/InvoluteSpurGear.h"
#include "happah/kdtree/ExplicitKDTree.h"
#include "happah/models/ZCircleCloud.h"
#include "happah/primitives/Circle.h"
#include "happah/primitives/Triangle.h"
#include "happah/simulations/CircularSimulationResult.h"

class WormGearGrind
{
public:
  WormGearGrind(InvoluteSpurGear& worm, InvoluteSpurGear& gear);
  ~WormGearGrind();

  void runSimulation();
  void calculateGrindingDepth();

private:
  glm::vec3 inline transformVector(glm::vec3& vector, QMatrix4x4& transformation);
  glm::vec3 inline transformPoint(glm::vec3& point, QMatrix4x4& transformation);
  void inline computeIntersectingTriangles(size_t& z, ExplicitKDTree& tree, std::list<CircleHitResult*>* hitResults);


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

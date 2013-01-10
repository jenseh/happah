#ifndef WORMGEARGRIND_H
#define WORMGEARGRIND_H

#include "../geometries/SpurGear.h"
#include "../primitives/Circle.h"
#include "../primitives/Triangle.h"

class WormGearGrind
{
public:
  WormGearGrind(SpurGear& worm, SpurGear& gear);
  ~WormGearGrind();

  void runSimulation();
  void calculateGrindingDepth();

private:
  glm::vec3 inline transformVector(glm::vec3& vector, QMatrix4x4& transformation);
  glm::vec3 inline transformPoint(glm::vec3& point, QMatrix4x4& transformation);
  bool inline checkIntersection(int& xy, size_t& resolutionXY, size_t& z, std::vector<Circle*>& circles, std::vector<Triangle*>& triangles);
  void inline computeIntersectingTriangles(int& xy, size_t& resolutionXY, size_t& z, std::vector<Circle*>& circles, std::vector<Triangle*>& triangles, std::list<Triangle*>& hits);
  bool inline reduceIntersectingTriangles(int& xy, size_t& resolutionXY, size_t& z, std::vector<Circle*>& circles, std::list<Triangle*>& hits);
  bool inline reduceNonIntersectingTriangles(int& xy, size_t& resolutionXY, size_t& z, std::vector<Circle*>& circles, std::list<Triangle*>& hits);

public:
  Triangle transformTriangle(Triangle& triangle);
  Circle transformCircle(Circle& circle);

private:
  SpurGear& m_worm;
  SpurGear& m_gear;

  const static float MAX_DIST = 1.0f;
};

#endif // WORMGEARGRIND_H

#include "happah/geometries/CircleCloud.h"

CircleCloud::CircleCloud(std::vector<Circle*> circles, size_t resolutionXY, size_t resolutionZ)
  : m_circles(circles), m_resolutionXY(resolutionXY), m_resolutionZ(resolutionZ)
{}


std::vector<Circle*>& CircleCloud::getCircles() {
  return m_circles;
}


size_t CircleCloud::getResolutionXY() {
  return m_resolutionXY;
}

size_t CircleCloud::getResolutionZ() {
  return m_resolutionZ;
}

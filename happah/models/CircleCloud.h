#ifndef CIRCLECLOUD_H
#define CIRCLECLOUD_H

#include <vector>

#include "happah/primitives/Circle.h"

class CircleCloud
{
public:
  CircleCloud(std::vector<Circle*> circles, size_t resolutionXY, size_t resolutionZ);

  std::vector<Circle*>& getCircles();
  size_t getResolutionXY();
  size_t getResolutionZ();
private:
  std::vector<Circle*> m_circles;

  size_t m_resolutionXY;
  size_t m_resolutionZ;
};
#endif // CIRCLECLOUD_H

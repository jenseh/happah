#include "CircleCloud.h"

CircleCloud::CircleCloud(std::vector<Circle*> circles)
{
   m_circles = circles;
}


std::vector<Circle*>* CircleCloud::getCircles() {
  return &m_circles;
}

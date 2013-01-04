#ifndef CIRCLECLOUD_H
#define CIRCLECLOUD_H


#include <vector>
#include "../primitives/Circle.h"

class CircleCloud
{
public:
  CircleCloud(std::vector<Circle*> circles);

  std::vector<Circle*>* getCircles();
private:
  std::vector<Circle*> m_circles;
};
#endif // CIRCLECLOUD_H

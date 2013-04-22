#ifndef BBOX_H
#define BBOX_H

#include <glm/glm.hpp>
#include <vector>
#include "happah/math/Triangle.h"
#include "happah/HappahTypes.h"

class BBox
{
public:
  BBox();
  BBox(hpvec3 min, hpvec3 max);

  void addTriangle(Triangle& t);
  bool intersects(BBox& other);
  //std::vector<BBox*> split(int axis, float axisValue);
  hpvec3* getMin();
  void setMin(hpvec3 min);
  hpvec3* getMax();
  void setMax(hpvec3 max);

private:
  hpvec3 m_min;
  hpvec3 m_max;
};

#endif // BBOX_H

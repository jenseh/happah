#ifndef BBOX_H
#define BBOX_H

#include <glm/glm.hpp>

class BBox
{
public:
  BBox(glm::vec3 min, glm::vec3 max);

  bool intersects(BBox* other);
  BBox* split(int axis, float axisValue);
  glm::vec3* getMin();
  void setMin(glm::vec3 min);
  glm::vec3* getMax();
  void setMax(glm::vec3 max);

private:
  glm::vec3 m_min;
  glm::vec3 m_max;
};

#endif // BBOX_H

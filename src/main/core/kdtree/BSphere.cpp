#include "BSphere.h"

BSphere::BSphere(glm::vec3 center, float radius)
{
  m_center = center;
  m_radius = radius;
}




glm::vec3* BSphere::getCenter() {
  return &m_center;
}

float BSphere::getRadius() {
  return m_radius;
}

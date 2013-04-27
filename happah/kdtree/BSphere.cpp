#include "happah/kdtree/BSphere.h"

BSphere::BSphere(hpvec3 center, hpreal radius)
{
  m_center = center;
  m_radius = radius;
}

hpvec3* BSphere::getCenter() {
  return &m_center;
}

hpreal BSphere::getRadius() {
  return m_radius;
}

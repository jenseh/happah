#ifndef BSPHERE_H
#define BSPHERE_H

#include <glm/glm.hpp>

class BSphere
{
public:
  BSphere(glm::vec3 center, float radius);

  glm::vec3* getCenter();
  float getRadius();

private:
  glm::vec3 m_center;
  float m_radius;
};

#endif // BSPHERE_H

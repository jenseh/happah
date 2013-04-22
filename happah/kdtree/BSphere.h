#ifndef BSPHERE_H
#define BSPHERE_H

#include <glm/glm.hpp>
#include "happah/HappahTypes.h"

class BSphere
{
public:
  BSphere(hpvec3 center, hpreal radius);

  hpvec3* getCenter();
  hpreal getRadius();

private:
  hpvec3 m_center;
  hpreal m_radius;
};

#endif // BSPHERE_H

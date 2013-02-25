#ifndef RAYCLOUD_H
#define RAYCLOUD_H

#include <vector>

#include "happah/primitives/Ray.h"

class RayCloud
{
public:
  RayCloud(std::vector<Ray*> rays);

  std::vector<Ray*>* getRays();
private:
  std::vector<Ray*> m_rays;
};

#endif // RAYCLOUD_H

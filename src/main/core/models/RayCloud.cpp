#include "RayCloud.h"

RayCloud::RayCloud(std::vector<Ray*> rays)
{
   m_rays = rays;
}


std::vector<Ray*>* RayCloud::getRays() {
  return &m_rays;
}

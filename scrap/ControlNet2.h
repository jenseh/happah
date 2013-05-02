#ifndef CONTROLNET2_H
#define CONTROLNET2_H

#include <math.h>
#include <glm/glm.hpp>
#include "happah/geometries/Mesh.h"


class ControlNet2 {
public:
  ControlNet2(hpvec3 p200,hpvec3 p110,hpvec3 p101,hpvec3 p020,hpvec3 p011,hpvec3 p002);
  ~ControlNet2();
  TriangleMesh* toTriangleMesh();

private:
  hpvec3 m_controlPoints[6];
  std::vector<hpvec4>m_verticesAndNormals;

};

#endif // CONTROLNET2_H

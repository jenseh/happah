#ifndef CONTROLNET2_H
#define CONTROLNET2_H

#include <math.h>
#include <glm/glm.hpp>
#include "happah/geometries/TriangleMesh.h"


class ControlNet2 {
public:
  ControlNet2(glm::vec3 p200,glm::vec3 p110,glm::vec3 p101,glm::vec3 p020,glm::vec3 p011,glm::vec3 p002);
  ~ControlNet2();
  TriangleMesh* toTriangleMesh();

private:
  glm::vec3 m_controlPoints[6];
  std::vector<glm::vec4>m_verticesAndNormals;

};

#endif // CONTROLNET2_H

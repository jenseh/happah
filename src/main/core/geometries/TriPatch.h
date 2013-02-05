#ifndef TRIPATCH_H
#define TRIPATCH_H

#include <math.h>
#include <glm/glm.hpp>
#include "NonDrawable.h"
#include "../models/TriangleMesh.h"

class TriPatch: public NonDrawable {

public:
  // TODO : Add normals
  TriPatch(int degree, glm::vec3 a, glm::vec3 b, glm::vec3 c);
  ~TriPatch();
  TriangleMesh* toTriangleMesh();
  void setControlPoint(int index,glm::vec3 value);
  void update();
  glm::vec3 getControlPoint(int index);

private:
  int m_degree,m_detail;
  float m_u,m_v,m_w;

  glm::vec3 m_a,m_b,m_c;
  glm::vec3 m_controlPoints[10];
  std::vector<glm::vec4> m_vertexData;
  glm::vec3 triPatch1(glm::vec3 p100,glm::vec3 p010,glm::vec3 p001);
  glm::vec3 triPatch2(glm::vec3 p200,glm::vec3 p110,glm::vec3 p101,glm::vec3 p020,glm::vec3 p011,glm::vec3 p002);
  glm::vec3 triPatch3(glm::vec3 p300,glm::vec3 p210,glm::vec3 p201,glm::vec3 p120,glm::vec3 p111,
                      glm::vec3 p102,glm::vec3 p030,glm::vec3 p021,glm::vec3 p012,glm::vec3 p003);
  void generateControlPoints();

};

#endif // TRIPATCH_H

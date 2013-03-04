#ifndef SPHEREPATCH_H
#define SPHEREPATCH_H


#include <math.h>
#include <glm/glm.hpp>
#include "happah/geometries/TriangleMesh.h"

class SpherePatch: public NonDrawable
{
public:
  SpherePatch(int degree, glm::vec3 a, glm::vec3 b, glm::vec3 c);
  TriangleMesh* toTriangleMesh();
  //void setControlPoint(int index,glm::vec3 value);
  //void update();
  //glm::vec3 getControlPoint(int index);


private:
  int m_degree,m_detail;
  float m_u,m_v,m_w,m_radius;
  glm::vec3 m_center;
  glm::vec3 m_a,m_b,m_c,m,m_sa,m_sb,m_sc;
  glm::vec3 m_controlPoints[10];
  glm::vec3 m_secantTriPoints[10];
  std::vector<glm::vec4> m_vertexData;
  glm::vec3 triPatch1(glm::vec3 p100,glm::vec3 p010,glm::vec3 p001);
  glm::vec3 triPatch2(glm::vec3 p200,glm::vec3 p110,glm::vec3 p101,glm::vec3 p020,glm::vec3 p011,glm::vec3 p002);
  glm::vec3 triPatch3(glm::vec3 p300,glm::vec3 p210,glm::vec3 p201,glm::vec3 p120,glm::vec3 p111,
                      glm::vec3 p102,glm::vec3 p030,glm::vec3 p021,glm::vec3 p012,glm::vec3 p003);
  void uDivideTriangle();
  void buildSecantTriangle(glm::vec3 a,glm::vec3 b,glm::vec3 c);
  bool intersectTriangle(glm::vec3 p,glm::vec3 a,glm::vec3 b,glm::vec3 c,glm::vec3*hit);
};

#endif // SPHEREPATCH_H

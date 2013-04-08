#ifndef SPHEREPATCH_H
#define SPHEREPATCH_H


#include <math.h>
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include "happah/geometries/Mesh.h"
#include "happah/HappahTypes.h"
#include "happah/geometries/Geometry.h"

class SpherePatch;
typedef shared_ptr<SpherePatch> SpherePatch_ptr;

class SpherePatch: public Geometry  {
public:
  SpherePatch(int degree, hpvec3 a, hpvec3 b, hpvec3 c);
  TriangleMesh* toTriangleMesh();
  //void setControlPoint(int index,hpvec3 value);
  //void update();
  //hpvec3 getControlPoint(int index);
  void handleSelection(){}
  void handleSelection(int pointIndex){}

private:
  int m_degree,m_detail;
  float m_u,m_v,m_w,m_radius;
  hpvec3 m_center;
  hpvec3 m_a,m_b,m_c,m,m_sa,m_sb,m_sc;
  hpvec3 m_controlPoints[10];
  hpvec3 m_secantTriPoints[10];
  std::vector<hpvec3> m_vertexData;
  hpvec3 triPatch1(hpvec3 p100,hpvec3 p010,hpvec3 p001);
  hpvec3 triPatch2(hpvec3 p200,hpvec3 p110,hpvec3 p101,hpvec3 p020,hpvec3 p011,hpvec3 p002);
  hpvec3 triPatch3(hpvec3 p300,hpvec3 p210,hpvec3 p201,hpvec3 p120,hpvec3 p111,
                      hpvec3 p102,hpvec3 p030,hpvec3 p021,hpvec3 p012,hpvec3 p003);
  void uDivideTriangle();
  void buildSecantTriangle(hpvec3 a,hpvec3 b,hpvec3 c);
  bool intersectTriangle(hpvec3 p,hpvec3 a,hpvec3 b,hpvec3 c,hpvec3*hit);
};

#endif // SPHEREPATCH_H

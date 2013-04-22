#include "happah/geometries/ControlNet2.h"

ControlNet2::ControlNet2(hpvec3 p200,hpvec3 p110,hpvec3 p101,hpvec3 p020,hpvec3 p011,hpvec3 p002){
  m_controlPoints[0]= p200;
  m_controlPoints[1]= p110;
  m_controlPoints[2]= p101;
  m_controlPoints[3]= p020;
  m_controlPoints[4]= p011;
  m_controlPoints[5]= p002;
}

ControlNet2::~ControlNet2(){

}

TriangleMesh* ControlNet2::toTriangleMesh(){
  std::vector<hpvec4> *triangles = new std::vector<hpvec4>();
  for(int i=0 ; i < 6 ; i++){
      hpvec3 cp = (m_controlPoints[i]);
      hpvec3 cp1 = cp - hpvec3(0.03f,0.0f,0.0f);
      hpvec3 cp2 = cp + hpvec3(0.03f,0.0f,0.0f);
      hpvec3 cp3 = cp + hpvec3(0.0f,0.03,0.0f);

      triangles->push_back(hpvec4(cp1,1.0f));
      triangles->push_back(hpvec4(cp,0.0f));

      triangles->push_back(hpvec4(cp2,1.0f));
      triangles->push_back(hpvec4(cp,0.0f));

      triangles->push_back(hpvec4(cp3,1.0f));
      triangles->push_back(hpvec4(cp,0.0f));

    }
  std::vector<hpuint>* indices;

  TriangleMesh* result = new TriangleMesh(triangles, indices);

  return result;
}

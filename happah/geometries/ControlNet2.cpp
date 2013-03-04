#include "happah/geometries/ControlNet2.h"

ControlNet2::ControlNet2(glm::vec3 p200,glm::vec3 p110,glm::vec3 p101,glm::vec3 p020,glm::vec3 p011,glm::vec3 p002, std::string name):NonDrawable(name)
{
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
  std::vector<glm::vec4> *triangles = new std::vector<glm::vec4>();
  for(int i=0 ; i < 6 ; i++){
      glm::vec3 cp = (m_controlPoints[i]);
      glm::vec3 cp1 = cp - glm::vec3(0.03f,0.0f,0.0f);
      glm::vec3 cp2 = cp + glm::vec3(0.03f,0.0f,0.0f);
      glm::vec3 cp3 = cp + glm::vec3(0.0f,0.03,0.0f);

      triangles->push_back(glm::vec4(cp1,1.0f));
      triangles->push_back(glm::vec4(cp,0.0f));

      triangles->push_back(glm::vec4(cp2,1.0f));
      triangles->push_back(glm::vec4(cp,0.0f));

      triangles->push_back(glm::vec4(cp3,1.0f));
      triangles->push_back(glm::vec4(cp,0.0f));

    }
  std::vector<hpuint>* indices;

  TriangleMesh* result = new TriangleMesh(triangles, indices);

  return result;
}

#include "happah/geometries/TriPatch.h"
#include <glm/glm.hpp>
#include <iostream>

TriPatch::TriPatch(int degree, glm::vec3 a, glm::vec3 b, glm::vec3 c, std::string name)
{
  m_degree = degree;
  m_a = a;
  m_b = b;
  m_c = c;
  m_u = 0.5f;
  m_v = 0.3f;
  m_w = 0.2f;
  glm::vec3 p000;
  m_detail = 100;
  int n=m_detail;
  glm::vec3 center =glm::vec3(0.0f);
  float radius = 1.0f;
  switch(m_degree){

    case(1):
      generateControlPoints();

                p000 = triPatch1(m_controlPoints[0],m_controlPoints[1],m_controlPoints[2]);
                std::cout << "BezierPunkt: "<< p000.x << "/" << p000.y << "/" <<p000.z << endl;
                m_vertexData.push_back(glm::vec4(p000,1.0f));
                m_vertexData.push_back(glm::vec4(0.0f,1.0f,0.0f,0.0f));

      break;
    case(2):
      generateControlPoints();
      for(int i=n; i>=0;i--){
          for(int j=n-i; j>=0; j--){
              for(int k=n-i-j;k>=0; k--){
                  if( i == 0 && j==0 && k==0)
                    break;
                  if((i+j+k)!=n)
                    break;
                  m_u = (float)i/(float)n;
                  m_v = (float)j/(float)n;
                  m_w = (float)k/(float)n;
                 p000 = triPatch2(m_controlPoints[0],m_controlPoints[1],m_controlPoints[2],m_controlPoints[3],m_controlPoints[4],m_controlPoints[5]);
                 //spherealize
                 glm::vec3 pot= (m_u*m_a)+(m_v*m_b)+(m_w*m_c);
                 pot = pot - center;
                 float offset = radius -glm::length(pot);
                 glm::vec3 offsetVector = glm::normalize(p000);
                 offsetVector = offset*offsetVector;
                 p000 = p000+offsetVector;
                 std::cout<<"u/v/w"<<" "<<m_u<<"/"<<m_v<<"/"<<m_w<<endl;
                 //std::cout << "BezierPunkt: "<< p000.x << "/" << p000.y << "/" <<p000.z << endl;
                 m_vertexData.push_back(glm::vec4(p000,1.0f));
                 glm::vec3 normal = (p000-center);
                 m_vertexData.push_back(glm::vec4(normal,0.0f));
                }
            }
        }

      break;
      default:
      std::cout << "Zu Hoher Grad" <<endl;
      break;
    }

}

 TriPatch::~TriPatch(){
}

void TriPatch::generateControlPoints(){
  if (m_degree == 1){
      m_controlPoints[0]= m_a;
      m_controlPoints[1]= m_b;
      m_controlPoints[2]= m_c;
    }
  if (m_degree == 2){
      m_controlPoints[0]=m_a;
      m_controlPoints[1]=m_a+((m_b-m_a)/2.0f);
      m_controlPoints[2]=m_a+((m_c-m_a)/2.0f);
      m_controlPoints[3]=m_b;
      m_controlPoints[4]=m_b+((m_c-m_b)/2.0f);
      m_controlPoints[5]=m_c;
      for (int i=0; i<6; i++){
          std::cout << "CP" << i << ": "<< m_controlPoints[i].x <<"/"<< m_controlPoints[i].y<<"/" << m_controlPoints[i].z << endl;
        }
     }
}

glm::vec3 TriPatch::triPatch1(glm::vec3 p100,glm::vec3 p010,glm::vec3 p001){
 return  m_u*p100+m_v*p010+m_w*p001;
}

glm::vec3 TriPatch::triPatch2(glm::vec3 p200,glm::vec3 p110,glm::vec3 p101,glm::vec3 p020,glm::vec3 p011,glm::vec3 p002){
  return triPatch1(triPatch1(p200,p110,p101),triPatch1(p110,p020,p011),triPatch1(p101,p011,p002));
}

glm::vec3 TriPatch::triPatch3(glm::vec3 p300,glm::vec3 p210,glm::vec3 p201,glm::vec3 p120,glm::vec3 p111,
                    glm::vec3 p102,glm::vec3 p030,glm::vec3 p021,glm::vec3 p012,glm::vec3 p003){
  return triPatch1(triPatch2(p300,p210,p201,p120,p111,p102),triPatch2(p210,p120,p111,p030,p021,p012),triPatch2(p201,p111,p102,p021,p012,p003));
}

TriangleMesh* TriPatch::toTriangleMesh(){
  std::vector<glm::vec4> *triangles = new std::vector<glm::vec4>();
  int detail = m_detail;
  int save = 1;
  for (int n = 1;n <= detail;n++){
      for(int i=0;i<n;i++){
    int a=save;
    int b=a+n;
    int c=b+1;
    save = c -n;
    triangles->push_back(m_vertexData.at((a-1)*2));
    triangles->push_back(m_vertexData.at(a*2));
    triangles->push_back(m_vertexData.at((b-1)*2));
    triangles->push_back(m_vertexData.at(a*2));
    triangles->push_back(m_vertexData.at((c-1)*2));
    triangles->push_back(m_vertexData.at(a*2));
        }
    }
  std::vector<hpuint> indices;
  TriangleMesh* result = new TriangleMesh(triangles,indices);

  std::cout << "TriPatchVertices" << m_vertexData.size() << endl;
  return result;
}

void TriPatch::update(){
  glm::vec3 p000;
  int n=m_detail;
  m_vertexData.clear();
  glm::vec3 center = glm::vec3(0.0f);
  float radius = 1.0f;
  switch(m_degree){
    case(1):
       p000 = triPatch1(m_controlPoints[0],m_controlPoints[1],m_controlPoints[2]);
       std::cout << "BezierPunkt: "<< p000.x << "/" << p000.y << "/" <<p000.z << endl;

      break;
    case(2):
      for(int i=n; i>=0;i--){
          for(int j=n-i; j>=0; j--){
              for(int k=n-i-j;k>=0; k--){
                  if( i == 0 && j==0 && k==0)
                    break;
                  if((i+j+k)!=n)
                    break;
                  m_u = (float)i/(float)n;
                  m_v = (float)j/(float)n;
                  m_w = (float)k/(float)n;

                 p000 = triPatch2(m_controlPoints[0],m_controlPoints[1],m_controlPoints[2],m_controlPoints[3],m_controlPoints[4],m_controlPoints[5]);
                 std::cout<<"u/v/w"<<" "<<m_u<<"/"<<m_v<<"/"<<m_w<<endl;
                 //std::cout << "BezierPunkt: "<< p000.x << "/" << p000.y << "/" <<p000.z << endl;
                  //spherealize
                 glm::vec3 pot= (m_u*m_a)+(m_v*m_b)+(m_w*m_c);
                 pot = pot - center;
                 float offset = radius -glm::length(pot);
                 glm::vec3 offsetVector = glm::normalize(p000);
                 offsetVector = offset*offsetVector;
                 p000 = p000+offsetVector;
                 m_vertexData.push_back(glm::vec4(p000,1.0f));
                 glm::vec3 normal =(p000 - center);
                 m_vertexData.push_back(glm::vec4(normal,0.0f));
                }
            }
        }
      std::cout<<"vertexdataSize: "<<m_vertexData.size()<< endl;
      break;
      default:
      std::cout << "Zu Hoher Grad" <<endl;
      break;
    }

}
void TriPatch::setControlPoint(int index,glm::vec3 value){
  m_controlPoints[index]=value;
  std::cout << "updated ControlPoint: "<< m_controlPoints[index].x <<"/"<< m_controlPoints[index].y<<"/" << m_controlPoints[index].z << endl;
}
glm::vec3 TriPatch::getControlPoint(int index){
  return m_controlPoints[index];
}

#include "happah/geometries/SpherePatch.h"
#include <iostream>


SpherePatch::SpherePatch(int degree, hpvec3 a, hpvec3 b, hpvec3 c)
	: m_degree(degree),m_a(a),m_b(b),m_c(c),
	  m_u(1.0f),m_v(0.0f),m_w(0.0f),m_detail(50),m_center(hpvec3(0.0f)),m_radius(1.0f) {

  hpvec3 p000;
  int n=m_detail;

  uDivideTriangle(); // Just to quick generate 6 controlpoints
  m_controlPoints[2]=m_controlPoints[2]*2.0f;
  m_controlPoints[4]=m_controlPoints[4]*2.0f;
  m_controlPoints[1]=m_controlPoints[1]*2.0f;

      for(int i=n; i>=0;i--){
         for(int j=n-i; j>=0; j--){
              for(int k=n-i-j;k>=0; k--){
                  if( i == 0 && j==0 && k==0)
                    break;
                  if((i+j+k)!=n)
                    break;
                  buildSecantTriangle(m_a,m_b,m_c);
                  m_u = (float)i/(float)n;
                  m_v = (float)j/(float)n;
                  m_w = (float)k/(float)n;

                  // Create Points on secant triangle
                  hpvec3 p100 = triPatch1(m_secantTriPoints[0],m_secantTriPoints[1],m_secantTriPoints[2]);
                  hpvec3 p010 = triPatch1(m_secantTriPoints[1],m_secantTriPoints[3],m_secantTriPoints[4]);
                  hpvec3 p001 = triPatch1(m_secantTriPoints[2],m_secantTriPoints[4],m_secantTriPoints[5]);
                  bool hit;
                  // get triangle intersections
                  hpvec3 p100i = hpvec3(0.0f);
                  hpvec3 p010i = hpvec3(0.0f);
                  hpvec3 p001i = hpvec3(0.0f);
                  hit = intersectTriangle(glm::normalize(p100),m_controlPoints[0],m_controlPoints[1],m_controlPoints[2],&p100i);
                  hit = intersectTriangle(glm::normalize(p010),m_controlPoints[1],m_controlPoints[3],m_controlPoints[4],&p010i);
                  hit = intersectTriangle(glm::normalize(p001),m_controlPoints[2],m_controlPoints[4],m_controlPoints[5],&p001i);
                  //std::cout << "p100i: " << p100i.x << " " << p100i.y<<" " << p100i.z<< std::endl;
                  //std::cout << "p010i: " << p010i.x << " " << p010i.y<<" " << p010i.z<< std::endl;
                  //std::cout << "p001i: " << p001i.x << " " << p001i.y<<" " << p001i.z<< std::endl;


                  //std::cout << "cp     " << m_controlPoints[1].x<<" "<< m_controlPoints[1].y<< " "<<m_controlPoints[0].z<<std::endl;
                  //std::cout << " First Stage Done"<< std::endl;
                  buildSecantTriangle(p100i,p010i,p001i);
                  p000 = triPatch1(m_secantTriPoints[0],m_secantTriPoints[3],m_secantTriPoints[5]);
                  hpvec3 p000i = hpvec3(0.0f);
                  hit = intersectTriangle(glm::normalize(p000),p100i,p010i,p001i,&p000i);
                  //std::cout << "p000i: "<< p000i.x<<" "<< p000i.y<<" " << p000i.z  <<std::endl;

                  //std::cout << "cp     " << m_controlPoints[0].x<<" "<< m_controlPoints[0].y<<std::endl;
                  //p000 = triPatch2(m_controlPoints[0],m_controlPoints[1],m_controlPoints[2],m_controlPoints[3],m_controlPoints[4],m_controlPoints[5]);
                 //std::cout<<"u/v/w"<<" "<<m_u<<"/"<<m_v<<"/"<<m_w<<std::endl;
                 //std::cout << "BezierPunkt: "<< p000.x << "/" << p000.y << "/" <<p000.z << std::endl;
                 m_verticesAndNormals.push_back(p000i);
                 hpvec3 normal = (p000-m_center); // TODO: THINK OF SOMETING NORMAL
                 m_verticesAndNormals.push_back(normal);

              }
           }
        }


std::cout<<"SpherePatch Created"<<std::endl;
}

void SpherePatch::uDivideTriangle(){
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
         // std::cout << "CP" << i << ": "<< m_controlPoints[i].x <<"/"<< m_controlPoints[i].y<<"/" << m_controlPoints[i].z << std::endl;
        }
     }
}

hpvec3 SpherePatch::triPatch1(hpvec3 p100,hpvec3 p010,hpvec3 p001){

  hpvec3 p000 = m_u*p100+m_v*p010+m_w*p001;


  return  p000;
}

hpvec3 SpherePatch::triPatch2(hpvec3 p200,hpvec3 p110,hpvec3 p101,hpvec3 p020,hpvec3 p011,hpvec3 p002){
    return triPatch1(triPatch1(p200,p110,p101),triPatch1(p110,p020,p011),triPatch1(p101,p011,p002));
}

hpvec3 SpherePatch::triPatch3(hpvec3 p300,hpvec3 p210,hpvec3 p201,hpvec3 p120,hpvec3 p111,
                    hpvec3 p102,hpvec3 p030,hpvec3 p021,hpvec3 p012,hpvec3 p003){
  return triPatch1(triPatch2(p300,p210,p201,p120,p111,p102),triPatch2(p210,p120,p111,p030,p021,p012),triPatch2(p201,p111,p102,p021,p012,p003));
}

TriangleMesh3D* SpherePatch::toTriangleMesh(){
  std::vector<hpvec3> *verticesAndNormals = &m_verticesAndNormals;
  std::vector<hpuint> *indices = new std::vector<hpuint>();
  int detail = m_detail;
  int save = 1;
  for (int n = 1;n <= detail;n++){
      for(int i=0;i<n;i++){
    int a=save;
    int b=a+n;
    int c=b+1;
    save = c -n;
    indices->push_back(a);
    indices->push_back(b);
    indices->push_back(c);
    int stop = ((n+1)*(n+2))/2;
    if (c<stop){
      int d = a ;
      int e = b+1;
      int f = c-n;
    indices->push_back(d);
    indices->push_back(e);
    indices->push_back(f);

        }
    }
}
  return new TriangleMesh3D(verticesAndNormals, indices);
}

void SpherePatch::buildSecantTriangle(hpvec3 a, hpvec3 b, hpvec3 c){
  hpvec3 sa = m_radius*(glm::normalize(a-m_center));
  hpvec3 sb = m_radius*(glm::normalize(b-m_center));
  hpvec3 sc = m_radius*(glm::normalize(c-m_center));

  m_secantTriPoints[0]=sa;
  m_secantTriPoints[1]=sa+((sb-sa)/2.0f);
  m_secantTriPoints[2]=sa+((sc-sa)/2.0f);
  m_secantTriPoints[3]=sb;
  m_secantTriPoints[4]=sb+((sc-sb)/2.0f);
  m_secantTriPoints[5]=sc;
  for (int i=0; i<6; i++){
  //    std::cout << "SecantTriangleCP" << i << ": "<< m_secantTriPoints[i].x <<"/"<< m_secantTriPoints[i].y<<"/" << m_secantTriPoints[i].z << std::endl;
    }
}
bool SpherePatch::intersectTriangle(hpvec3 dir,hpvec3 e,hpvec3 f,hpvec3 g,hpvec3* hit){
 float result;
 float epsilon = 0.00001f;
 hpvec3 orig = hpvec3(0.0f);

 hpvec3 v1 = f-e;
 hpvec3 v2 = g-e;
 hpvec3 q = glm::cross(dir,v2);
 float det = glm::dot(v1,q);
 if (det>(-epsilon)&&det<(epsilon)){
   result = false;
 //  std::cout<< " NO HIT1" <<std::endl;
   return result;
   }
 float inv = (1/det);
 hpvec3 s = orig-e;
 float u = inv*glm::dot(s,q);
 if (u<0.0f){
     result = false;
 //    std::cout<< " NO HIT2" << std::endl;
     return result;

   }
 hpvec3 r=glm::cross(s,v1);
 float v=inv*glm::dot(dir,r);
 if (v<0.0f-epsilon || u+v > 1.0f+epsilon){
     result = false;
  //   std::cout<< " NO HIT3" <<std::endl;
     return result;
   }
 float t= inv*glm::dot(v2,r);
 //std::cout << "HIT"<< std::endl;
 result = true;
 hpvec3 hitpoint= orig+t*dir;
// std::cout << "hit at " << hitpoint.x<<" " << hitpoint.y<<" " <<hitpoint.z<<std::endl;
 *hit=hitpoint;
 return result;
}

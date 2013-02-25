#ifndef GEOMETRYMESH_H
#define GEOMETRYMESH_H

#include <glm/glm.hpp>
#include <vector>

#include "happah/models/Drawable.h"

struct TriangleFace{
 unsigned int a,b,c;
 TriangleFace(unsigned int x,unsigned int y, unsigned int z){a=x; b=y ; c=z;}
};

struct QuadFace{
  unsigned int a,b,c,d;
  QuadFace(unsigned int x,unsigned int y, unsigned int z,unsigned int w){a=x; b=y ; c=z;d=w;}
};

class GeometryMesh : public Drawable
{
public:
  GeometryMesh(std::vector<glm::vec4> *vertices,std::vector<glm::vec4> *normals,std::string name);
  ~GeometryMesh();

  void setVertices(std::vector<glm::vec4> *vertices);
  void setNormals(std::vector<glm::vec4> *normals);
  std::vector<glm::vec4>* getVertices();
  std::vector<glm::vec4>* getNormals();


  int addTriangleFace(unsigned int a, unsigned int b, unsigned int c);
  void delTriangleFace(unsigned int index);
  TriangleFace getTriangleFace(unsigned int index);

  int addQuadFace(unsigned int a, unsigned int b, unsigned int c,unsigned int d);
  void delQuadFace(unsigned int index);
  QuadFace getQuadFace(unsigned int index);



private:
  std::vector<glm::vec4>*        m_vertices;
  std::vector<glm::vec4>*        m_normals;
  std::vector<TriangleFace>*     m_triangleFaces;
  std::vector<QuadFace>*         m_quadFaces;
  bool m_hasTriangularMesh;
  bool m_hasQuadMesh;
};

#endif // GEOMETRYMESH_H

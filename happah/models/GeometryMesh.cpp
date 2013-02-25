#include "GeometryMesh.h"

GeometryMesh::GeometryMesh(std::vector<glm::vec4> *vertices,std::vector<glm::vec4> *normals,std::string name):Drawable(name)
{
  m_vertices = vertices;
  m_normals = normals;
  m_hasTriangularMesh = false;
  m_hasQuadMesh = false;
  m_triangleFaces = new std::vector<TriangleFace>;
  m_quadFaces = new std::vector<QuadFace>;
}

GeometryMesh::~GeometryMesh(){

}


void GeometryMesh::setVertices(std::vector<glm::vec4> *vertices){
  m_vertices = vertices ;
}

void GeometryMesh::setNormals(std::vector<glm::vec4> *normals){
  m_normals = normals;
}

std::vector<glm::vec4>* GeometryMesh::getVertices(){
  return m_vertices;
}

std::vector<glm::vec4>*GeometryMesh::getNormals(){
  return m_normals;
}

 int GeometryMesh::addTriangleFace(unsigned int a, unsigned int b, unsigned int c){
   TriangleFace triangleFace = TriangleFace(a,b,c);
   m_triangleFaces->push_back(triangleFace);
   return m_triangleFaces->size()-1;
 }

 void GeometryMesh::delTriangleFace(unsigned int index){
   m_triangleFaces->erase(m_triangleFaces->begin()+index);
 }

 TriangleFace GeometryMesh::getTriangleFace(unsigned int index){
   return m_triangleFaces->at(index);
 }

 int GeometryMesh::addQuadFace(unsigned int a, unsigned int b, unsigned int c,unsigned int d){
   QuadFace quadFace = QuadFace(a,b,c,d);
   m_quadFaces->push_back(quadFace);
   return m_quadFaces->size()-1;
 }

 void GeometryMesh::delQuadFace(unsigned int index){
   m_quadFaces->erase(m_quadFaces->begin()+index);
 }
QuadFace GeometryMesh::getQuadFace(unsigned int index){
   return m_quadFaces->at(index);
 }

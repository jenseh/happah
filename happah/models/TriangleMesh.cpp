#include "happah/models/TriangleMesh.h"

TriangleMesh::TriangleMesh(std::vector<glm::vec4> *vertexData, std::string name) : Drawable(name)
{
    m_vertexData = vertexData;
}

TriangleMesh::~TriangleMesh()
{
    for (unsigned int i = 0; i < m_triangles.size(); ++i) {
        delete m_triangles[i];
    }
    delete m_vertexData;
}

TriangleMesh& TriangleMesh::operator=(const TriangleMesh& other) {
    *m_vertexData = *(other.m_vertexData);
    m_triangles = other.m_triangles;
}

std::vector<glm::vec4>* TriangleMesh::getVertexData()
{
    return m_vertexData;
}

int TriangleMesh::getTupleSize() {
  return 3;
}

std::vector<Triangle*>* TriangleMesh::getTriangles() {
  return &m_triangles;
}

void TriangleMesh::fillTriangles(){
    if (m_vertexData->size() % 6 != 0) {
      std::cerr << "Error: Invalid number of vertices and normals for a triangle!" << std::endl;
      return;
    }

    size_t triangleCount = m_vertexData->size() / 6;
    m_triangles.clear();
    m_triangles.resize(triangleCount);
    for(size_t i = 0; i < triangleCount; i++){
        m_triangles.at(i) = new Triangle();

        m_triangles.at(i)->vertices[0] = glm::vec3(m_vertexData->at(i*6)[0], m_vertexData->at(i*6)[1], m_vertexData->at(i*6)[2]);
        m_triangles.at(i)->normals[0] = glm::vec3(m_vertexData->at(i*6+1)[0], m_vertexData->at(i*6+1)[1], m_vertexData->at(i*6+1)[2]);

        m_triangles.at(i)->vertices[1] = glm::vec3(m_vertexData->at(i*6+2)[0], m_vertexData->at(i*6+2)[1], m_vertexData->at(i*6+2)[2]);
        m_triangles.at(i)->normals[1] = glm::vec3(m_vertexData->at(i*6+3)[0], m_vertexData->at(i*6+3)[1], m_vertexData->at(i*6+3)[2]);

        m_triangles.at(i)->vertices[2] = glm::vec3(m_vertexData->at(i*6+4)[0], m_vertexData->at(i*6+4)[1], m_vertexData->at(i*6+4)[2]);
        m_triangles.at(i)->normals[2] = glm::vec3(m_vertexData->at(i*6+5)[0], m_vertexData->at(i*6+5)[1], m_vertexData->at(i*6+5)[2]);
      }
}


RayCloud* TriangleMesh::toRayCloud(){
    fillTriangles();
    std::vector<Ray*> rayVector(m_triangles.size() * 3);
    for( size_t i = 0; i < m_triangles.size(); i++){
        rayVector[i*3] = new Ray;
        rayVector[i*3]->direction = m_triangles.at(i)->normals[0];
        rayVector[i*3]->origin = m_triangles.at(i)->vertices[0];
        rayVector[i*3]->inverse_direction = -rayVector[i*3]->direction;

        rayVector[i*3+1] = new Ray;
        rayVector[i*3+1]->direction = m_triangles.at(i)->normals[1];
        rayVector[i*3+1]->origin = m_triangles.at(i)->vertices[1];
        rayVector[i*3+1]->inverse_direction = -rayVector[i*3+1]->direction;

        rayVector[i*3+2] = new Ray;
        rayVector[i*3+2]->direction = m_triangles.at(i)->normals[2];
        rayVector[i*3+2]->origin = m_triangles.at(i)->vertices[2];
        rayVector[i*3+2]->inverse_direction = -rayVector[i*3+2]->direction;
    }
    return new RayCloud(rayVector);
}

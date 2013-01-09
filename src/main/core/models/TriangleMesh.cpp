#include "TriangleMesh.h"

TriangleMesh::TriangleMesh(std::vector<glm::vec4> vertexData)
{
    vertexData_ = vertexData;
}

TriangleMesh::~TriangleMesh()
{

}

std::vector<glm::vec4>* TriangleMesh::getVertexData()
{
    return &vertexData_;
}
int TriangleMesh::getTupleSize() {
  return 3;
}
std::vector<Triangle*>& TriangleMesh::getTriangles() {
  return triangles_;
}

void TriangleMesh::fillTriangles(){
    if (vertexData_.size() % 6 != 0) {
      std::cerr << "Error: Invalid number of vertices and normals for a triangle!" << std::endl;
      return;
    }

    size_t triangleCount = vertexData_.size() / 6;
    triangles_.clear();
    triangles_.resize(triangleCount);
    for(size_t i = 0; i < triangleCount; i++){
        triangles_.at(i) = new Triangle();

        triangles_.at(i)->vertices[0] = glm::vec3(vertexData_[i*6][0], vertexData_[i*6][1], vertexData_[i*6][2]);
        triangles_.at(i)->normals[0] = glm::vec3(vertexData_[i*6+1][0], vertexData_[i*6+1][1], vertexData_[i*6+1][2]);

        triangles_.at(i)->vertices[1] = glm::vec3(vertexData_[i*6+2][0], vertexData_[i*6+2][1], vertexData_[i*6+2][2]);
        triangles_.at(i)->normals[1] = glm::vec3(vertexData_[i*6+3][0], vertexData_[i*6+3][1], vertexData_[i*6+3][2]);

        triangles_.at(i)->vertices[2] = glm::vec3(vertexData_[i*6+4][0], vertexData_[i*6+4][1], vertexData_[i*6+4][2]);
        triangles_.at(i)->normals[2] = glm::vec3(vertexData_[i*6+5][0], vertexData_[i*6+5][1], vertexData_[i*6+5][2]);

    }
}


RayCloud* TriangleMesh::toRayCloud(){
    fillTriangles();
    std::vector<Ray*> rayVector(triangles_.size() * 3);
    for( size_t i = 0; i < triangles_.size(); i++){
        rayVector[i*3] = new Ray;
        rayVector[i*3]->direction = triangles_.at(i)->normals[0];
        rayVector[i*3]->origin = triangles_.at(i)->vertices[0];
        rayVector[i*3]->inverse_direction = -rayVector[i*3]->direction;

        rayVector[i*3+1] = new Ray;
        rayVector[i*3+1]->direction = triangles_.at(i)->normals[1];
        rayVector[i*3+1]->origin = triangles_.at(i)->vertices[1];
        rayVector[i*3+1]->inverse_direction = -rayVector[i*3+1]->direction;

        rayVector[i*3+2] = new Ray;
        rayVector[i*3+2]->direction = triangles_.at(i)->normals[2];
        rayVector[i*3+2]->origin = triangles_.at(i)->vertices[2];
        rayVector[i*3+2]->inverse_direction = -rayVector[i*3+2]->direction;
    }
    return new RayCloud(rayVector);
}

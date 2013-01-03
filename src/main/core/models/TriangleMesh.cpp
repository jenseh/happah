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

void TriangleMesh::fillTriangles(){
    triangles_.resize(vertexData_.size() / 6);
    for( size_t i = 0; i < vertexData_.size() / 6; ){
        triangles_[i].vertices[0] = glm::vec3(vertexData_[i*6][0], vertexData_[i*6][1], vertexData_[i*6][2]);
        triangles_[i].normals[0] = glm::vec3(vertexData_[i*6+1][0], vertexData_[i*6+1][1], vertexData_[i*6+1][2]);

        triangles_[i].vertices[1] = glm::vec3(vertexData_[i*6+2][0], vertexData_[i*6+2][1], vertexData_[i*6+2][2]);
        triangles_[i].normals[1] = glm::vec3(vertexData_[i*6+3][0], vertexData_[i*6+3][1], vertexData_[i*6+3][2]);

        triangles_[i].vertices[2] = glm::vec3(vertexData_[i*6+4][0], vertexData_[i*6+4][1], vertexData_[i*6+4][2]);
        triangles_[i].normals[2] = glm::vec3(vertexData_[i*6+5][0], vertexData_[i*6+5][1], vertexData_[i*6+5][2]);

    }
}


std::vector<Ray*> TriangleMesh::toRayCloud(){
    fillTriangles();
    std::vector<Ray*> result(triangles_.size() * 3);
    for( size_t i = 0; i < triangles_.size(); i++){
        result[i*3] = new Ray;
        result[i*3]->direction = triangles_[i].normals[0];
        result[i*3]->origin = triangles_[i].vertices[0];
        result[i*3]->inverse_direction = -result[i*3]->direction;

        result[i*3+1] = new Ray;
        result[i*3+1]->direction = triangles_[i].normals[1];
        result[i*3+1]->origin = triangles_[i].vertices[1];
        result[i*3+1]->inverse_direction = -result[i*3+1]->direction;

        result[i*3+2] = new Ray;
        result[i*3+2]->direction = triangles_[i].normals[2];
        result[i*3+2]->origin = triangles_[i].vertices[2];
        result[i*3+2]->inverse_direction = -result[i*3+2]->direction;
    }
    return result;
}

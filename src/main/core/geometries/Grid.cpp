#include "Grid.h"

Grid::Grid() {
}

Grid::~Grid() {
}


QuadMesh* Grid::toQuadMesh() {
    for (float x = -2.0; x <= 2.0; x = x + 0.5f) {
        for (float z = -2.0f; z <= 2.0f; z = z + 0.5f) {
            glm::vec4 normal = glm::vec4(0.0, 1.0, 0.0, 1.0);
            vertexData_.push_back(glm::vec4(x, -1.0f, -2.0, 1.0f));
            vertexData_.push_back(normal);
            vertexData_.push_back(glm::vec4(x, -1.0f, 2.0, 1.0f));
            vertexData_.push_back(normal);
            vertexData_.push_back(glm::vec4(-2.0f, -1.0f, z, 1.0f));
            vertexData_.push_back(normal);
            vertexData_.push_back(glm::vec4(2.0f, -1.0f, z, 1.0f));
            vertexData_.push_back(normal);
        }
    }
    QuadMesh* result = new QuadMesh(vertexData_);
    result->setName(name_ + " - Instance 1");
    return result;
}

TriangleMesh* Grid::toTriangleMesh() {
  //TODO: Implement this function
  return 0;
}

#include "happah/geometries/Grid.h"

Grid::Grid(std::string name) : NonDrawable(name) {
}

Grid::~Grid() {
}


QuadMesh* Grid::toQuadMesh() {
    for (float x = -2.0; x <= 2.0; x = x + 0.5f) {
        for (float z = -2.0f; z <= 2.0f; z = z + 0.5f) {
            glm::vec4 normal = glm::vec4(0.0, 1.0, 0.0, 1.0);
            m_vertexData.push_back(glm::vec4(x, -1.0f, -2.0, 1.0f));
            m_vertexData.push_back(normal);
            m_vertexData.push_back(glm::vec4(x, -1.0f, 2.0, 1.0f));
            m_vertexData.push_back(normal);
            m_vertexData.push_back(glm::vec4(-2.0f, -1.0f, z, 1.0f));
            m_vertexData.push_back(normal);
            m_vertexData.push_back(glm::vec4(2.0f, -1.0f, z, 1.0f));
            m_vertexData.push_back(normal);
        }
    }
    QuadMesh* result = new QuadMesh(m_vertexData, concatStringNumber(m_name + " - Instance ", m_objectIdCounter++));
    result->setModelMatrix(m_modelMatrix);
    return result;
}

TriangleMesh* Grid::toTriangleMesh() {
  //TODO: Implement this function
  return 0;
}
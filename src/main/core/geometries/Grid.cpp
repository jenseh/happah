#include "Grid.h"

Grid::Grid() : GeometryObject() {
}

Grid::~Grid() {
}


void Grid::createVertexData() {
    for (float x = -2.0; x <= 2.0; x = x + 0.5f) {
        for (float z = -2.0f; z <= 2.0f; z = z + 0.5f) {
            vertexData_.push_back(glm::vec4(x, -1.0f, -2.0, 1.0f));
            vertexData_.push_back(glm::vec4(x, -1.0f, 2.0, 1.0f));
            vertexData_.push_back(glm::vec4(-2.0f, -1.0f, z, 1.0f));
            vertexData_.push_back(glm::vec4(2.0f, -1.0f, z, 1.0f));
        }
    }
}

#include "QuadliteralMesh.h"

QuadliteralMesh::QuadliteralMesh(std::vector<glm::vec4> vertexData)
{
    vertexData_ = vertexData;
}

std::vector<glm::vec4> QuadliteralMesh::getVertexData()
{
    return vertexData_;
}

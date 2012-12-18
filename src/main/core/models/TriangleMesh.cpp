#include "TriangleMesh.h"

TriangleMesh::TriangleMesh(std::vector<glm::vec4> vertexData)
{
    vertexData_ = vertexData;
}

std::vector<glm::vec4> TriangleMesh::getVertexData()
{
    return vertexData_;
}

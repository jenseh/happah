#include "QuadMesh.h"

QuadMesh::QuadMesh(std::vector<glm::vec4> vertexData)
{
    vertexData_ = vertexData;
}

std::vector<glm::vec4> QuadMesh::getVertexData()
{
    return vertexData_;
}

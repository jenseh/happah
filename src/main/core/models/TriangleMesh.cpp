#include "TriangleMesh.h"

TriangleMesh::TriangleMesh(std::vector<glm::vec4> vertexData)
{
    vertexData_ = vertexData;
}

TriangleMesh::~TriangleMesh()
{

}

std::vector<glm::vec4> TriangleMesh::getVertexData()
{
    return vertexData_;
}

void TriangleMesh::draw(DrawManager* drawManager) {

}

#include "QuadMesh.h"

QuadMesh::QuadMesh(std::vector<glm::vec4> vertexData)
{
    vertexData_ = vertexData;
}

QuadMesh::~QuadMesh()
{

}

std::vector<glm::vec4>* QuadMesh::getVertexData()
{
    return &vertexData_;
}

int QuadMesh::getTupleSize() {
  return 4;
}

TriangleMesh* QuadMesh::toTriangleMesh(){
    std::vector<glm::vec4> triVertexData;
    triVertexData.resize(vertexData_.size() / 4 * 6);
    for( size_t i = 0; i < vertexData_.size() / 8; i++){
        // Trianle 1
        // A
        triVertexData[i*12] =vertexData_[i*8];
        triVertexData[i*12+1] =vertexData_[i*8+1];
        // B
        triVertexData[i*12+2] =vertexData_[i*8+2];
        triVertexData[i*12+3] =vertexData_[i*8+3];
        // C
        triVertexData[i*12+4] =vertexData_[i*8+4];
        triVertexData[i*12+5] =vertexData_[i*8+5];

        // Trianle 2
        // A
        triVertexData[i*12+6] =vertexData_[i*8];
        triVertexData[i*12+7] =vertexData_[i*8+1];
        // C
        triVertexData[i*12+8] =vertexData_[i*8+4];
        triVertexData[i*12+9] =vertexData_[i*8+5];
        // D
        triVertexData[i*12+10] =vertexData_[i*8+6];
        triVertexData[i*12+11] =vertexData_[i*8+7];

    }
    TriangleMesh* result = new TriangleMesh(triVertexData);
    return result;
}

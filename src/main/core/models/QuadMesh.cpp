#include "QuadMesh.h"

QuadMesh::QuadMesh(std::vector<glm::vec4> vertexData, std::string name) : Drawable(name)
{
    m_vertexData = vertexData;
}

QuadMesh::~QuadMesh()
{

}

std::vector<glm::vec4>* QuadMesh::getVertexData()
{
    return &m_vertexData;
}


int QuadMesh::getTupleSize() {
  return 4;
}

//TODO: remove this method and use GeometryObject->toTriangleMesh() !
TriangleMesh* QuadMesh::toTriangleMesh(){
    std::vector<hpvec4> *triVertexData = new std::vector<hpvec4>();
    triVertexData->resize(m_vertexData.size() / 4 * 6);
    for( size_t i = 0; i < m_vertexData.size() / 8; i++){
        // Triangle 1
        // A
        triVertexData->at(i*12) = m_vertexData[i*8];
        triVertexData->at(i*12+1) = m_vertexData[i*8+1];
        // B
        triVertexData->at(i*12+2) = m_vertexData[i*8+2];
        triVertexData->at(i*12+3) = m_vertexData[i*8+3];
        // C
        triVertexData->at(i*12+4) = m_vertexData[i*8+4];
        triVertexData->at(i*12+5) = m_vertexData[i*8+5];

        // Trianle 2
        // A
        triVertexData->at(i*12+6) = m_vertexData[i*8];
        triVertexData->at(i*12+7) = m_vertexData[i*8+1];
        // C
        triVertexData->at(i*12+8) = m_vertexData[i*8+4];
        triVertexData->at(i*12+9) = m_vertexData[i*8+5];
        // D
        triVertexData->at(i*12+10) = m_vertexData[i*8+6];
        triVertexData->at(i*12+11) = m_vertexData[i*8+7];
    }

    TriangleMesh* result = new TriangleMesh(triVertexData, concatStringNumber(m_name + " - Instance ", m_objectIdCounter++));
    result->setModelMatrix(*getModelMatrix());
    return result;
}


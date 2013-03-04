#include "happah/geometries/TriangleMesh.h"

TriangleMesh::TriangleMesh(vector<hpvec3>* vertexData,vector<hpuint>* indices) {
    m_vertexData = vertexData;
    m_indices = indices;
}

TriangleMesh::~TriangleMesh() {
    delete m_vertexData;
    delete m_indices;
}


vector<hpvec3>* TriangleMesh::getVertexData() {
    return m_vertexData;
}

vector<hpuint>* TriangleMesh::getIndices() {
	return m_indices;
}

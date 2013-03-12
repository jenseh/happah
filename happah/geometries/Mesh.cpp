#include "Mesh.h"

Mesh::Mesh(vector<hpvec3>* vertexData,vector<hpuint>* indices)
		:m_vertexData(vertexData),m_indices(indices) {}

Mesh::~Mesh() {
    delete m_vertexData;
    delete m_indices;
}

vector<hpvec3>* Mesh::getVertexData() {
    return m_vertexData;
}

vector<hpuint>* Mesh::getIndices() {
	return m_indices;
}

TriangleMesh::TriangleMesh(vector<hpvec3>* vertexData,vector<hpuint>* indices)
		: Mesh(vertexData,indices) {}
TriangleMesh::~TriangleMesh() {}

LineMesh::LineMesh(vector<hpvec3>* vertexData,vector<hpuint>* indices)
		: Mesh(vertexData,indices) {}
LineMesh::~LineMesh() {}


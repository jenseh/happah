#include "Mesh.h"

Mesh::Mesh(vector<hpvec2>* verticesAndNormals,vector<hpuint>* indices)
		:m_indices(indices) {
	m_verticesAndNormals = new vector<hpvec3>(verticesAndNormals->size());
	vector<hpvec3>::iterator itVec3 = m_verticesAndNormals->begin();
	for(vector<hpvec2>::iterator it = verticesAndNormals->begin(), end = verticesAndNormals->end(); it != end; ++it) {
		(*itVec3) = hpvec3(*it, 0.0f);
		++itVec3;
	}
	delete verticesAndNormals;
}

Mesh::Mesh(vector<hpvec3>* verticesAndNormals,vector<hpuint>* indices)
		:m_verticesAndNormals(verticesAndNormals),m_indices(indices) {}

Mesh::~Mesh() {
	delete m_verticesAndNormals;
	delete m_indices;
}

vector<hpvec3>* Mesh::getVerticesAndNormals() {
	return m_verticesAndNormals;
}

vector<hpuint>* Mesh::getIndices() {
	return m_indices;
}


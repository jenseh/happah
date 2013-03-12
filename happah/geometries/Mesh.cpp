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

vector<Ray>* TriangleMesh::toRays(){
	vector<hpvec3>* vertexData = getVertexData();
	vector<hpuint>* indices = getIndices();

	vector<Ray>* result = new vector<Ray>();
	result->reserve(indices->size());
	for( size_t i = 0; i < indices->size(); i++){
		result->push_back(	Ray(vertexData->at(2*indices->at(i)), // Origin
								vertexData->at(2*indices->at(i)+1)) ); // Direction
	}
	return result;
}

vector<Triangle>* TriangleMesh::toTriangles(){
	vector<hpvec3>* vertexData = getVertexData();
	vector<hpuint>* indices = getIndices();

	vector<Triangle>* result = new vector<Triangle>();
	result->reserve(indices->size() / 3);
	for( size_t i = 0; i < indices->size() / 3; i+=3){
		result->push_back( Triangle(vertexData->at(2 * indices->at(i)),
									vertexData->at(2 * indices->at(i+1)),
									vertexData->at(2 * indices->at(i+2))));
	}
	return result;
}

LineMesh::LineMesh(vector<hpvec3>* vertexData,vector<hpuint>* indices)
		: Mesh(vertexData,indices) {}
LineMesh::~LineMesh() {}
#include "Mesh.h"

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

TriangleMesh::TriangleMesh(vector<hpvec3>* verticesAndNormals,vector<hpuint>* indices)
		: Mesh(verticesAndNormals,indices) {}
TriangleMesh::~TriangleMesh() {}

vector<Ray>* TriangleMesh::toRays(){
	vector<hpvec3>* verticesAndNormals = getVerticesAndNormals();

	vector<Ray>* result = new vector<Ray>();
	result->resize(verticesAndNormals->size()/2);
	for( size_t i = 0; i < verticesAndNormals->size(); i+=2){
		result->at(i/2) = 	Ray(verticesAndNormals->at(i), // Origin
								verticesAndNormals->at(i+1) ); // Direction
	}
	return result;
}

vector<Triangle>* TriangleMesh::toTriangles(){
	vector<hpvec3>* verticesAndNormals = getVerticesAndNormals();
	vector<hpuint>* indices = getIndices();

	vector<Triangle>* result = new vector<Triangle>();
	result->reserve(indices->size() / 3);
	for(size_t i = 0; i < indices->size(); i += 3){
		Triangle t = Triangle(verticesAndNormals->at(2 * indices->at(i)),
							  verticesAndNormals->at(2 * indices->at(i+1)),
							  verticesAndNormals->at(2 * indices->at(i+2)));

		result->push_back(t);
	}
	return result;
}

LineMesh::LineMesh(vector<hpvec3>* verticesAndNormals,vector<hpuint>* indices)
		: Mesh(verticesAndNormals,indices) {}

LineMesh::~LineMesh() {}


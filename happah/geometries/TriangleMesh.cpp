#include "happah/geometries/TriangleMesh.h"

TriangleMesh::TriangleMesh(vector<hpvec3>* verticesAndNormals,vector<hpuint>* indices)
		: Mesh(verticesAndNormals, indices) {}

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

hpuint TriangleMesh::getTriangleCount() {
	vector<hpuint>* indices = getIndices();
	return indices->size() / 3;
}

hpuint TriangleMesh::getVertexCount() {
	vector<hpuint>* indices = getIndices();
	return indices->size() / 2;
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


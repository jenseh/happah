#include "happah/geometries/LineMesh.h"

LineMesh::LineMesh(vector<hpvec2>* verticesAndNormals, vector<hpuint>* indices)
	: Mesh(verticesAndNormals,indices) {}

LineMesh::LineMesh(vector<hpvec3>* verticesAndNormals, vector<hpuint>* indices)
	: Mesh(verticesAndNormals,indices) {}

LineMesh::~LineMesh() {}

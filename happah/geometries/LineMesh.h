#pragma once

#include <memory>

#include "happah/geometries/Mesh.h"

using namespace std;

class LineMesh : public Mesh {
public:
	LineMesh(vector<hpvec2>* verticesAndNormals, vector<hpuint>* indices);
	LineMesh(vector<hpvec3>* verticesAndNormals, vector<hpuint>* indices);
	~LineMesh();
};
typedef shared_ptr<LineMesh> LineMesh_ptr;

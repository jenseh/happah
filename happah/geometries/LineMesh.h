#pragma once

#include <memory>

#include "happah/geometries/Mesh.h"

using namespace std;

template<typename T>
class LineMesh : public Mesh<T> {
public:
	LineMesh(vector<T>* verticesAndNormals, vector<hpuint>* indices);
	~LineMesh();

};
typedef LineMesh<hpvec2> LineMesh2D;
typedef shared_ptr<LineMesh2D> LineMesh2D_ptr;
typedef LineMesh<hpvec3> LineMesh3D;
typedef shared_ptr<LineMesh3D> LineMesh_ptr;


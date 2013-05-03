#pragma once

#include <memory>

#include "happah/geometries/Mesh.h"
#include "happah/math/Ray.h"
#include "happah/math/Triangle.h"

using namespace std;

class TriangleMesh : public Mesh {
public:
	TriangleMesh(vector<hpvec3>* verticesAndNormals, vector<hpuint>* indices);
	~TriangleMesh();

	hpuint getTriangleCount();
	hpuint getVertexCount();
	vector<Triangle>* toTriangles();
	vector<Ray>* toRays();
};
typedef shared_ptr<TriangleMesh> TriangleMesh_ptr;

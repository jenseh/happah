#pragma once

#include <memory>

#include "happah/geometries/Mesh.h"
#include "happah/geometries/Segment.h"

using namespace std;

template<typename T>
class SegmentEndpointsIterator : public iterator<random_access_iterator_tag, const SegmentEndpoints<T> > {
		//TODO
};

template<typename T>
class LineMesh : public Mesh<T> {//TODO: rename LineMesh to SegmentMesh?
public:


	LineMesh(vector<T>* verticesAndNormals, vector<hpuint>* indices);
	~LineMesh();

	SegmentEndpointsIterator<T> getBeginningOfSegmentEndpointsIteration();
	SegmentEndpointsIterator<T> getEndOfSegmentEndpointsIteration();

};
typedef LineMesh<hpvec2> LineMesh2D;
typedef shared_ptr<LineMesh2D> LineMesh2D_ptr;
typedef LineMesh<hpvec3> LineMesh3D;
typedef shared_ptr<LineMesh3D> LineMesh3D_ptr;


#include "happah/geometries/LineMesh.h"

template<typename T>
LineMesh<T>::LineMesh(vector<T>* verticesAndNormals, vector<hpuint>* indices)
	: Mesh<T>(verticesAndNormals, indices) {}

template<typename T>
LineMesh<T>::~LineMesh() {}

template<typename T>
SegmentEndpointsIterator<T> LineMesh<T>::getBeginningOfSegmentEndpointsIteration() {
	return SegmentEndpointsIterator<T>(); //TODO
}

template<typename T>
SegmentEndpointsIterator<T> LineMesh<T>::getEndOfSegmentEndpointsIteration() {
	return SegmentEndpointsIterator<T>(); //TODO
}

template class LineMesh<hpvec2>;
template class LineMesh<hpvec3>;


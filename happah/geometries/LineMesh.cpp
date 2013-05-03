#include "happah/geometries/LineMesh.h"

template<typename T>
LineMesh<T>::LineMesh(vector<T>* verticesAndNormals, vector<hpuint>* indices)
	: Mesh<T>(verticesAndNormals, indices) {}

template<typename T>
LineMesh<T>::~LineMesh() {}

template class LineMesh<hpvec2>;
template class LineMesh<hpvec3>;


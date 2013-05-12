#include "happah/geometries/TriangleMesh.h"

template<typename T>
TriangleMesh<T>::TriangleMesh(vector<T>* verticesAndNormals,vector<hpuint>* indices)
		: Mesh<T>(verticesAndNormals, indices) {}

template<typename T>
TriangleMesh<T>::~TriangleMesh() {}

template<typename T>
TriangleIterator* TriangleMesh<T>::getIterator() {
    return new TriangleMeshTriangleIterator(this);
}

/*** methods for the iterator class below here */
template<typename T>
TriangleMesh<T>::TriangleMeshTriangleIterator::TriangleMeshTriangleIterator(TriangleMesh<T>* triangleMesh) {
    this->m_myMesh = triangleMesh;
}

template<typename T>
TriangleVerticeRefs* TriangleMesh<T>::TriangleMeshTriangleIterator::operator[](int index) {
    // compile problem with compatificated code below
    return NULL;
    /*
    return new TriangleVerticeRefs(myMesh->getVerticesAndNormals->at(2 * myMesh->getIndices()->at(index)),
                                    myMesh->getVerticesAndNormals->at(2 * myMesh->getIndices()->at(index+1)),
                                    myMesh->getVerticesAndNormals->at(2 * myMesh->getIndices()->at(index+2)));*/
}


template class TriangleMesh<hpvec2>;
template class TriangleMesh<hpvec3>;




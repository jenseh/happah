#pragma once

#include <memory>

#include "happah/geometries/Mesh.h"
#include "happah/kdtree/TriangleIterator.h"
#include "happah/math/TriangleVerticeRefs.h"

using namespace std;

template<typename T>
class TriangleMesh : public Mesh<T> {
public:
	TriangleMesh(vector<T>* verticesAndNormals, vector<hpuint>* indices);
    ~TriangleMesh();

    /**
     * @brief getIterator returns the iterator to get the vertices to create the triangles of this structure
     * @return the iterator to iterate over the vertices structure from the mesh to create the triangles
     */
    virtual TriangleIterator* getIterator();


    class TriangleMeshTriangleIterator : public TriangleIterator {
    private:
        TriangleMesh<T>* m_myMesh;
    public:
        TriangleMeshTriangleIterator(TriangleMesh<T>*);
        virtual TriangleVerticeRefs* operator[](int);
    };

};
typedef TriangleMesh<hpvec2> TriangleMesh2D;
typedef shared_ptr<TriangleMesh2D> TriangleMesh2D_ptr;
typedef TriangleMesh<hpvec3> TriangleMesh3D;
typedef shared_ptr<TriangleMesh3D> TriangleMesh3D_ptr;


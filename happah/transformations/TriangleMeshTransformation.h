#ifndef TRIANGLEMESHTRANSFORMATION_H
#define TRIANGLEMESHTRANSFORMATION_H

#include "happah/HappahTypes.h"
#include "happah/geometries/TriangleMesh.h"

#include "Eigen/Sparse"
#include <iostream>
#include <ostream>
#include <string>

using namespace std;

class TriangleMeshTransformation;
typedef shared_ptr<TriangleMeshTransformation> TriangleMeshTransformation_ptr;

class TriangleMeshTransformation
{
public:
    TriangleMeshTransformation(hpmat3x3 matrix);    // just for testing
    TriangleMeshTransformation(hpmat4x4 matrix);
    TriangleMeshTransformation(vector<hpmat4x4> *transformations);

    TriangleMesh3D_ptr transform(TriangleMesh3D_ptr);

    static vector<hpvec3>* getVertices(TriangleMesh3D_ptr mesh);
private:

    hpmat4x4 matrix;
    Eigen::SparseMatrix<float> sparseMatrix;
    vector<hpmat4x4> *transformations;

};

#endif // TRIANGLEMESHTRANSFORMATION_H

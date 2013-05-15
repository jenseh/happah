#include "TriangleMeshTransformation.h"

/** Could get a better place, maybe a method in TriangleMesh itself? **/
vector<hpvec3>* TriangleMeshTransformation::getVertices(TriangleMesh3D_ptr mesh)
{
    vector<hpvec3>* vertices = new vector<hpvec3>();

    for (int i=0; i<mesh->getVerticesAndNormals()->size()/2; ++i)
    {
        vertices->push_back(mesh->getVerticesAndNormals()->at(i*2));
    }

    return vertices;

}

TriangleMeshTransformation::TriangleMeshTransformation(hpmat3x3 matrix)
{
    this->matrix = hpmat4x4(matrix);
    this->transformations = 0;
}


TriangleMeshTransformation::TriangleMeshTransformation(hpmat4x4 matrix)
{
    this->matrix = matrix;
    this->transformations = 0;
}

TriangleMeshTransformation::TriangleMeshTransformation(vector<hpmat4x4> *transformations)
{
    this->transformations = transformations;
}

TriangleMeshTransformation::~TriangleMeshTransformation() {}

TriangleMesh3D_ptr TriangleMeshTransformation::transform(TriangleMesh3D_ptr mesh)
{
    vector<hpvec3>* vertices = TriangleMeshTransformation::getVertices(mesh);
    vector<hpvec3>* verticesAndNormals = new vector<hpvec3>(mesh->getVerticesAndNormals()->size());
    vector<hpuint> *indices;

    if (transformations == 0) {
        hpvec4 v1 = hpvec4(vertices->at(0), 1);
        hpvec4 v2 = hpvec4(vertices->at(1), 1);
        hpvec4 v3 = hpvec4(vertices->at(2), 1);

        hpvec3 d1 = hpvec3(matrix * v1);
        hpvec3 d2 = hpvec3(matrix * v2);
        hpvec3 d3 = hpvec3(matrix * v3);
        hpvec3 n  = glm::normalize(glm::cross(d2-d1, d3-d1));

        verticesAndNormals->push_back(d1);
        verticesAndNormals->push_back(n);
        verticesAndNormals->push_back(d2);
        verticesAndNormals->push_back(n);
        verticesAndNormals->push_back(d3);
        verticesAndNormals->push_back(n);

    } else {

        indices = new vector<hpuint>(*mesh->getIndices());
        hpvec3 v1, v2, v3, c1, c2, c3, n;
        hpuint i1, i2, i3;

        int vertexIndex = 0;
        int transformationIndex = 0;
        while (vertexIndex < indices->size()-2)
        {
            i1 = indices->at(vertexIndex+0);
            i2 = indices->at(vertexIndex+1);
            i3 = indices->at(vertexIndex+2);

            v1 = vertices->at(i1);
            v2 = vertices->at(i2);
            v3 = vertices->at(i3);

            c1 = hpvec3(transformations->at(transformationIndex)*hpvec4(v1, 1));
            c2 = hpvec3(transformations->at(transformationIndex)*hpvec4(v2, 1));
            c3 = hpvec3(transformations->at(transformationIndex)*hpvec4(v3, 1));
            n = glm::normalize(glm::cross(c2-c1, c3-c1));

            verticesAndNormals->at(i1*2) = c1;
            verticesAndNormals->at(i1*2+1) = n;
            verticesAndNormals->at(i2*2) = c2;
            verticesAndNormals->at(i2*2+1) = n;
            verticesAndNormals->at(i3*2) = c3;
            verticesAndNormals->at(i3*2+1) = n;

            vertexIndex += 3;
            ++transformationIndex;
        }
    }

    return TriangleMesh3D_ptr(new TriangleMesh3D(verticesAndNormals, indices) );
}

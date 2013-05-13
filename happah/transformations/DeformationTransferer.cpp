#include "DeformationTransferer.h"

/** Takes 3 vertices of a source triangle and 3 vertices of a target triangle and returns
    a transformation 3x3 matrix, that transforms the source to the target triangle.
    The transformation does not take the translation into account. It only transforms shape and scale.
  */
hpmat3x3 DeformationTransferer::computeTransformationWithoutTranslation(hpvec3 v1, hpvec3 v2, hpvec3 v3, hpvec3 c1, hpvec3 c2, hpvec3 c3) {

    hpvec3 v4 = v1 + glm::normalize(glm::cross(v2 - v1, v3 - v1));
    hpvec3 c4 = c1 + glm::normalize(glm::cross(c2 - c1, c3 - c1));

    hpvec3 vM1 = v2-v1;
    hpvec3 vM2 = v3-v1;
    hpvec3 vM3 = v4-v1;

    hpmat3x3 vM(vM1.x, vM1.y, vM1.z,    // definition per column
                vM2.x, vM2.y, vM2.z,
                vM3.x, vM3.y, vM3.z);
    vM = glm::inverse(vM);

    hpvec3 cM1 = c2-c1;
    hpvec3 cM2 = c3-c1;
    hpvec3 cM3 = c4-c1;

    hpmat3x3 cM(cM1.x, cM1.y, cM1.z,
                cM2.x, cM2.y, cM2.z,
                cM3.x, cM3.y, cM3.z);

    return (cM * vM);
}

/** Takes 3 vertices of a source triangle and 3 vertices of a target triangle and returns
    a transformation 4x4 matrix, that transforms the source to the target triangle.
    The transformation does take the translation as well as the shape and scale transformation into account.
  */
hpmat4x4 DeformationTransferer::computeTransformation(hpvec3 v1, hpvec3 v2, hpvec3 v3, hpvec3 c1, hpvec3 c2, hpvec3 c3) {

    hpvec3 v4 = v1 + glm::normalize(glm::cross(v2 - v1, v3 - v1));
    hpvec3 c4 = c1 + glm::normalize(glm::cross(c2 - c1, c3 - c1));

    hpvec3 vM1 = v2-v1;
    hpvec3 vM2 = v3-v1;
    hpvec3 vM3 = v4-v1;

    hpmat3x3 vM(vM1.x, vM1.y, vM1.z,    // definition per column
                vM2.x, vM2.y, vM2.z,
                vM3.x, vM3.y, vM3.z);
    vM = glm::inverse(vM);

    hpvec3 cM1 = c2-c1;
    hpvec3 cM2 = c3-c1;
    hpvec3 cM3 = c4-c1;

    hpmat3x3 cM(cM1.x, cM1.y, cM1.z,
                cM2.x, cM2.y, cM2.z,
                cM3.x, cM3.y, cM3.z);

    hpmat3x3 affinePart = cM * vM;
    hpvec3 translation = c1-(affinePart * v1);

    hpmat4x4 T(affinePart);
    T[3] = hpvec4(translation, 0);

    return (T);
}


TriangleMeshTransformation_ptr DeformationTransferer::computeTransformation(TriangleMesh3D_ptr mesh, TriangleMesh3D_ptr deformedMesh) {

    vector<hpvec3> *verticesOfSource = TriangleMeshTransformation::getVertices(mesh);
    vector<hpvec3> *verticesOfTarget = TriangleMeshTransformation::getVertices(deformedMesh);
    vector<hpuint> *indicesOfSource = mesh->getIndices();
    vector<hpuint> *indicesOfTarget = deformedMesh->getIndices();
    vector<hpmat4x4> *transformations = new vector<hpmat4x4>();

    hpvec3 v1, v2, v3, c1, c2, c3;
    hpmat4x4 deformation;

    unsigned int index = 0;
    while (index < indicesOfSource->size() - 2) { //indices->size()-2) {

        v1 = verticesOfSource->at(indicesOfSource->at(index+0));
        v2 = verticesOfSource->at(indicesOfSource->at(index+1));
        v3 = verticesOfSource->at(indicesOfSource->at(index+2));

        c1 = verticesOfTarget->at(indicesOfTarget->at(index+0));
        c2 = verticesOfTarget->at(indicesOfTarget->at(index+1));
        c3 = verticesOfTarget->at(indicesOfTarget->at(index+2));

        deformation = computeTransformation(v1, v2, v3, c1, c2, c3);    // uses transform with translation for testing
        transformations->push_back(deformation);

        index += 3;
    }

    return TriangleMeshTransformation_ptr(new TriangleMeshTransformation(transformations));
}


forward_list<TriangleCorrespondence> DeformationTransferer::computeTriangleCorrespondences(TriangleMesh3D_ptr mesh1, TriangleMesh3D_ptr mesh2) {
    // ToDo
}


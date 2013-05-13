#ifndef DEFORMATIONTRANSFERER_H
#define DEFORMATIONTRANSFERER_H

#include <forward_list>
#include <vector>

#include "happah/geometries/TriangleMesh.h"
#include "happah/transformations/TriangleMeshTransformation.h"

/** A Mapping from source triangle ids to target triangle ids */
struct TriangleCorrespondence {
    unsigned int sourceID;
    unsigned int targetID;
};

class DeformationTransferer
{

public:
    /**
      Calculates a set of affine transformations tabulated for each triangle of the source mesh.
      To correctly deform the triangles normal, a forth vertex is defined as
            v4 = v1 + (v2-v1) x (v3-v1) / sqrt( |(v2-v1) x (v3-v1)| )
      and transformed as well.

      The affine transformation Qi (3x3 matrix) for triangle with index i is calculated by
            Qi = Ci * Vi^(-1)
            Vi = [v2-v1, v3-v1, v4-v1]  vi, k from 1..3 element Triangle_i(mesh)
            Ci = [c2-c1, c3-c1, c4-c1]  ci, k from 1..3 element Triangle_i(deformedMesh)

      The transformations are encapsulated and returned in a TriangleMeshTransformation object.
      */
    static TriangleMeshTransformation_ptr computeTransformation(TriangleMesh3D_ptr mesh, TriangleMesh3D_ptr deformedMesh);

    /**
      Computes the triangle correspondence by testing wether the centroids of two triangles are within a certain threshold and
      their normals are acute-angled (n1 ∟ n2 <= 90°).

      Hint: Changing mesh1 and mesh2 returns the same result, because the test is bidirectional.
      */
    static forward_list<TriangleCorrespondence> computeTriangleCorrespondences(TriangleMesh3D_ptr mesh1, TriangleMesh3D_ptr mesh2);
    /*
    static TriangleMeshTransformation computeTransformation(TriangleMesh3D_ptr mesh1, TriangleMesh3D_ptr mesh2, vector<pair<int, int> > vertexCorrespondences);

    static TriangleMesh3D_ptr deform(TriangleMesh3D_ptr mesh, TriangleMeshTransformation_ptr transformation);
    static TriangleMesh3D_ptr deform(TriangleMesh3D_ptr source, TriangleMesh3D_ptr deformedSource, TriangleMesh3D_ptr target, vector<pair<int, int> > vertexCorrespondences);
     /*
     {
         TriangleMeshTransformation sourceToDeformedSourceTransformation = computeTransformation(source, deformedSource);
         TriangleMeshTransformation sourceToTargetTransformation = computeTransformation(source, target, vertexCorrespondences);
         TriangleMesh_ptr sourceDeformedToTarget = deform(source, sourceToTargetTransformation);
         forward_list<int> triangleCorrespondences = computeTriangleCorrespondences(sourceDeformedToTarget, target);
         return deform(source, target, triangleCorrespondences, sourceToDeformedSourceTransformation);
     }
     */
     //static TriangleMesh3D_ptr deform(TriangleMesh3D_ptr source, TriangleMesh3D_ptr target, forward_list<pair<int, int> > triangleCorrespondences, TriangleMeshTransformation_ptr sourceDeformation);

private:
    static hpmat3x3 computeTransformationWithoutTranslation(hpvec3 v1, hpvec3 v2, hpvec3 v3, hpvec3 deformedV1, hpvec3 deformedV2, hpvec3 deformedV3);
    static hpmat4x4 computeTransformation(hpvec3 v1, hpvec3 v2, hpvec3 v3, hpvec3 deformedV1, hpvec3 deformedV2, hpvec3 deformedV3);
};

#endif // DEFORMATIONTRANSFERER_H

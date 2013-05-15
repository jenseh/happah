#include "happah/kdtreeLib/NearestNeighbor.h"


hpvec3 NearestNeighbor::triangleCentroid(TriangleMesh3D_ptr mesh, hpuint triangle) {

    hpuint triangleCount = (mesh->getIndices()->size() / 2 * 3);

    bool validMesh = mesh->getVerticesAndNormals()->size() % 2 == 0 && mesh->getIndices()->size() % 3 == 0;
    bool validTriangle = triangle <= triangleCount;

    // Test wether the mesh and the triagleId is valid
    assert (validMesh);
    assert (validTriangle);

    return  ( mesh->getVerticesAndNormals()->at(2 * mesh->getIndices()->at(triangle * 3))
              + mesh->getVerticesAndNormals()->at(2 * mesh->getIndices()->at(triangle * 3 + 1))
              + mesh->getVerticesAndNormals()->at(2 * mesh->getIndices()->at(triangle * 3 + 2)) ) ;
}

vector<hpuint>* NearestNeighbor::trianglesWithinRange(TriangleMesh3D_ptr mesh, hpuint triangleId, float distance) {

    TriangleKDTree *tree = NearestNeighbor::generateTriangleKDTree(mesh);
    vector<hpuint> *triangleIndices = NearestNeighbor::trianglesWithinRange(mesh, triangleId, distance, *tree);

    free(tree);

    return triangleIndices;
}


vector<hpuint>* NearestNeighbor::trianglesWithinRange(TriangleMesh3D_ptr mesh, hpuint triangleId, float distance, TriangleKDTree& tree) {

    //assert(tree==0);

    // Test for triangles within the range of distance
    triangleKDTreeNode refNode;
    refNode.position = triangleCentroid(mesh, triangleId);

    vector<triangleKDTreeNode> closestTriangles;
    tree.find_within_range(refNode,distance,back_insert_iterator<vector<triangleKDTreeNode> >(closestTriangles));

    // Convert to triangle indices
    vector<hpuint> *triangleIndices = new vector<hpuint>(closestTriangles.size());
    hpuint i = 0;
    for (vector<triangleKDTreeNode>::iterator it = closestTriangles.begin(); it != closestTriangles.end(); ++it)
    {
        triangleIndices->at(i) = ((*it).index);
        ++i;
    }


    return triangleIndices;
}


TriangleKDTree* NearestNeighbor::generateTriangleKDTree(TriangleMesh3D_ptr mesh) {

    TriangleKDTree *tree = new TriangleKDTree();

    hpuint triangleCount = (mesh->getIndices()->size() / 3);

    // Fill KD Tree
    for (size_t triangle = 0; triangle < triangleCount; ++triangle) {
        triangleKDTreeNode triangleNode;
        triangleNode.position = NearestNeighbor::triangleCentroid(mesh, triangle);
        triangleNode.index = triangle;

        tree->insert(triangleNode);
    }


    return tree;

}

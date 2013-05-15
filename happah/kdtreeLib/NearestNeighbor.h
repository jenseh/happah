#ifndef NEARESTNEIGHBOR_H
#define NEARESTNEIGHBOR_H

#include "happah/HappahTypes.h"
#include "happah/geometries/TriangleMesh.h"

#include <kdtree++/kdtree.hpp>
#include <cstdio>
#include <vector>
#include <map>
#include <set>

using namespace std;


// KDTreeNode used for triangles
struct triangleKDTreeNode
{
    typedef hpreal value_type; //should be hpreal

    hpvec3 position;
    size_t index;

    hpreal operator[](size_t n) const
    {
        return position[n];
    }

    hpreal distance(const triangleKDTreeNode &node)
    {
        return glm::length(position - node.position);
    }
};

typedef KDTreeLib::KDTree<3,triangleKDTreeNode> TriangleKDTree;


class NearestNeighbor {

public:

    /** Searches all triangles whose center is closer or maximal as far as distance from the center of the given triangle (with triangleID).
        For the search it builds a KDTree for all triangles.
        Returns a vector with all triangleIds within the given range.

        Hint: the returned vector always contains triangleID (as it always passes the test).
      */
    static vector<hpuint> *trianglesWithinRange(TriangleMesh3D_ptr mesh, hpuint triangleId, float distance);

    /** Searches all triangles whose center is closer or maximal as far as distance from the center of the given triangle (with triangleID).
        For the search it uses the TriangleKDTree that has to be generated first (with generateTriangleKDTree).
        Returns a vector with all triangleIds within the given range.

        Hint: the returned vector always contains triangleID (as it always passes the test).
      */
    static vector<hpuint> *trianglesWithinRange(TriangleMesh3D_ptr mesh, hpuint triangleId, float distance, TriangleKDTree &tree);

    /** Generates a KDTree for all the Triangles within the given mesh.
        In the structure every triangle is described by its centroid and its index.

        Hint: Can be used with triangleWithinRange(...) to speed up many searches on the same mesh.
      */
    static TriangleKDTree *generateTriangleKDTree(TriangleMesh3D_ptr mesh);

private:

    /** Calculates the centroid (center) of the given triangle in the given triangleMesh.

        Hint: The mesh has to have a multiple of three as #indices and the triangleId must be valid,
              which means that 0 <= triangleID <= #indices/3.
      */
    static hpvec3 triangleCentroid(TriangleMesh3D_ptr mesh, hpuint triangleId);

};

#endif // NEARESTNEIGHBOR_H

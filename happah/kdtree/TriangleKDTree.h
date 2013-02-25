/*
    Code Based on "heatray" project by Cody White.
*/

#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <list>
#include <set>
#include <vector>

#include "happah/kdtree/Box.h"
#include "happah/kdtree/IntersectInfo.h"
#include "happah/kdtree/TriangleKDTreeNode.h"
#include "happah/models/TriangleMesh.h"


/**
  * KDTree class.
  */
class TriangleKDTree 
{
    typedef  glm::vec3 kvec;

    // Root of the tree
    TriangleKDTreeNode *m_root;

	public:

    /**
      * Default constructor.
      */
    TriangleKDTree();

    /**
      * Destructor.
      */
    ~TriangleKDTree();

    /**
      * Build the KDtree.
      * @param mesh Triangle mesh to use for building the tree.
      */
    void build (TriangleMesh &mesh);


    /**
      * Clear the kdtree.
      */
    void clear();

    /**
      * Intersect with the kdtree.
      * @param ray Ray to use for intersection tests.
      * @param info Intersection info struct to populate if a hit occurs.
      * @param shadow If this is a shadow ray, we can avoid some of the accuracy of an actual intersection to speed up this test.
      * @param tmin Minimum time to an intersection.
      */
    bool intersect (Ray &ray, IntersectInfo &info, const double tmin = 0.0);


	private:

    /**
      * Recursively build the tree.
      * @param node TriangleKDTreeNode to split.
      * @param current_depth Current depth in the tree.
      */
    void buildR (TriangleKDTreeNode *&node, int current_depth);

    /**
      * Perform a SAH split.
      * @param node TriangleKDTreeNode to perform the splitting of.
      * @param current_depth Current depth in the tree.
      */
    bool sahSplit (TriangleKDTreeNode *&node, int current_depth);

    /**
      * Perform a mediam split.
      * @param node TriangleKDTreeNode to split.
      * @param current_depth depth in the tree.
      */
    bool medianSplit (TriangleKDTreeNode *&node, int depth);

    /**
      * Recursively clear the tree.
      * @param node TriangleKDTreeNode to clear.
      */
    void clearR (TriangleKDTreeNode *&node);

		/**
		  * Split the tree.
		  */
    bool split (TriangleKDTreeNode *&node, int depth);

    /**
      * Recursively intersect with the tree.
      * @param node TriangleKDTreeNode to check.
      * @param ray Ray to check against node.
      * @param tmin Minimum time value allowed for an intersection to occur.
      * @param info Intersection information to be returned.
      */
    bool intersectR (const TriangleKDTreeNode *node, Ray &ray, const double &tmin, IntersectInfo &info);
};


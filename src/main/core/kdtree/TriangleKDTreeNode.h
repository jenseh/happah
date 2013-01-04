/*
    Code Based on heatray Project by Cody White.

*/

#pragma once

#include "../primitives/Ray.h"
#include "../primitives/Triangle.h"
#include "Box.h"


/**
  * KDTree node.
  */
struct TriangleKDTreeNode
{

    std::vector <Triangle *> triangles;		// List of triangles contained within this node.
    TriangleKDTreeNode *left;               // Left child of this node.
    TriangleKDTreeNode *right;              // Right child of this node.
    Box box;                                // Bounding box for this node.

	/**
	  * Default constructor.
	  */
	TriangleKDTreeNode (void)
	{
		left = NULL;
		right = NULL;
	}

	/**
	  * Destructor.
	  */
	~TriangleKDTreeNode (void)
	{
		triangles.clear ();
		left = NULL;
		right = NULL;
	}

	/**
	  * Return the area of the node.
	  */
    double getArea (void) const
	{
		return box.getArea ();	
	}

    /**
      * Get the amount of triangles from a passed in list
      * that would be contained within this node.
      * @param list List of triangles to test with.
      */
    int intersectCount (const std::vector <Triangle*> &list) const
    {
        int count = 0;
        for (size_t i = 0; i < list.size (); ++i)
        {
            count += (box.testTriangle (*list[i]) ? 1 : 0);
        }

        return count;
    }


	/**
	  * Check a ray for collision with this node.
	  * @param ray Ray to check with.
	  * @param time Time value returned if the ray hit.
	  */
    bool checkRay (const Ray &ray, double &time) const
	{
		return box.testRay (ray, time);	
	}

	/**
	  * Return leaf or not.
	  */
	bool isLeaf (void) const
	{
		return (left == NULL && right == NULL);
	}

	/**
	  * Insert a triangle into this node.
	  * @param triangle Triangle to insert.
	  */
    bool insertTriangle (Triangle *triangle)
	{
        if (box.testTriangle (*triangle))
		{
			triangles.push_back (triangle);
			return true;
		}

		return false;
	}
};



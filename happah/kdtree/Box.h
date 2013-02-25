/*
    Code Based on "heatray" project by Cody White.
*/

#pragma once

#include <glm/glm.hpp>
#include <iostream>

#include "happah/kdtree/TriangleBox.h"
#include "happah/primitives/Ray.h"
#include "happah/primitives/Triangle.h"

struct Box
{
    typedef glm::vec3 bvec;

    // Member variables.
    bvec min;		// Minimum value of this box.
    bvec max;   	// Maximum value of this box.
    bvec center;	// Center of the bounding box.
    bvec half_size;	// Half the size of the box.

	/**
	  * Default constructor.
	  */
    Box();

	/**
	  * Paramater constructor.
	  * @param _min Minimum value of the box.
	  * @param _max Maximum value of the box.
	  */
    Box (const bvec &_min, const bvec &_max);

	/**
	  * Operator=.
	  * @param other Box to set this box equal to.
	  */
    Box & operator= (const Box &other);

	/**
	  * Get the area of the box.
	  */
    double getArea () const;

	/**
	  * Test an intersection with a triangle.
	  * @param triangle Triangle to test against the box.
	  */
    bool testTriangle (const Triangle& triangle) const;

	/**
	  * Test a point to see if it lies within this box.
	  * @param point Point to test.
	  */
    bool testPoint (const bvec &point) const;

	/** 
	  * Test for a ray collision with this box.
	  * @param ray Ray to check with.
	  * @param time Distance from the ray to the box.
	  */
    bool testRay (const Ray &ray, double &time) const;

	/**
	  * Determine the center and the half size of the box.
	  */
    void calcDimensions (void);

    /**
      * Get the distance to a point from this box.
      * @param point Point to compute distance from.
      */
    double calcDistance (bvec& point) const;

};



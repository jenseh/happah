#ifndef TRIANGLEVERTICEREFS_H
#define TRIANGLEVERTICEREFS_H

#include <cmath>
#include "happah/HappahTypes.h"

/**
* @brief The TriangleVerticeRefs struct to store the vertices references to one complete triangle
*/
struct TriangleVerticeRefs {
	/**
	* @brief all the references to the 3 vertices
	*/
	const hpvec3* vertices[3];

	/**
	* @brief Array that represents the axis aligned bounding box of the constructed triangle.
	* 
	* The axis aligned bounding box consists of six planes: Two of them are parallel to each axis-axis-plane.
	* 
	* The first element contains the x-coordinates of the planes parallel to the yz-plane. 	
	* The second element contains the y-coordinates of the planes parallel to the xz-plane.
	* The third element contains the z-coordinates of the planes parallel to the xy-plane.
	* 
	* Each pair of coordinates is sorted in ascending order.
	*/

	const hpvec2* axisAlignedBoundingBox[3];


	/**
	* @brief Triangle constructor create one TriangleVerticeRefs type
	*/
	TriangleVerticeRefs(const hpvec3* vertexA, const hpvec3* vertexB, const hpvec3* vertexC) {
		vertices[0] = vertexA;
		vertices[1] = vertexB;
		vertices[2] = vertexC;		

		axisAlignedBoundingBox[0] = new hpvec2(std::min(std::min(vertexA->x, vertexB->x),vertexC->x), std::max(std::max(vertexA->x, vertexB->x),vertexC->x));
		axisAlignedBoundingBox[1] = new hpvec2(std::min(std::min(vertexA->y, vertexB->y),vertexC->y), std::max(std::max(vertexA->y, vertexB->y),vertexC->y));
		axisAlignedBoundingBox[2] = new hpvec2(std::min(std::min(vertexA->z, vertexB->z),vertexC->z), std::max(std::max(vertexA->z, vertexB->z),vertexC->z));
	}

	/**
	 * @fn	void clippedBoundingBox(int axis, hpreal p, hpvec3** left, hpvec3** right)
	 *
	 * @brief	Clips the bounding box relatively to the plane p which is perpendicular 
	 * 			to axis.
	 *
	 * @param	axis		 	The axis (=1,2 or 3)
	 * @param	p			 	The coordinate of the planes intersection.
	 * @param [in,out]	left 	The bounding box to the left of the plane.
	 * @param [in,out]	right	The bounding box to the right of the plane.
	 */

	void clippedBoundingBox(int axis, hpreal p, hpvec3** left, hpvec3** right) {
	}

	/**
	 * @fn	~TriangleVerticeRefs()
	 *
	 * @brief	Destructor.
	 */

	~TriangleVerticeRefs() {
		delete axisAlignedBoundingBox[0];
		delete axisAlignedBoundingBox[1];
		delete axisAlignedBoundingBox[2];
	}
};

#endif // TRIANGLEVERTICEREFS_H

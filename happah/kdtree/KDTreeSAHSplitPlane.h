#ifndef KDTREESAHSPLITPLANE_H
#define KDTREESAHSPLITPLANE_H

#include "KDTreeSplitPlaneStrategy.h"

class KDTreeSAHSplitPlane : public KDTreeSplitPlaneStrategy
{
	/**
	 * @enum	SweepEventType
	 *
	 * @brief	Values that represent SweepEventType.
	 */

	enum SweepEventType {
		///< An enum constant representing the end= 0 option
		END=0, 
		///< An enum constant representing the planar= 1 option
		PLANAR=1, 
		///< An enum constant representing the start= 2 option
		START=2
	};

	/**
	 * @struct	SweepEvent
	 *
	 * @brief	Sweep event.
	 */

	struct SweepEvent {
		int p;
		int axis;
		SweepEventType eventType;
		TriangleVerticeRefs* triangle;
	};


public:
	KDTreeSAHSplitPlane();

	/**
	* @fn	virtual void KDTreeSAHSplitPlane::buildKdTree(TriangleIterator& triangleIterator,
	* 		FastKdTree*& fastKdTree);
	*
	* @brief	Builds the kd-tree using SAH to split the triangles.
	*
	* @param [in,out]	triangleIterator	The triangle iterator.
	* @param [in,out]	fastKdTree			[in,out] The fast kd tree.
	*/

	virtual void buildKdTree(TriangleIterator& triangleIterator, FastKdTree*& fastKdTree);

private:

	void findPlane(int axis, hpreal p);
};

#endif // KDTREESAHSPLITPLANE_H

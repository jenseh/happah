#ifndef KDTREEMEDIANSPLITPLANE_H
#define KDTREEMEDIANSPLITPLANE_H

#include "KDTreeSplitPlaneStrategy.h"

class KDTreeMedianSplitPlane : public KDTreeSplitPlaneStrategy
{
public:
    KDTreeMedianSplitPlane();
	virtual FastKdTree* planePosistion(int axis, FastKdTree& fastKdTree);
};

#endif // KDTREEMEDIANSPLITPLANE_H

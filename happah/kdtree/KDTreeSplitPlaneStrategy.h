#ifndef KDTREESPLITPLANESTRATEGY_H
#define KDTREESPLITPLANESTRATEGY_H

#include "FastKdTree.h"
#include "TriangleIterator.h"

class KDTreeSplitPlaneStrategy
{
public:
    KDTreeSplitPlaneStrategy();
	virtual void buildKdTree(TriangleIterator& triangleIterator, FastKdTree*& fastKdTree) = 0;
};

#endif // KDTREESPLITPLANESTRATEGY_H

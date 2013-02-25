#ifndef EXPLICITKDTREENODE_H
#define EXPLICITKDTREENODE_H

#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

#include "happah/primitives/Circle.h"
#include "happah/primitives/Triangle.h"


class ExplicitKDTreeNode
{
public:
  virtual ~ExplicitKDTreeNode();

  virtual bool intersectAll(Circle& intersector, std::list<CircleHitResult*>* hitResults, BBox* intersectorBox, int depth);
};

#endif // EXPLICITKDTREENODE_H

#ifndef EXPLICITKDTREENODE_H
#define EXPLICITKDTREENODE_H

#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

#include "../primitives/Triangle.h"
#include "../primitives/Circle.h"


class ExplicitKDTreeNode
{
public:
  virtual ~ExplicitKDTreeNode();

  virtual bool intersectAll(Circle& intersector, std::list<CircleHitResult*>* hitResults, BBox* intersectorBox, int depth);
};

#endif // EXPLICITKDTREENODE_H

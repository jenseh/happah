#ifndef EXPLICITKDTREENODE_H
#define EXPLICITKDTREENODE_H

#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

#include "happah/math/Triangle.h"
#include "happah/math/Circle.h"


class ExplicitKDTreeNode
{
public:
  virtual ~ExplicitKDTreeNode();

  virtual bool intersectAll(Circle& intersector, std::list<CircleHitResult*>* hitResults, BBox* intersectorBox, hpuint depth);
};

#endif // EXPLICITKDTREENODE_H

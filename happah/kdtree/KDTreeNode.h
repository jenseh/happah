#ifndef KDTREENODE_H
#define KDTREENODE_H

#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

#include "happah/math/Triangle.h"
#include "happah/math/Circle.h"
#include "happah/math/Ray.h"


class KDTreeNode
{
public:
  virtual ~KDTreeNode();

  virtual bool intersectAll(Circle& intersector, std::list<CircleHitResult*>* hitResults, BBox* intersectorBox, hpuint depth);
  virtual hpreal intersectFirst(Ray& intersector, hpreal maxLength);
};

#endif // KDTREENODE_H

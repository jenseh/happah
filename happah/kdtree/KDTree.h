#ifndef KDTREE_H
#define KDTREE_H

#include <vector>
#include <list>
#include <iostream>

#include "happah/math/Triangle.h"
#include "happah/math/Circle.h"
#include "happah/kdtree/KDTreeInnerNode.h"
#include "happah/kdtree/BBox.h"


class KDTree
{
public:
  KDTree(std::vector<Triangle>* triangles, hpuint maxTrianglesPerBox = 50);
  ~KDTree();

  bool intersectAll(Circle& intersector, std::list<CircleHitResult*>* hitResults);
  hpreal intersectFirst(Ray& intersector, hpreal maxLength);
  hpuint countTriangles();

private:
  KDTreeInnerNode* m_root;

  BBox m_bBox;
};

#endif // KDTREE_H

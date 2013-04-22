#ifndef KDTREELEAF_H
#define KDTREELEAF_H

#include <vector>
#include <list>

#include "KDTreeNode.h"
#include "happah/math/Circle.h"
#include "happah/math/Triangle.h"

class KDTreeLeaf : public KDTreeNode
{
public:
  KDTreeLeaf(std::vector<Triangle>* triangles, int depth);
  ~KDTreeLeaf();

  bool intersectAll(Circle& intersector, std::list<CircleHitResult>* hitResults, BBox& intersectorBox, hpuint depth);
  hpreal intersectFirst(Ray& intersector, hpreal maxLength);
  hpuint countTriangles();

private:
  std::vector<Triangle>* m_triangles;
};

#endif // KDTREELEAF_H

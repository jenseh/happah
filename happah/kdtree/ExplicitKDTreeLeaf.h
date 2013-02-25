#ifndef EXPLICITKDTREELEAF_H
#define EXPLICITKDTREELEAF_H

#include <list>
#include <vector>

#include "happah/kdtree/ExplicitKDTreeNode.h"
#include "happah/primitives/Circle.h"
#include "happah/primitives/Triangle.h"

class ExplicitKDTreeLeaf : public ExplicitKDTreeNode
{
public:
  ExplicitKDTreeLeaf(std::vector<Triangle*>* triangles, int depth);

  bool intersectAll(Circle& intersector, std::list<CircleHitResult*>* hitResults, BBox* intersectorBox, int depth);

private:
  std::vector<Triangle*>* m_triangles;
};

#endif // EXPLICITKDTREELEAF_H

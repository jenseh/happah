#ifndef EXPLICITKDTREELEAF_H
#define EXPLICITKDTREELEAF_H

#include <vector>
#include <list>

#include "ExplicitKDTreeNode.h"
#include "../primitives/Circle.h"
#include "../primitives/Triangle.h"

class ExplicitKDTreeLeaf : public ExplicitKDTreeNode
{
public:
  ExplicitKDTreeLeaf(std::vector<Triangle*>* triangles, int depth);

  bool intersectAll(Circle& intersector, std::list<CircleHitResult*>* hitResults, BBox* intersectorBox, int depth);

private:
  std::vector<Triangle*>* m_triangles;
};

#endif // EXPLICITKDTREELEAF_H

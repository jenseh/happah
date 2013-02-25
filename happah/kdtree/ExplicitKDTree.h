#ifndef EXPLICITKDTREE_H
#define EXPLICITKDTREE_H

#include <list>
#include <vector>

#include "happah/kdtree/BBox.h"
#include "happah/kdtree/BSphere.h"
#include "happah/kdtree/ExplicitKDTreeInnerNode.h"
#include "happah/primitives/Circle.h"
#include "happah/primitives/Triangle.h"


class ExplicitKDTree
{
public:
  ExplicitKDTree(std::vector<Triangle*>* triangles);

  bool intersectAll(Circle& intersector, std::list<CircleHitResult*>* hitResults);

private:
  ExplicitKDTreeInnerNode* m_root;

  BBox* m_bBox;
};

#endif // EXPLICITKDTREE_H

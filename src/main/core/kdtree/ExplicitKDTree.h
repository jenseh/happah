#ifndef EXPLICITKDTREE_H
#define EXPLICITKDTREE_H

#include <vector>
#include <list>

#include "../primitives/Triangle.h"
#include "../primitives/Circle.h"
#include "ExplicitKDTreeInnerNode.h"
#include "BBox.h"
#include "BSphere.h"


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

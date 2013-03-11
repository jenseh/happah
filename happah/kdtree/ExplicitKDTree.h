#ifndef EXPLICITKDTREE_H
#define EXPLICITKDTREE_H

#include <vector>
#include <list>

#include "happah/math/Triangle.h"
#include "happah/math/Circle.h"
#include "happah/kdtree/ExplicitKDTreeInnerNode.h"
#include "happah/kdtree/BBox.h"
#include "happah/kdtree/BSphere.h"


class ExplicitKDTree
{
public:
  ExplicitKDTree(std::vector<Triangle*>* triangles, hpuint maxTrianglesPerBox = 500);

  bool intersectAll(Circle& intersector, std::list<CircleHitResult*>* hitResults);

private:
  ExplicitKDTreeInnerNode* m_root;

  BBox* m_bBox;
};

#endif // EXPLICITKDTREE_H

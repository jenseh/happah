#ifndef IMPLICITKDTREE_H
#define IMPLICITKDTREE_H

#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

#include "../primitives/Triangle.h"
#include "../primitives/Circle.h"
#include "BBox.h"
#include "BSphere.h"

struct TreeNode {
  float axisValue;
  int treeIndex;

  TreeNode(float axisValue_, int treeIndex_) {
    axisValue = axisValue_;
    treeIndex = treeIndex_;
  }
};

class ImplicitKDTree
{
public:
  ImplicitKDTree(std::vector<Triangle*>& triangles);

  template <typename Intersector> bool intersectAll(Intersector& intersector, std::list<CircleHitResult>& hitResults);

private:
  template <typename Intersector> bool intersectAllRec(Intersector& intersector, std::list<CircleHitResult>& hitResults, BBox& circleBox, int depth, unsigned int kPos);

  BBox* m_bBox;
  BSphere* m_bSphere;
  std::vector<Triangle*>& m_triangles;
  std::vector<TreeNode> m_tree; //TODO: Define a pessimistic start size, maybe log2(size/maxTriangles)
};

#endif // IMPLICITKDTREE_H

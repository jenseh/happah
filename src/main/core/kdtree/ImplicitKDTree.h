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

template <class T>
class ImplicitKDTree
{
public:
  ImplicitKDTree(std::vector<T*>& triangles);

  bool intersect(Circle& circle, std::list<T*>& hits);

private:
  bool intersectRec(Circle& circle, std::list<T*>& hits, BBox& circleBox, int depth, unsigned int kPos);

  BBox* m_bBox;
  BSphere* m_bSphere;
  std::vector<T*>& m_triangles;
  std::vector<TreeNode> m_tree; //TODO: Define a pessimistic start size, maybe log2(size/maxTriangles)
};

#endif // IMPLICITKDTREE_H

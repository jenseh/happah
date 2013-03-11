#ifndef EXPLICITKDTREEINNERNODE_H
#define EXPLICITKDTREEINNERNODE_H

#include "happah/kdtree/ExplicitKDTreeNode.h"
#include "happah/kdtree/ExplicitKDTreeInnerNode.h"
#include "happah/kdtree/ExplicitKDTreeLeaf.h"

class ExplicitKDTreeInnerNode : public ExplicitKDTreeNode
{
public:
  ExplicitKDTreeInnerNode(std::vector<Triangle*>* triangles, BBox* bBox, hpuint depth, hpuint maxTrianglesPerBox);

  bool intersectAll(Circle& intersector, std::list<CircleHitResult*>* hitResults, BBox* intersectorBox, int depth);

private:
  ExplicitKDTreeNode* m_leftChild;
  ExplicitKDTreeNode* m_rightChild;

  BBox* m_bBox;

  float m_axisValue;
  int m_axis;
};

#endif // EXPLICITKDTREEINNERNODE_H

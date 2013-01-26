#ifndef EXPLICITKDTREEINNERNODE_H
#define EXPLICITKDTREEINNERNODE_H

#include "ExplicitKDTreeNode.h"
#include "ExplicitKDTreeInnerNode.h"
#include "ExplicitKDTreeLeaf.h"

class ExplicitKDTreeInnerNode : public ExplicitKDTreeNode
{
public:
  ExplicitKDTreeInnerNode(std::vector<Triangle*>* triangles, BBox* bBox, int depth);

  bool intersectAll(Circle& intersector, std::list<CircleHitResult*>* hitResults, BBox* intersectorBox, int depth);

private:
  ExplicitKDTreeNode* m_leftChild;
  ExplicitKDTreeNode* m_rightChild;

  BBox* m_bBox;

  float m_axisValue;
  int m_axis;
};

#endif // EXPLICITKDTREEINNERNODE_H

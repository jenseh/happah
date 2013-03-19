#ifndef KDTREEINNERNODE_H
#define KDTREEINNERNODE_H

#include "happah/math/Ray.h"
#include "happah/kdtree/KDTreeNode.h"
#include "happah/kdtree/KDTreeInnerNode.h"
#include "happah/kdtree/KDTreeLeaf.h"


class KDTreeInnerNode : public KDTreeNode
{
public:
  KDTreeInnerNode(std::vector<Triangle>* triangles, BBox* bBox, hpuint depth, hpuint maxTrianglesPerBox);
  ~KDTreeInnerNode();

  bool intersectAll(Circle& intersector, std::list<CircleHitResult*>* hitResults, BBox* intersectorBox, int depth);
  hpreal intersectFirst(Ray& intersector, hpreal maxLength);
private:
  KDTreeNode* m_leftChild;
  KDTreeNode* m_rightChild;

  BBox* m_bBox;

  float m_axisValue;
  int m_axis;
};

#endif // KDTREEINNERNODE_H

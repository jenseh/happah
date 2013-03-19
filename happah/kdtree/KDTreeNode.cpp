#include "KDTreeNode.h"

KDTreeNode::~KDTreeNode() {}

bool KDTreeNode::intersectAll(Circle& intersector, std::list<CircleHitResult*>* hitResults, BBox& intersectorBox, hpuint depth) {
	return false;
}

hpreal KDTreeNode::intersectFirst(Ray& intersector, hpreal maxLength){
	return maxLength;
}

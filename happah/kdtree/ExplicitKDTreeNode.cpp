#include "ExplicitKDTreeNode.h"

ExplicitKDTreeNode::~ExplicitKDTreeNode() {}

bool ExplicitKDTreeNode::intersectAll(Circle& intersector, std::list<CircleHitResult*>* hitResults, BBox* intersectorBox, hpuint depth) {
	return false;
}

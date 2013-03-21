#include "KDTree.h"

KDTree::KDTree(std::vector<Triangle>* triangles, hpuint maxTrianglesPerBox) {
	// Compute bounding box for whole tree
  for (std::vector<Triangle>::iterator t = triangles->begin(); t != triangles->end(); t++) {
      m_bBox.addTriangle(*t);
  }
  // Create root node
  m_root = new KDTreeInnerNode(triangles, m_bBox, 0, maxTrianglesPerBox);
}

KDTree::~KDTree(){
	delete m_root;
}

bool KDTree::intersectAll(Circle& intersector, std::list<CircleHitResult*>* hitResults) {
  BBox intersectorBox = intersector.computeBoundingBox();
  return m_root->intersectAll(intersector, hitResults, intersectorBox, 0);
}

hpreal KDTree::intersectFirst(Ray& intersector, hpreal maxLength){
	return m_root->intersectFirst(intersector, maxLength);
}

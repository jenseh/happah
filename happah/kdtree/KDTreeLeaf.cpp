#include "KDTreeLeaf.h"

KDTreeLeaf::KDTreeLeaf(std::vector<Triangle>* triangles, int depth)
{
        m_triangles = triangles;
}

KDTreeLeaf::~KDTreeLeaf(){
	delete m_triangles;
}


bool KDTreeLeaf::intersectAll(Circle& intersector, std::list<CircleHitResult*>* hitResults, BBox& intersectorBox, hpuint depth) {
		// Leaf node
      std::vector<Triangle>::iterator pos = m_triangles->begin();
      std::vector<Triangle>::iterator end = m_triangles->end();
      bool hit = false;
      for (; pos != end; pos++) {
          Triangle triangle = *pos;

          if (intersector.intersect(&triangle, hitResults)) {
              hit = true;
            }
        }
      return hit;
}

hpreal KDTreeLeaf::intersectFirst(Ray& intersector, hpreal maxLength){
	for(std::vector<Triangle>::iterator pos = m_triangles->begin(); pos != m_triangles->end(); ++pos){
		maxLength = std::min(maxLength, intersector.intersectDistance(*pos));
	}
	return maxLength;
}

hpuint KDTreeLeaf::countTriangles() {
	return m_triangles->size();
}


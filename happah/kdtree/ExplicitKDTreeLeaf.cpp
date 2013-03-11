#include "ExplicitKDTreeLeaf.h"

ExplicitKDTreeLeaf::ExplicitKDTreeLeaf(std::vector<Triangle*>* triangles, int depth)
{
        m_triangles = triangles;
}


bool ExplicitKDTreeLeaf::intersectAll(Circle& intersector, std::list<CircleHitResult*>* hitResults, BBox* intersectorBox, int depth) {
      // Leaf node
      std::vector<Triangle*>::iterator pos = m_triangles->begin();
      std::vector<Triangle*>::iterator end = m_triangles->end();
      bool hit = false;
      for (; pos != end; pos++) {
          Triangle* triangle = *pos;

          if (intersector.intersect(triangle, hitResults)) {
              hit = true;
            }
        }
      return hit;
}

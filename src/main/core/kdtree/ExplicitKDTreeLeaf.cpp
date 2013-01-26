#include "ExplicitKDTreeLeaf.h"

ExplicitKDTreeLeaf::ExplicitKDTreeLeaf(std::vector<Triangle*>* triangles, int depth)
{
        m_triangles = triangles;
        //  for (std::vector<Triangle*>::iterator t = triangles.begin(); t != triangles.end(); t++) {
        //      glm::vec3& t_v0 = (*t)->vertices[0];
        //      glm::vec3& t_v1 = (*t)->vertices[1];
        //      glm::vec3& t_v2 = (*t)->vertices[2];

        //      std::cout << "triangleA: " << t_v0.x << ", " << t_v0.y << ", " << t_v0.z << std::endl;
        //      std::cout << "triangleB: " << t_v1.x << ", " << t_v1.y << ", " << t_v1.z << std::endl;
        //      std::cout << "triangleC: " << t_v2.x << ", " << t_v2.y << ", " << t_v2.z << std::endl;
        //    }

//        for (unsigned int pos = 0; pos < triangles.size(); pos++) {
//            Triangle* triangle = triangles[pos];
//            std::cout << "triangleA: " << triangle->vertices[0].x << ", " << triangle->vertices[0].y << ", " << triangle->vertices[0].z << std::endl;
//            std::cout << "triangleB: " << triangle->vertices[1].x << ", " << triangle->vertices[1].y << ", " << triangle->vertices[1].z << std::endl;
//            std::cout << "triangleC: " << triangle->vertices[2].x << ", " << triangle->vertices[2].y << ", " << triangle->vertices[2].z << std::endl;
//        }
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

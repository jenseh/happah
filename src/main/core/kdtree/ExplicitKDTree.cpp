#include "ExplicitKDTree.h"

ExplicitKDTree::ExplicitKDTree(std::vector<Triangle*>* triangles) {
  // Compute bounding box for whole tree
  float minX = INFINITY, minY = INFINITY, minZ = INFINITY, maxX = -INFINITY, maxY = -INFINITY, maxZ = -INFINITY;

  for (std::vector<Triangle*>::iterator t = triangles->begin(); t != triangles->end(); t++) {
      for (int i = 0; i < 3; i++) {
        float x = (*t)->vertices[i].x;
        float y = (*t)->vertices[i].y;
        float z = (*t)->vertices[i].z;

        if (x < minX) minX = x;
        else if (x > maxX) maxX = x;

        if (y < minY) minY = y;
        else if (y > maxY) maxY = y;

        if (z < minZ) minZ = z;
        else if (z > maxZ) maxZ = z;
      }
  }

  glm::vec3 min = glm::vec3(minX, minY, minZ);
  glm::vec3 max = glm::vec3(maxX, maxY, maxZ);
  m_bBox = new BBox(min, max);

  // Create root node
  m_root = new ExplicitKDTreeInnerNode(triangles, m_bBox, 0);

//    std::cout << "Built BBox-Min: " << m_bBox->getMin()->x << ", " << m_bBox->getMin()->y << ", " << m_bBox->getMin()->z << std::endl;
//    std::cout << "Built BBox-Max: " << m_bBox->getMax()->x << ", " << m_bBox->getMax()->y << ", " << m_bBox->getMax()->z << std::endl;

//  for (std::vector<Triangle*>::iterator t = triangles->begin(); t != triangles->end(); t++) {
//      glm::vec3& t_v0 = (*t)->vertices[0];
//      glm::vec3& t_v1 = (*t)->vertices[1];
//      glm::vec3& t_v2 = (*t)->vertices[2];

//      std::cout << "triangleA: " << t_v0.x << ", " << t_v0.y << ", " << t_v0.z << std::endl;
//      std::cout << "triangleB: " << t_v1.x << ", " << t_v1.y << ", " << t_v1.z << std::endl;
//      std::cout << "triangleC: " << t_v2.x << ", " << t_v2.y << ", " << t_v2.z << std::endl;
//    }
}

bool ExplicitKDTree::intersectAll(Circle& intersector, std::list<CircleHitResult*>* hitResults) {
  BBox intersectorBox = intersector.computeBoundingBox();
  return m_root->intersectAll(intersector, hitResults, &intersectorBox, 0);
}

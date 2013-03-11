#include "ExplicitKDTree.h"

ExplicitKDTree::ExplicitKDTree(std::vector<Triangle*>* triangles, hpuint maxTrianglesPerBox) {
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
  m_root = new ExplicitKDTreeInnerNode(triangles, m_bBox, 0, maxTrianglesPerBox);
}

bool ExplicitKDTree::intersectAll(Circle& intersector, std::list<CircleHitResult*>* hitResults) {
  BBox intersectorBox = intersector.computeBoundingBox();
  return m_root->intersectAll(intersector, hitResults, &intersectorBox, 0);
}
